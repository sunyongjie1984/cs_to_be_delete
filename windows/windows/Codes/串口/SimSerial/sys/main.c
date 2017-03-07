
/*++

Copyright (c) 1990-2000  Changzhi Zhou All Rights Reserved

Module Name:

    main.c

Abstract:

	This module contains the entry points  for a virtual serial driver

Author

	Changzhi Zhou	Jul 25, 2003

Environment:

    Kernel mode

Revision History:

    Changzhi Zhou Dec 5 2003

--*/
#include <ntddk.h>
#include <initguid.h>
#include <stdio.h>

#include "main.h"
#include "..\inc\wdmioctl.h"


#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, AddDevice)
#pragma alloc_text (PAGE, DispatchPower)
#pragma alloc_text (PAGE, Unload)
#endif


DEVICE_ARRAY	gDeviceArray[ MAX_NUM_DEV ];
KSPIN_LOCK		gSpinLock;
PACKET			gPacketPool[ MAX_PACKET_NUM ];
LIST_ENTRY		gIdleQueue;
KSPIN_LOCK		gPoolSpinLock;



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
    //ULONG               ulIndex;
	ULONG				i;
    PDRIVER_DISPATCH  * dispatch;

    UNREFERENCED_PARAMETER (RegistryPath);

    DebugPrint (("-----------  Virtual Serial Device Build on %s %s  ----------\n", __DATE__, __TIME__ ));
    

    //
    // Create dispatch points
    //
	/*
    for (ulIndex = 0, dispatch = DriverObject->MajorFunction;
         ulIndex <= IRP_MJ_MAXIMUM_FUNCTION;
         ulIndex++, dispatch++) {

        *dispatch = DefaultPnpHandler;
    }
	*/

    DriverObject->MajorFunction[IRP_MJ_PNP]				= DispatchPnp;
    DriverObject->MajorFunction[IRP_MJ_POWER]			= DispatchPower;
    DriverObject->MajorFunction[IRP_MJ_CREATE]			= RequestCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE]			= RequestClose;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP ]		= RequestCleanup;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]	= RequestControl;

    DriverObject->MajorFunction[IRP_MJ_READ]			= DispatchRead;
    DriverObject->MajorFunction[IRP_MJ_WRITE]			= DispatchWrite;

    DriverObject->DriverExtension->AddDevice			= AddDevice;
    DriverObject->DriverUnload							= Unload;

	// Initialize global varible
	RtlZeroMemory( gDeviceArray, sizeof( DEVICE_ARRAY ) * MAX_NUM_DEV );
	KeInitializeSpinLock( &gSpinLock );
	RtlZeroMemory( gPacketPool, sizeof( PACKET ) * MAX_PACKET_NUM );
	InitializeListHead( &gIdleQueue );
	KeInitializeSpinLock( &gPoolSpinLock );

	for( i = 0; i < MAX_PACKET_NUM; i++)
	{
		InsertTailList( &gIdleQueue, &(gPacketPool[ i ].ListEntry) );
	}

    return status;
}


NTSTATUS
AddDevice(
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
    // Create a device object.
    //
	status = SerialCreateDevObj(DriverObject, &deviceObject);
    
    if (!NT_SUCCESS (status)) {
        //
        // Returning failure here prevents the entire stack from functioning,
        // but most likely the rest of the stack will not be able to create
        // device objects either, so it is still OK.
        //
		DebugPrint(("SerialCreateDevice failed with status %d\n", status ));
        return status;
    }

    DebugPrint (("AddDevice PDO (0x%x) FDO (0x%x)\n", PhysicalDeviceObject, deviceObject));

    deviceExtension = (PDEVICE_EXTENSION) deviceObject->DeviceExtension;

	deviceExtension->PhysicalDeviceObject = PhysicalDeviceObject;
  
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

    INITIALIZE_PNP_STATE(deviceExtension);

 
    DebugPrint(("AddDevice: %x to %x->%x \n", deviceObject, 
                       deviceExtension->NextLowerDriver,
                       PhysicalDeviceObject));
	if( !NT_SUCCESS ( status ) ){
		DebugPrint(( "AddDevice:  IoRegisterDeviceInterface failed (%x) \n", status ));
		IoDetachDevice( deviceExtension->NextLowerDriver );
		gDeviceArray[ deviceExtension->localInstance ].deviceExtension = NULL;
		IoDeleteDevice( deviceObject );
		return status;
	}
	deviceObject->Flags |= ( DO_BUFFERED_IO | DO_POWER_PAGABLE );
    deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    return STATUS_SUCCESS;

}
#if 0
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
#endif

