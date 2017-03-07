
/*++

Copyright (c) 1990-2000    Microsoft Corporation All Rights Reserved

Module Name:

    filter.c

Abstract:

    This module shows how to a write a filter driver for Windows2000.

Environment:

    Kernel mode

Revision History:

    Eliyas Yakub Oct 29 1998

--*/
#include <ntddk.h>
#include <ntddser.h>
#include "filter.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, FilterAddDevice)
#pragma alloc_text (PAGE, FilterDispatchPnp)
#pragma alloc_text (PAGE, FilterDispatchPower)
#pragma alloc_text (PAGE, FilterUnload)
#endif


NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:

    Installable driver initialization entry point.
    This entry point is called directly by the I/O system.

Arguments:

    DriverObject - pointer to the driver object

    RegistryPath - pointer to a unicode string representing the path,
                   to driver-specific key in the registry.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
    NTSTATUS            status = STATUS_SUCCESS;
    ULONG               ulIndex;
    PDRIVER_DISPATCH  * dispatch;

    UNREFERENCED_PARAMETER (RegistryPath);

    DebugPrint (("Entered the Driver Entry  build on %s  %s\n", __DATE__, __TIME__));
    

    //
    // Create dispatch points
    //
    for (ulIndex = 0, dispatch = DriverObject->MajorFunction;
         ulIndex <= IRP_MJ_MAXIMUM_FUNCTION;
         ulIndex++, dispatch++) {

        *dispatch = FilterPass;
    }

    DriverObject->MajorFunction[IRP_MJ_PNP]            = FilterDispatchPnp;
    DriverObject->MajorFunction[IRP_MJ_POWER]          = FilterDispatchPower;
    DriverObject->DriverExtension->AddDevice           = FilterAddDevice;
    DriverObject->DriverUnload                         = FilterUnload;

	//++ by cz.zhou
    DriverObject->MajorFunction[IRP_MJ_CREATE]			= FilterCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE]			= FilterClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]  = FilterIoControl;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP]         = FilterCleanup;

    DriverObject->MajorFunction[IRP_MJ_READ]			= FilterRead;
    DriverObject->MajorFunction[IRP_MJ_WRITE]			= FilterWrite;
	//--
    return status;
}


NTSTATUS
FilterAddDevice(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT PhysicalDeviceObject
    )
/*++

Routine Description:

    The Plug & Play subsystem is handing us a brand new PDO, for which we
    (by means of INF registration) have been asked to provide a driver.

    We need to determine if we need to be in the driver stack for the device.
    Create a function device object to attach to the stack
    Initialize that device object
    Return status success.

    Remember: We can NOT actually send ANY non pnp IRPS to the given driver
    stack, UNTIL we have received an IRP_MN_START_DEVICE.

Arguments:

    DeviceObject - pointer to a device object.

    PhysicalDeviceObject -  pointer to a device object created by the
                            underlying bus driver.

Return Value:

    NT status code.

--*/
{
    NTSTATUS                status = STATUS_SUCCESS;
    PDEVICE_OBJECT          deviceObject = NULL;
    PDEVICE_EXTENSION       deviceExtension; 
    
    PAGED_CODE ();

    //
    // Create a filter device object.
    //

    status = IoCreateDevice (DriverObject,
                             sizeof (DEVICE_EXTENSION),
                             NULL,  // No Name
                             FILE_DEVICE_UNKNOWN,
                             FILE_DEVICE_SECURE_OPEN,
                             FALSE,
                             &deviceObject);

    
    if (!NT_SUCCESS (status)) {
        //
        // Returning failure here prevents the entire stack from functioning,
        // but most likely the rest of the stack will not be able to create
        // device objects either, so it is still OK.
        //
        return status;
    }

    DebugPrint (("AddDevice PDO (0x%x) FDO (0x%x)\n", 
                    PhysicalDeviceObject, deviceObject));

    deviceExtension = (PDEVICE_EXTENSION) deviceObject->DeviceExtension;
  
    deviceExtension->NextLowerDriver = IoAttachDeviceToDeviceStack (
                                       deviceObject,
                                       PhysicalDeviceObject);
    //
    // Failure for attachment is an indication of a broken plug & play system.
    //

    if(NULL == deviceExtension->NextLowerDriver) {

        IoDeleteDevice(deviceObject);
        return STATUS_UNSUCCESSFUL;
    }

    deviceObject->Flags |= deviceExtension->NextLowerDriver->Flags & 
                            (DO_BUFFERED_IO | DO_DIRECT_IO | 
                            DO_POWER_PAGABLE  | DO_POWER_INRUSH);
                            
    
    deviceObject->DeviceType = deviceExtension->NextLowerDriver->DeviceType;

    deviceObject->Characteristics = 
                          deviceExtension->NextLowerDriver->Characteristics;

    deviceExtension->Self = deviceObject;

    //
    // Set the initial state of the Filter DO
    //

    INITIALIZE_PNP_STATE(deviceExtension);
 
    DebugPrint(("AddDevice: %x to %x->%x \n", deviceObject, 
                       deviceExtension->NextLowerDriver,
                       PhysicalDeviceObject));

    deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    return STATUS_SUCCESS;

}