NTSTATUS
DispatchPower(
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
	NTSTATUS	status;
    PDEVICE_EXTENSION   deviceExtension;
    
    PAGED_CODE ();

	DebugPrint(("Enter DispatchPower routine...\n"));

    deviceExtension = (PDEVICE_EXTENSION) DeviceObject->DeviceExtension;
    PoStartNextPowerIrp(Irp);
    IoSkipCurrentIrpStackLocation(Irp);
	DebugPrint(("NextLowerDriver:  0x%x\n", deviceExtension->NextLowerDriver ));
	status = PoCallDriver(deviceExtension->NextLowerDriver, Irp);

	DebugPrint(("-Exit Power\n") );
    return status;
}


    
VOID
Unload(
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
	DebugPrint( ("Is unloading......\n") );
    ASSERT(DriverObject->DeviceObject == NULL);
    
    //
    // We should not be unloaded until all the devices we control 
    // have been removed from our queue.  
    //
    DebugPrint (("Unload:  unload\n"));

    return;
}


NTSTATUS RequestCreate(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
/*++

Routine Description:

    Create the device

Arguments:

	DeviceObject	- Pointer to deviceobject
	Irp				- Pointer to an IRP_MJ_CREATE

Return Value:

    NT Status is return.

--*/
{                           // RequestCreate
	NTSTATUS	status;
	PDEVICE_EXTENSION	deviceExtension;

    DbgPrint("Entering IRP_MJ_CREAT\n");
	status = STATUS_SUCCESS;
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;
	// 每一个设备同一时间只允许一个应用打开
	if( deviceExtension->bIsOpen ){
		status = STATUS_ACCESS_DENIED;
	}else{
		deviceExtension->bIsOpen = TRUE;
	}
	return CompleteRequest(Irp, status, 0);
}

NTSTATUS RequestClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
/*++

Routine Description:

    Close the device

Arguments:

	DeviceObject	- Pointer to deviceobject
	Irp				- Pointer to an IRP_MJ_CREATE

Return Value:

    NT Status is returned;

--*/
{                           // RequestClose
	NTSTATUS	status;
	PDEVICE_EXTENSION	deviceExtension;
    
	DbgPrint("Entering IRP_MJ_CLOSE\n");
	status = STATUS_SUCCESS;
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;
	if( deviceExtension->bIsOpen ){
		deviceExtension->bIsOpen = FALSE;
	}else{
		status = STATUS_ACCESS_DENIED;
	}
	return CompleteRequest(Irp, status, 0);
}

NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG info)
/*++

Routine Description:

    Routine to complete the requests

Arguments:

	Irp			- Pointer to an IRP_MJ_CREATE
	status		- NT status
	info		- Irp->IoStatus.Information

Return Value:

    NT Status is returned;

--*/

{                           // CompleteRequest
    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = info;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return status;
}                           // CompleteRequest


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
/*

  Note:
	Because we call IoSkipCurrentIrpStackLocation rather than IoCopyCurrentIrpStackLocation, we need NOT
	set Irp->IoStatus.Status and NOT call IoCompleteRequest. The only work is to call IoCallDriver.

*/
NTSTATUS DefaultPnpHandler(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	PDEVICE_EXTENSION	deviceExtension;
    IoSkipCurrentIrpStackLocation( Irp );
    deviceExtension = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
    return IoCallDriver( deviceExtension->NextLowerDriver, Irp);
}

NTSTATUS ForwardAndWait(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
/*++
Routine Description:

  The routine forwards the IRP to the underlying driver and waits for the lower layer to complete the IRP

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.

Return Value:

    NT Status is returned.

--*/
{
    KEVENT				event;
    NTSTATUS			status;
	PDEVICE_EXTENSION	deviceExtension;

	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;
    
	KeInitializeEvent(&event, NotificationEvent, FALSE);

    IoCopyCurrentIrpStackLocationToNext( Irp );

    IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) 
        OnRequestComplete, (PVOID) &event, TRUE, TRUE, TRUE);

	status = IoCallDriver( deviceExtension->NextLowerDriver, Irp);
    if (status == STATUS_PENDING)
    {                       // wait for completion
        KeWaitForSingleObject(
			&event,
			Executive,		//	Waiting for reasion of a driver
			KernelMode,		//	Waiting in kernel mode
			FALSE,			//	No alert
			NULL);			//	No timeout
        status = Irp->IoStatus.Status;
    }                       // wait for completion

    return status;
}                           // ForwardAndWait

NTSTATUS OnRequestComplete(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp, IN PKEVENT event)
/*++
Routine Description:
    A completion routine for use when calling the lower device objects to
    which ourdeviceobject is attached.

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.
	event		 - Pointer to event
Return Value:

    NT Status is returned.

--*/
{
    KeSetEvent( event, 0, FALSE);
    return STATUS_MORE_PROCESSING_REQUIRED;
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
NTSTATUS RequestCleanup(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	)
/*++
Routine Description:
	The routine handles the IRP_MJ_CLEANUP which is sent beforce the IRP_MJ_CLOSE.
Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.

Return Value:

    NT Status is returned.

--*/
{
	NTSTATUS	status;
	PDEVICE_EXTENSION	deviceExtension;
	PLIST_ENTRY			link;
	PIRP				pendingIrp;


	DbgPrint("Entering IRP_MJ_Cleanup\n");
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;
	status = STATUS_SUCCESS;

	DebugPrint(("to cleanup pending WaitOnMask IRP\n"));
	if( deviceExtension->bIsWaitOnMask ){
		CompleteRequest( deviceExtension->WaitOnMaskIrp, STATUS_CANCELLED, 0 );
		deviceExtension->WaitOnMaskIrp = NULL;
		deviceExtension->bIsWaitOnMask = FALSE;
	}

	DebugPrint(("to cleanup pending Read IRP\n"));
	RequestPurgeIrpQueue( DeviceObject, &deviceExtension->ReadIrpQueue );

	DebugPrint(("to cleanup pending Write IRP\n"));
	RequestPurgeIrpQueue( DeviceObject, &deviceExtension->WriteIrpQueue );

	return CompleteRequest( Irp, status, 0 );
}





#if 0
VOID
OnTimer(
    IN PDEVICE_OBJECT DeviceObject,
    IN PVOID Context
    )
{
	PDEVICE_EXTENSION	deviceExtension;
	PLIST_ENTRY			link;
	PIRP				IrpToComplete;

	deviceExtension = ( PDEVICE_EXTENSION )Context;
	if( deviceExtension->timer > 0 ){
		deviceExtension->timer--;
	}else{
		link = NULL;
		link = ExInterlockedRemoveHeadList( &deviceExtension->ReadIrpQueue, &deviceExtension->CancelSpinLock );
		while( link != NULL ){
			IrpToComplete = CONTAINING_RECORD( link, IRP, Tail.Overlay.ListEntry );
			ASSERT( IrpToComplete );
			DebugPrint(("Fing out pending ReadIrp (0x%x )\n", IrpToComplete ));
			CompleteReadIrpOnTimer(deviceExtension, IrpToComplete );
			link = ExInterlockedRemoveHeadList( &deviceExtension->ReadIrpQueue, &deviceExtension->CancelSpinLock );
		}
		deviceExtension->timer = 3;		
	}
}
VOID
CompleteReadIrpOnTimer(
	IN PDEVICE_EXTENSION	deviceExtension,
	IN PIRP					Irp
	)
{
	PIO_STACK_LOCATION IrpStack;
	ULONG				ControlCode;
	ULONG				InputLength,OutputLength;
	PUCHAR				pOutBuf;
	ULONG				info;
	ULONG				i;
	CHAR				buf[ 256 ];
	LARGE_INTEGER time;


	DebugPrint(("Enter ReadIrpOnTimer routine ( 0x%x )\n", Irp));
	IrpStack = IoGetCurrentIrpStackLocation(Irp);

	DebugPrint(("GetCurrentIrpStackLocation OK\n"));
	ControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	InputLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
	OutputLength= IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	DbgPrint("InputBufferLength:  %d     OutputBufferLength:   %d\n", InputLength, OutputLength );

	pOutBuf = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;

	KeQuerySystemTime(&time);
	sprintf( buf, "CurrentTime:  %10u-%10u\r\n", time.HighPart, time.LowPart );
	memcpy(pOutBuf, buf, ( (strlen( buf ) > OutputLength ) ? OutputLength : strlen( buf ) ) );
	info = (strlen( buf ) > OutputLength ) ? OutputLength : strlen( buf ) ;
	CompleteRequest( Irp, STATUS_SUCCESS, info );
	DebugPrint(("Exit ReadIrpOnTimer routine\n"));
}
#endif