FilterCompletionRoutine(
    IN PDEVICE_OBJECT   DeviceObject,
    IN PIRP             Irp,
    IN PVOID            Context
    )
/*++
Routine Description:
    A completion routine for use when calling the lower device objects to
    which our filter deviceobject is attached.

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.
    Context      - Pointer to an event object    
Return Value:

    NT Status is returned.

--*/

{
    UNREFERENCED_PARAMETER(DeviceObject);

    if (Irp->PendingReturned) {
        IoMarkIrpPending(Irp);
    }

    //
    // We could switch on the major and minor functions of the IRP to perform
    // different functions, but we know that Context is an event that needs
    // to be set.
    //

    KeSetEvent((PKEVENT) Context, IO_NO_INCREMENT, FALSE);

    //
    // Allows the caller to use the IRP after it is completed
    //
    return STATUS_MORE_PROCESSING_REQUIRED;
}

NTSTATUS
FilterPass (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )
/*++

Routine Description:

    The default dispatch routine.  If this driver does not recognize the
    IRP, then it should send it down, unmodified.
    If the device holds iris, this IRP must be queued in the device extension
    No completion routine is required.
    
    For demonstrative purposes only, we will pass all the (non-PnP) Irps down
    on the stack (as we are a filter driver). A real driver might choose to 
    service some of these Irps.

    As we have NO idea which function we are happily passing on, we can make
    NO assumptions about whether or not it will be called at raised IRQL.
    For this reason, this function must be in put into non-paged pool
    (aka the default location).

Arguments:

   DeviceObject - pointer to a device object.

   Irp - pointer to an I/O Request Packet.

Return Value:

      NT status code

--*/
{
    PDEVICE_EXTENSION           deviceExtension; 
    PIO_STACK_LOCATION          irpStack;
	NTSTATUS				status;

	DebugPrint(("+   Enter Filter pass\n"));

    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
	irpStack = IoGetCurrentIrpStackLocation( Irp );
	DebugPrint(("MajorFunction:  0x%x\n", irpStack->MajorFunction ));
    IoSkipCurrentIrpStackLocation (Irp);
	status = IoCallDriver (deviceExtension->NextLowerDriver, Irp);
	DebugPrint(("-   Exit filter pass\n"));
	return status;
}

NTSTATUS
FilterDispatchPnp (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )
/*++

Routine Description:

    The plug and play dispatch routines.

    Most of these the driver will completely ignore.
    In all cases it must pass on the IRP to the lower driver.

Arguments:

   DeviceObject - pointer to a device object.

   Irp - pointer to an I/O Request Packet.

Return Value:

      NT status code

--*/
{
    PDEVICE_EXTENSION           deviceExtension; 
    PIO_STACK_LOCATION          irpStack;
    NTSTATUS                    status;
    KEVENT                      event;        

    PAGED_CODE();

    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
    irpStack = IoGetCurrentIrpStackLocation(Irp);

    DebugPrint(("FilterDO %s IRP:0x%x \n", 
                PnPMinorFunctionString(irpStack->MinorFunction), Irp));

    status = STATUS_SUCCESS;
    
    switch (irpStack->MinorFunction) {
    case IRP_MN_START_DEVICE:

        //
        // The device is starting.
        //
        // We cannot touch the device (send it any non pnp irps) until a
        // start device has been passed down to the lower drivers.
        //
        IoCopyCurrentIrpStackLocationToNext(Irp);
        KeInitializeEvent(&event,
                          NotificationEvent,
                          FALSE
                          );

        IoSetCompletionRoutine(Irp,
                               (PIO_COMPLETION_ROUTINE) FilterCompletionRoutine, 
                               &event,
                               TRUE,
                               TRUE,
                               TRUE); // No need for Cancel

        status = IoCallDriver(deviceExtension->NextLowerDriver, Irp);

        if (STATUS_PENDING == status) {
            KeWaitForSingleObject(
               &event,
               Executive, // Waiting for reason of a driver
               KernelMode, // Waiting in kernel mode
               FALSE, // No alert
               NULL); // No timeout
        }

        if (NT_SUCCESS(status) && NT_SUCCESS(Irp->IoStatus.Status)) {
            //
            // As we are successfully now back from our start device
            // we can do work.
            //
            SET_NEW_PNP_STATE(deviceExtension, Started);
        }

        //
        // We must now complete the IRP, since we stopped it in the
        // completion routine with STATUS_MORE_PROCESSING_REQUIRED.
        //
        Irp->IoStatus.Status = status;
        IoCompleteRequest(Irp, IO_NO_INCREMENT);
        return status;
        
    case IRP_MN_REMOVE_DEVICE:
        
        IoSkipCurrentIrpStackLocation(Irp);

        status = IoCallDriver(deviceExtension->NextLowerDriver, Irp);

        SET_NEW_PNP_STATE(deviceExtension, Deleted);

        IoDetachDevice(deviceExtension->NextLowerDriver); 
        IoDeleteDevice(DeviceObject);
        return status;
        
        
    case IRP_MN_QUERY_STOP_DEVICE:
        SET_NEW_PNP_STATE(deviceExtension, StopPending);
        status = STATUS_SUCCESS;
        break;
        
    case IRP_MN_CANCEL_STOP_DEVICE:

        //
        // Check to see whether you have received cancel-stop
        // without first receiving a query-stop. This could happen if someone
        // above us fails a query-stop and passes down the subsequent
        // cancel-stop.
        //
        
        if(StopPending == deviceExtension->DevicePnPState)
        {
            //
            // We did receive a query-stop, so restore.
            //             
            RESTORE_PREVIOUS_PNP_STATE(deviceExtension);
        }
        status = STATUS_SUCCESS; // We must not fail this IRP.
        break;
        
    case IRP_MN_STOP_DEVICE:
        SET_NEW_PNP_STATE(deviceExtension, StopPending);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_QUERY_REMOVE_DEVICE:

        SET_NEW_PNP_STATE(deviceExtension, RemovePending);
        status = STATUS_SUCCESS;
        break;
       
    case IRP_MN_SURPRISE_REMOVAL:

        SET_NEW_PNP_STATE(deviceExtension, SurpriseRemovePending);
        status = STATUS_SUCCESS;
        break;

    case IRP_MN_CANCEL_REMOVE_DEVICE:

        //
        // Check to see whether you have received cancel-remove
        // without first receiving a query-remove. This could happen if 
        // someone above us fails a query-remove and passes down the 
        // subsequent cancel-remove.
        //
        
        if(RemovePending == deviceExtension->DevicePnPState)
        {
            //
            // We did receive a query-remove, so restore.
            //             
            RESTORE_PREVIOUS_PNP_STATE(deviceExtension);
        }
        status = STATUS_SUCCESS; // We must not fail this IRP.
        break;
         
        
    default:
        //
        // If you don't handle any IRP you must leave the
        // status as is.
        //        
        status = Irp->IoStatus.Status;

        break;
    }

    //
    // Pass the IRP down and forget it.
    //
    Irp->IoStatus.Status = status;
    return FilterPass(DeviceObject, Irp);
}


NTSTATUS
FilterDispatchPower(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
/*++

Routine Description:

    This routine is the dispatch routine for power irps.

Arguments:

    DeviceObject - Pointer to the device object.

    Irp - Pointer to the request packet.

Return Value:

    NT Status code
--*/
{
    PDEVICE_EXTENSION   deviceExtension;
    
    PAGED_CODE ();

    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
    PoStartNextPowerIrp(Irp);
    IoSkipCurrentIrpStackLocation(Irp);
    return PoCallDriver(deviceExtension->NextLowerDriver, Irp);
}


    
VOID
FilterUnload(
    IN PDRIVER_OBJECT DriverObject
    )
/*++

Routine Description:

    Free all the allocated resources in DriverEntry, etc.

Arguments:

    DriverObject - pointer to a driver object.

Return Value:

    VOID.

--*/
{
    PAGED_CODE ();

    //
    // The device object(s) should be NULL now
    // (since we unload, all the devices objects associated with this
    // driver must be deleted.
    //
    ASSERT(DriverObject->DeviceObject == NULL);
    
    //
    // We should not be unloaded until all the devices we control 
    // have been removed from our queue.  
    //
    DebugPrint (("unload\n"));

    return;
}


#if DBG



PCHAR
PnPMinorFunctionString (
    UCHAR MinorFunction
)
{
    switch (MinorFunction)
    {
        case IRP_MN_START_DEVICE:
            return "IRP_MN_START_DEVICE";
        case IRP_MN_QUERY_REMOVE_DEVICE:
            return "IRP_MN_QUERY_REMOVE_DEVICE";
        case IRP_MN_REMOVE_DEVICE:
            return "IRP_MN_REMOVE_DEVICE";
        case IRP_MN_CANCEL_REMOVE_DEVICE:
            return "IRP_MN_CANCEL_REMOVE_DEVICE";
        case IRP_MN_STOP_DEVICE:
            return "IRP_MN_STOP_DEVICE";
        case IRP_MN_QUERY_STOP_DEVICE:
            return "IRP_MN_QUERY_STOP_DEVICE";
        case IRP_MN_CANCEL_STOP_DEVICE:
            return "IRP_MN_CANCEL_STOP_DEVICE";
        case IRP_MN_QUERY_DEVICE_RELATIONS:
            return "IRP_MN_QUERY_DEVICE_RELATIONS";
        case IRP_MN_QUERY_INTERFACE:
            return "IRP_MN_QUERY_INTERFACE";
        case IRP_MN_QUERY_CAPABILITIES:
            return "IRP_MN_QUERY_CAPABILITIES";
        case IRP_MN_QUERY_RESOURCES:
            return "IRP_MN_QUERY_RESOURCES";
        case IRP_MN_QUERY_RESOURCE_REQUIREMENTS:
            return "IRP_MN_QUERY_RESOURCE_REQUIREMENTS";
        case IRP_MN_QUERY_DEVICE_TEXT:
            return "IRP_MN_QUERY_DEVICE_TEXT";
        case IRP_MN_FILTER_RESOURCE_REQUIREMENTS:
            return "IRP_MN_FILTER_RESOURCE_REQUIREMENTS";
        case IRP_MN_READ_CONFIG:
            return "IRP_MN_READ_CONFIG";
        case IRP_MN_WRITE_CONFIG:
            return "IRP_MN_WRITE_CONFIG";
        case IRP_MN_EJECT:
            return "IRP_MN_EJECT";
        case IRP_MN_SET_LOCK:
            return "IRP_MN_SET_LOCK";
        case IRP_MN_QUERY_ID:
            return "IRP_MN_QUERY_ID";
        case IRP_MN_QUERY_PNP_DEVICE_STATE:
            return "IRP_MN_QUERY_PNP_DEVICE_STATE";
        case IRP_MN_QUERY_BUS_INFORMATION:
            return "IRP_MN_QUERY_BUS_INFORMATION";
        case IRP_MN_DEVICE_USAGE_NOTIFICATION:
            return "IRP_MN_DEVICE_USAGE_NOTIFICATION";
        case IRP_MN_SURPRISE_REMOVAL:
            return "IRP_MN_SURPRISE_REMOVAL";
            
        default:
            return "IRP_MN_?????";
    }
}

#endif

NTSTATUS
FilterCreate(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
{
	NTSTATUS			status;
    PDEVICE_EXTENSION	deviceExtension; 

	DebugPrint(("+ Enter FilterCreate routine\n"));
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
 	status = STATUS_SUCCESS;
	IoSkipCurrentIrpStackLocation (Irp);
	status = IoCallDriver (deviceExtension->NextLowerDriver, Irp);
	DebugPrint(("- Exit FilterCreate routine\n"));
	return status;
}
NTSTATUS
FilterClose(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
{
	NTSTATUS			status;
    PDEVICE_EXTENSION	deviceExtension; 

	DebugPrint(("+ Enter FilterClose routine\n"));
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
 	status = STATUS_SUCCESS;
	IoSkipCurrentIrpStackLocation (Irp);
	status = IoCallDriver (deviceExtension->NextLowerDriver, Irp);
	DebugPrint(("- Exit FilterClose routine\n"));
	return status;
}
NTSTATUS
FilterCleanup(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
{
	NTSTATUS			status;
    PDEVICE_EXTENSION	deviceExtension; 

	DebugPrint(("+ Enter FilterCleanup routine\n"));
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
 	status = STATUS_SUCCESS;
	IoSkipCurrentIrpStackLocation (Irp);
	status = IoCallDriver (deviceExtension->NextLowerDriver, Irp);
	DebugPrint(("- Exit FilterCleanup routine\n"));
	return status;
}
NTSTATUS
FilterIoControl(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
{
	NTSTATUS			status;
	DebugPrint(("+ Enter FilterIoControl routine\n"));
	status = FilterCommonRoutine( DeviceObject, Irp );
	DebugPrint(("- Exit FilterIoControl routine\n\n"));
	return status;
}
VOID
PrintIoControlCode(
	IN ULONG	IoControlCode
	)
{
	switch( IoControlCode ){
	case	IOCTL_SERIAL_SET_BAUD_RATE      :
		DebugPrint(("---  IOCTL_SERIAL_SET_BAUD_RATE ---\n"));
		break;
	case	IOCTL_SERIAL_SET_QUEUE_SIZE     :
		DebugPrint(("---  IOCTL_SERIAL_SET_QUEUE_SIZE ---\n"));
		break;
	case	IOCTL_SERIAL_SET_LINE_CONTROL   :
		DebugPrint(("---  IOCTL_SERIAL_SET_LINE_CONTROL ---\n"));
		break;
	case	IOCTL_SERIAL_SET_BREAK_ON       :
		DebugPrint(("---  IOCTL_SERIAL_SET_BREAK_ON ---\n"));
		break;
	case	IOCTL_SERIAL_SET_BREAK_OFF      :
		DebugPrint(("---  IOCTL_SERIAL_SET_BREAK_OFF ---\n"));
		break;
	case	IOCTL_SERIAL_IMMEDIATE_CHAR     :
		DebugPrint(("---  IOCTL_SERIAL_IMMEDIATE_CHAR ---\n"));
		break;
	case	IOCTL_SERIAL_SET_TIMEOUTS       :
		DebugPrint(("---  IOCTL_SERIAL_SET_TIMEOUTS ---\n"));
		break;
	case	IOCTL_SERIAL_GET_TIMEOUTS       :
		DebugPrint(("---  IOCTL_SERIAL_GET_TIMEOUTS ---\n"));
		break;
	case	IOCTL_SERIAL_SET_DTR            :
		DebugPrint(("---  IOCTL_SERIAL_SET_DTR ---\n"));
		break;
	case	IOCTL_SERIAL_CLR_DTR            :
		DebugPrint(("---  IOCTL_SERIAL_CLR_DTR ---\n"));
		break;
	case	IOCTL_SERIAL_RESET_DEVICE       :
		DebugPrint(("---  IOCTL_SERIAL_RESET_DEVICE ---\n"));
		break;
	case	IOCTL_SERIAL_SET_RTS            :
		DebugPrint(("---  IOCTL_SERIAL_SET_RTS ---\n"));
		break;
	case	IOCTL_SERIAL_CLR_RTS            :
		DebugPrint(("---  IOCTL_SERIAL_CLR_RTS ---\n"));
		break;
	case	IOCTL_SERIAL_SET_XOFF           :
		DebugPrint(("---  IOCTL_SERIAL_SET_XOFF ---\n"));
		break;
	case	IOCTL_SERIAL_SET_XON            :
		DebugPrint(("---  IOCTL_SERIAL_SET_XON ---\n"));
		break;
	case	IOCTL_SERIAL_GET_WAIT_MASK      :
		DebugPrint(("---  IOCTL_SERIAL_GET_WAIT_MASK ---\n"));
		break;
	case	IOCTL_SERIAL_SET_WAIT_MASK      :
		DebugPrint(("---  IOCTL_SERIAL_SET_WAIT_MASK ---\n"));
		break;
	case	IOCTL_SERIAL_WAIT_ON_MASK       :
		DebugPrint(("---  IOCTL_SERIAL_WAIT_ON_MASK ---\n"));
		break;
	case	IOCTL_SERIAL_PURGE              :
		DebugPrint(("---  IOCTL_SERIAL_PURGE ---\n"));
		break;
	case	IOCTL_SERIAL_GET_BAUD_RATE      :
		DebugPrint(("---  IOCTL_SERIAL_GET_BAUD_RATE ---\n"));
		break;
	case	IOCTL_SERIAL_GET_LINE_CONTROL   :
		DebugPrint(("---  IOCTL_SERIAL_GET_LINE_CONTROL ---\n"));
		break;
	case	IOCTL_SERIAL_GET_CHARS          :
		DebugPrint(("---  IOCTL_SERIAL_GET_CHARS ---\n"));
		break;
	case	IOCTL_SERIAL_SET_CHARS          :
		DebugPrint(("---  IOCTL_SERIAL_SET_CHARS ---\n"));
		break;
	case	IOCTL_SERIAL_GET_HANDFLOW       :
		DebugPrint(("---  IOCTL_SERIAL_GET_HANDFLOW ---\n"));
		break;
	case	IOCTL_SERIAL_SET_HANDFLOW       :
		DebugPrint(("---  IOCTL_SERIAL_SET_HANDFLOW ---\n"));
		break;
	case	IOCTL_SERIAL_GET_MODEMSTATUS    :
		DebugPrint(("---  IOCTL_SERIAL_GET_MODEMSTATUS ---\n"));
		break;
	case	IOCTL_SERIAL_GET_COMMSTATUS     :
		DebugPrint(("---  IOCTL_SERIAL_GET_COMMSTATUS ---\n"));
		break;
	case	IOCTL_SERIAL_XOFF_COUNTER       :
		DebugPrint(("---  IOCTL_SERIAL_XOFF_COUNTER ---\n"));
		break;
	case	IOCTL_SERIAL_GET_PROPERTIES     :
		DebugPrint(("---  IOCTL_SERIAL_GET_PROPERTIES ---\n"));
		break;
	case	IOCTL_SERIAL_GET_DTRRTS         :
		DebugPrint(("---  IOCTL_SERIAL_GET_DTRRTS ---\n"));
		break;
	default:
		DebugPrint(("--- Default  ---\n"));
		break;
	}
	return;
}

NTSTATUS
FilterRead(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
{
	NTSTATUS			status;
	DebugPrint(("+  Enter Filter Read routine\n"));
	status = FilterCommonRoutine( DeviceObject, Irp );
	DebugPrint(("-  Exit Filter Read routine\n\n"));
	return status;
}
NTSTATUS
FilterWrite(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
{
	NTSTATUS			status;
	DebugPrint(("+  Enter Filter Write routine\n"));
	status = FilterCommonRoutine( DeviceObject, Irp );
	DebugPrint(("-  Exit Filter Write routine\n\n"));
	return status;
}

NTSTATUS
FilterCommonRoutine(
	IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    )
{
	NTSTATUS			status;
    PDEVICE_EXTENSION	deviceExtension; 
	PIO_STACK_LOCATION IrpStack;
	ULONG				ControlCode;
	ULONG				InputLength,OutputLength;
	PUCHAR				buf;
	ULONG				i;
	KEVENT				event;
	BOOLEAN				bIsIoControl;
	
	IrpStack=IoGetCurrentIrpStackLocation(Irp);
	InputLength = OutputLength = 0;
    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
 	status = STATUS_SUCCESS;
	bIsIoControl = FALSE;

	switch( IrpStack->MajorFunction ){
	case IRP_MJ_READ:
		OutputLength = IrpStack->Parameters.Read.Length;
		break;
	case IRP_MJ_WRITE:
		InputLength = IrpStack->Parameters.Write.Length;
		break;
	case IRP_MJ_DEVICE_CONTROL:
		ControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
		InputLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
		OutputLength= IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
		PrintIoControlCode( ControlCode );
		bIsIoControl = TRUE;
		DebugPrint(("IoControl code:  %d\n", ControlCode ));
		break;
	default:
		DebugPrint(("---   Unkown MajorFunction  ---\n"));
		break;
	}
	DbgPrint("InputBufferLength:  %d     OutputBufferLength:   %d   Irp:   0x%x\n", InputLength, OutputLength, Irp );
	
	buf = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;
	if( InputLength > 0 ){
		DebugPrint(("Input Buf (%x):\n", buf));
		for( i = 0; i < InputLength; i++)
		{
			DbgPrint("%2x ", buf[ i ] );
		}
		DbgPrint("\n");
	}
	IoCopyCurrentIrpStackLocationToNext( Irp );
	KeInitializeEvent(&event, NotificationEvent, FALSE );
	IoSetCompletionRoutine( Irp, (PIO_COMPLETION_ROUTINE) FilterReturnRoutine, &event, TRUE, TRUE, TRUE );
	status = IoCallDriver (deviceExtension->NextLowerDriver, Irp);
	return status;
/*
	if( status == STATUS_PENDING ){
		KeWaitForSingleObject(
               &event,
               Executive, // Waiting for reason of a driver
               KernelMode, // Waiting in kernel mode
               FALSE, // No alert
               NULL); // No timeout
	}
	if( bIsIoControl ){
		DebugPrint(("IoControl code: %d\n", ControlCode ));
	}
	if( OutputLength > 0 ){
		buf = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;
		DebugPrint(("Output Buf (%x):\n", buf));
		for( i = 0; i < OutputLength; i++){
			DbgPrint("%2x ", buf[ i ] );
		}
		DbgPrint("\n");
	}
	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
*/
}
NTSTATUS
FilterReturnRoutine(
    IN PDEVICE_OBJECT   DeviceObject,
    IN PIRP             Irp,
    IN PVOID            Context
    )
{
	NTSTATUS	status;
	PUCHAR				buf;
	ULONG			info;
	ULONG			i;
    UNREFERENCED_PARAMETER(DeviceObject);

    if (Irp->PendingReturned) {
        IoMarkIrpPending(Irp);
    }

	DebugPrint(("+  Enter Completion routine...\nCompletionRoutine:  Irp:  0x%x\n", Irp ));
	info = Irp->IoStatus.Information;
	buf = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;
	DbgPrint("info:  %d\nreturn buffer(0x%x):\n", info, buf );
	for( i = 0; i < info; i++)
	{
		DbgPrint("%2x ", buf[ i ] );
	}
	DbgPrint("\n");
	DebugPrint(("-  Exit Completion routine...\n"));
	status = Irp->IoStatus.Status;
	return status;
}
