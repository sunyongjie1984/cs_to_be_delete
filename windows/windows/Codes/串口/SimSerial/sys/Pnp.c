#include <ntddk.h>
#include <ntddser.h>

#include "main.h"
#include "..\inc\wdmioctl.h"


#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, DispatchPnp)
#endif


extern DEVICE_ARRAY	gDeviceArray[ MAX_NUM_DEV ];
extern KSPIN_LOCK		gSpinLock;

NTSTATUS
DispatchPnp (
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

    DebugPrint(("Sample %s IRP:0x%x \n", 
                PnPMinorFunctionString(irpStack->MinorFunction), Irp));

    status = STATUS_SUCCESS;
    
    switch (irpStack->MinorFunction) {
    case IRP_MN_START_DEVICE:

		status = PnpStartDevice( DeviceObject, Irp);
		return status;

    case IRP_MN_REMOVE_DEVICE:
		status = PnpRemoveDevice( DeviceObject, Irp );        
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
    return DefaultPnpHandler( DeviceObject, Irp );
}



NTSTATUS PnpStartDevice(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
    NTSTATUS			status;
	PDEVICE_EXTENSION	deviceExtension;
	PIO_STACK_LOCATION stack;

	deviceExtension = DeviceObject->DeviceExtension;
	status = ForwardAndWait( DeviceObject, Irp);
    if (!NT_SUCCESS(status))
        return CompleteRequest(Irp, status, Irp->IoStatus.Information);

	stack = IoGetCurrentIrpStackLocation( Irp );
	// TODO: other work to start the device in this layer driver

	status = SerialFinishStartDevice( deviceExtension );
	if( !NT_SUCCESS( status ) ){
		return CompleteRequest( Irp, status, 0 );
	}
	// 添加Interface，给win32 App提供访问接口
	status = AddInterface( deviceExtension );
	if( NT_SUCCESS( status ) && NT_SUCCESS( Irp->IoStatus.Status ) ){
		SET_NEW_PNP_STATE( deviceExtension, Started );
	}
    return CompleteRequest(Irp, status, 0);
}

NTSTATUS PnpRemoveDevice( IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
	NTSTATUS			status;
	PDEVICE_EXTENSION	deviceExtension;

	DebugPrint(("+Enter RemoveDevice routine\n" ));
	deviceExtension = DeviceObject->DeviceExtension;
	//  TODO: handle our remove work at first

	SerialUndoExternalNaming( deviceExtension );

	// 删除Interface
	DelInterface( deviceExtension );
	
	SerialRemoveDevObj( DeviceObject );

	// Pass down the IRP
	IoSkipCurrentIrpStackLocation( Irp );
	status = IoCallDriver( deviceExtension->NextLowerDriver, Irp );

	SET_NEW_PNP_STATE(deviceExtension, Deleted);
	DebugPrint( ("NextLowerDriver:  0x%x\n", deviceExtension->NextLowerDriver ));

	IoDetachDevice( deviceExtension->NextLowerDriver );
	gDeviceArray[ deviceExtension->localInstance ].deviceExtension = NULL;
	IoDeleteDevice( DeviceObject );
	DebugPrint(("-Exit RemoveDevice routine\n"));
	
	return status;
}



NTSTATUS
SerialCreateDevObj(
	IN PDRIVER_OBJECT DriverObject,
	OUT PDEVICE_OBJECT *NewDeviceObject
	)
{
	UNICODE_STRING		deviceObjName;
	UNICODE_STRING		instanceStr;
	PDEVICE_OBJECT		deviceObject = NULL;
	PDEVICE_EXTENSION	pDevExt;
	NTSTATUS			status = STATUS_SUCCESS;
	WCHAR				instanceNumberBuffer[20];
	ULONG				currentInstance;
	
	PAGED_CODE();
	
	DebugPrint(("Enter SerialCreateDevObj\n"));

	for( currentInstance = 0; currentInstance < MAX_NUM_DEV; currentInstance++){
		// find the first empty device description in gDeviceArray
		if( gDeviceArray[ currentInstance ].deviceExtension == NULL ){
			break;
		}
	}
	if( currentInstance == MAX_NUM_DEV ){
		DebugPrint(("There is no memory in gDeviceArray\n"));
		status = STATUS_INSUFFICIENT_RESOURCES;
		*NewDeviceObject = NULL;
		return status;
	}
	// 首先处理deviceObjName，这是一个核心态使用的设备名，形如"\\Device\\SiSerial0"
	// Zero out allocated memory pointers so we know if they must be freed
	RtlZeroMemory(&deviceObjName, sizeof(UNICODE_STRING));
	deviceObjName.MaximumLength = DEVICE_OBJECT_NAME_LENGTH * sizeof(WCHAR);
	deviceObjName.Buffer = ExAllocatePool(PagedPool, deviceObjName.MaximumLength + sizeof(WCHAR));
	if (deviceObjName.Buffer == NULL) {
		DebugPrint(("Couldn't allocate memory for device name\n"));
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	RtlZeroMemory( deviceObjName.Buffer, deviceObjName.MaximumLength + sizeof(WCHAR));
	// now, the size of deviceObjName.Buffer is (128 + 1)(WCHAR)
	RtlAppendUnicodeToString(&deviceObjName, DEVICE_NAME);	// L"\\Device\\SiSerial"

	// 处理deviceObjName的后缀序号
	RtlInitUnicodeString(&instanceStr, NULL);
	instanceStr.MaximumLength = sizeof(instanceNumberBuffer);
	instanceStr.Buffer = instanceNumberBuffer;	// 20 WCHAR
	RtlIntegerToUnicodeString( currentInstance, 10, &instanceStr);
	RtlAppendUnicodeStringToString( &deviceObjName, &instanceStr);
	DebugPrint(("DeviceName:\n"));
	DebugPrint(("----------- %ws\n", deviceObjName.Buffer ));
	
	//
	// Create the device object
	//
	status = IoCreateDevice(DriverObject, sizeof( DEVICE_EXTENSION ),
		&deviceObjName, FILE_DEVICE_SERIAL_PORT,
		FILE_DEVICE_SECURE_OPEN, TRUE, &deviceObject);
	if (!NT_SUCCESS(status)) {
		DebugPrint(("SerialAddDevice: Create device failed - %x \n", status ));
		goto SerialCreateDevObjError;
	}
	ASSERT(deviceObject != NULL);
	gDeviceArray[ currentInstance ].deviceExtension = deviceObject->DeviceExtension;
	pDevExt = deviceObject->DeviceExtension;

	//
	// The device object has a pointer to an area of non-paged
	// pool allocated for this device.  This will be the device
	// extension. Zero it out.
	//
	RtlZeroMemory( pDevExt, sizeof( DEVICE_EXTENSION ) );


	// 在DeviceExtension中保存deviceName
	pDevExt->DeviceName.Buffer =
		ExAllocatePool(PagedPool, deviceObjName.Length + sizeof(WCHAR));
	if (!pDevExt->DeviceName.Buffer) {
		DebugPrint(("SERIAL: Couldn't allocate memory for DeviceName\n"));
		status = STATUS_INSUFFICIENT_RESOURCES;
		goto SerialCreateDevObjError;
	}
	pDevExt->DeviceName.MaximumLength = deviceObjName.Length + sizeof(WCHAR);
	// Zero fill it.
	RtlZeroMemory(pDevExt->DeviceName.Buffer, pDevExt->DeviceName.MaximumLength);
	RtlAppendUnicodeStringToString(&pDevExt->DeviceName, &deviceObjName);
	
	//++	Initialize common devExtension
	// 设置本设备的instance序号和与其相联接的设备序号（目前是没有连接，所以设为Invalid_Instance
	pDevExt->localInstance	= currentInstance;
	pDevExt->remoteInstance	= INVALID_INSTANCE;

	pDevExt->Self					= deviceObject;
	pDevExt->bIsOpen				= FALSE;
	pDevExt->PowerState				= PowerDeviceD0;
	pDevExt->CreatedSymbolicLink    = FALSE;
	pDevExt->CreatedSerialCommEntry	= FALSE;
	pDevExt->BufferSize				= 1024;

    //+	by zcz
    //deviceObject->DeviceType = deviceExtension->NextLowerDriver->DeviceType;

    //deviceObject->Characteristics = 
    //                      deviceExtension->NextLowerDriver->Characteristics;
	//---
	//++	Initialize serial section
	KeInitializeSpinLock( &pDevExt->CancelSpinLock );
	InitializeListHead( &pDevExt->ReadIrpQueue );
	InitializeListHead( &pDevExt->WriteIrpQueue );
	InitializeListHead( &pDevExt->ReadDataQueue );
	KeInitializeSpinLock( &pDevExt->ReadQueueSpinLock );
	//-

    //
    // Set the initial state of the Filter DO
    //
	*NewDeviceObject = deviceObject;
	
	ExFreePool(deviceObjName.Buffer);

	DebugPrint(("Leave SerialCreateDevObj\n") );

	return STATUS_SUCCESS;
	
SerialCreateDevObjError:
	
	DebugPrint(("SERIAL: SerialCreateDevObj Error, Cleaning up\n") );
	
	//
	// Free the allocated strings for the NT and symbolic names if they exist.
	//
	
	if (deviceObjName.Buffer != NULL) {
		ExFreePool(deviceObjName.Buffer);
	}
	
	if (deviceObject) {
		if (pDevExt->DeviceName.Buffer != NULL) {
			ExFreePool(pDevExt->DeviceName.Buffer);
		}
		gDeviceArray[ currentInstance ].deviceExtension = NULL;
		IoDeleteDevice(deviceObject);
	}
	
	*NewDeviceObject = NULL;
	
	DebugPrint(("SERIAL: Leave SerialCreateDevObj\n") );
	return status;
}


NTSTATUS
SerialRemoveDevObj(IN PDEVICE_OBJECT PDevObj)
/*++

Routine Description:

    Removes a serial device object from the system.

Arguments:

    PDevObj - A pointer to the Device Object we want removed.

Return Value:

    Always TRUE

--*/
{
	PDEVICE_EXTENSION pDevExt = (PDEVICE_EXTENSION)PDevObj->DeviceExtension;
	PAGED_CODE();
	
	DebugPrint(("SERIAL: Enter SerialRemoveDevObj\n"));
	
	
	//
	// Free memory allocated in the extension
	//
	
	if (pDevExt->DeviceName.Buffer != NULL) {
		ExFreePool(pDevExt->DeviceName.Buffer);
	}
	
	if (pDevExt->SymbolicLinkName.Buffer != NULL) {
		ExFreePool(pDevExt->SymbolicLinkName.Buffer);
	}
	
	if (pDevExt->DosName.Buffer != NULL) {
		ExFreePool(pDevExt->DosName.Buffer);
	}

	if( pDevExt->BufferSize != 0 ){
		pDevExt->BufferSize = 0;
	}
	
	DebugPrint(("SERIAL: Leave SerialRemoveDevObj\n"));
	
	return STATUS_SUCCESS;
}

NTSTATUS
SerialDoExternalNaming(
	IN PDEVICE_EXTENSION	deviceExtension,
	IN LONG					ComX
	)
{
	NTSTATUS		status;
	ULONG			bufLen;
	WCHAR			ComXBuffer[ 4 ];
	UNICODE_STRING	instanceStr;

	DebugPrint(("Enter SerialdoExternalNaming routine...\n"));
	if( deviceExtension->CreatedSymbolicLink || deviceExtension->CreatedSerialCommEntry ){
		DebugPrint(("Already create symboliclink or serial commentry\n"));
		return STATUS_UNSUCCESSFUL;
	}
	ASSERT( deviceExtension->SymbolicLinkName.Buffer == NULL );
	ASSERT( deviceExtension->DosName.Buffer == NULL );

	RtlInitUnicodeString(&instanceStr, NULL);
	instanceStr.MaximumLength = sizeof( ComXBuffer );
	instanceStr.Buffer = ComXBuffer;	// 4 WCHAR
	RtlIntegerToUnicodeString( ComX, 10, &instanceStr );

	// 将SymbolicLinkName设置为 \DosDevices\COMn 的形式。其中n = ComX
	RtlZeroMemory( &deviceExtension->SymbolicLinkName, sizeof( UNICODE_STRING ) );
	deviceExtension->SymbolicLinkName.MaximumLength = DEVICE_OBJECT_NAME_LENGTH + sizeof( WCHAR );
	deviceExtension->SymbolicLinkName.Buffer = ExAllocatePoolWithTag( PagedPool, deviceExtension->SymbolicLinkName.MaximumLength, 'SymL' );
	if( deviceExtension->SymbolicLinkName.Buffer == NULL ){
		DebugPrint(("SERIAL: Couldn't allocate memory for symbolic link name\n"));
		status = STATUS_INSUFFICIENT_RESOURCES;
		goto SerialDoExternalNamingError;
	}
	RtlZeroMemory( deviceExtension->SymbolicLinkName.Buffer, deviceExtension->SymbolicLinkName.MaximumLength );
	RtlAppendUnicodeToString( &deviceExtension->SymbolicLinkName, DOS_DEVICE_NAME );	//L"\\DosDevices\\COM"
	RtlAppendUnicodeStringToString( &deviceExtension->SymbolicLinkName, &instanceStr);
	DebugPrint(("SymbolicLinkName:   %wZ\n",  deviceExtension->SymbolicLinkName ));

	// 将DosName初始化 COMn 的形式， 其中 n = ComX
	deviceExtension->DosName.MaximumLength = 64 + sizeof(WCHAR);
	deviceExtension->DosName.Buffer = ExAllocatePoolWithTag( PagedPool, 64 + sizeof( WCHAR ), 'Name' );
	if( deviceExtension->DosName.Buffer == NULL ){
		DebugPrint(("SERIAL: Couldn't allocate memory for Dos name\n"));
		status =  STATUS_INSUFFICIENT_RESOURCES;
		goto SerialDoExternalNamingError;
	}
	deviceExtension->DosName.Length = 0;
	RtlZeroMemory( deviceExtension->DosName.Buffer, deviceExtension->DosName.MaximumLength );
	RtlAppendUnicodeToString( &deviceExtension->DosName, L"COM" );
	RtlAppendUnicodeStringToString( &deviceExtension->DosName, &instanceStr);
	DebugPrint(("DosName:   %wZ\n", &deviceExtension->DosName ));
	DebugPrint(("DeviceName:    %wZ\n", &deviceExtension->DeviceName ));

	// 生成符号连接，至此本设备对win32应用表现的Dos设备名为 \DosDevices\COMn
	status = IoCreateSymbolicLink( &deviceExtension->SymbolicLinkName, &deviceExtension->DeviceName );
	if( !NT_SUCCESS( status )){
		DebugPrint(("SERIAL:  Couldn't create the symbolic link with error %d\n", status));
		goto SerialDoExternalNamingError;
	}else{
		DebugPrint(("Create the symbolic link OK\n"));
		deviceExtension->CreatedSymbolicLink = TRUE;
	}
	// 在注册表的 HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM 中，添加ComX的键值
	// 若不进行这一步，则超级终端程序无法检测到本虚拟串口设备
	status = RtlWriteRegistryValue(RTL_REGISTRY_DEVICEMAP, SERIAL_DEVICE_MAP,
		deviceExtension->DeviceName.Buffer, REG_SZ,
		deviceExtension->DosName.Buffer,
		deviceExtension->DosName.Length + sizeof(WCHAR));
	if( !NT_SUCCESS( status )){
		DebugPrint(("SERIAL: Couldn't create the device map entry\n------- for port %wZ\n", deviceExtension->DeviceName ));
		goto SerialDoExternalNamingError;
	}
	deviceExtension->ComX = ComX;
	deviceExtension->CreatedSerialCommEntry = TRUE;

SerialDoExternalNamingError:

	if( !NT_SUCCESS( status )){
		if( deviceExtension->DosName.Buffer != NULL ){
			ExFreePool( deviceExtension->DosName.Buffer );
			deviceExtension->DosName.Buffer = NULL;
			deviceExtension->CreatedSerialCommEntry = FALSE;
		}
		if( deviceExtension->CreatedSymbolicLink ){
			IoDeleteSymbolicLink( &deviceExtension->SymbolicLinkName );
			deviceExtension->CreatedSymbolicLink = FALSE;
		}
		if( deviceExtension->SymbolicLinkName.Buffer != NULL ){
			ExFreePool( deviceExtension->SymbolicLinkName.Buffer );
			deviceExtension->SymbolicLinkName.Buffer = NULL;
		}
	}
	return status;
}

NTSTATUS
SerialUndoExternalNaming(
	IN PDEVICE_EXTENSION	deviceExtension
	)
{
	NTSTATUS	status = STATUS_SUCCESS;
	if( deviceExtension->CreatedSymbolicLink ){
		IoDeleteSymbolicLink( &deviceExtension->SymbolicLinkName );
		ExFreePool( deviceExtension->SymbolicLinkName.Buffer );
		deviceExtension->SymbolicLinkName.Buffer = NULL;
		deviceExtension->CreatedSymbolicLink = FALSE;
	}else{
		ASSERT( deviceExtension->SymbolicLinkName.Buffer == NULL );
	}
	ASSERT( deviceExtension->DeviceName.Buffer != NULL );
	if( deviceExtension->CreatedSerialCommEntry ){
		status = RtlDeleteRegistryValue( RTL_REGISTRY_DEVICEMAP, SERIAL_DEVICE_MAP, deviceExtension->DeviceName.Buffer );
		if( !NT_SUCCESS( status ) ){
			DebugPrint(("RtlDeleteRegistryValue device map failed\n"));
		}
		ExFreePool( deviceExtension->DosName.Buffer );
		deviceExtension->DosName.Buffer = NULL;
		deviceExtension->CreatedSerialCommEntry = FALSE;
	}else{
		ASSERT( deviceExtension->DosName.Buffer == NULL );
	}
	return status;
}

NTSTATUS
SerialFinishStartDevice(
	IN	PDEVICE_EXTENSION	deviceExtension
	)
{
	// Default Line control protocol. 7E1
	//
	// Seven data bits.
	// Even parity.
	// 1 Stop bits.
	//
	//deviceExtension->LineControl = SERIAL_7_DATA | SERIAL_EVEN_PARITY | SERIAL_NONE_PARITY;
	deviceExtension->LineControl.WordLength = 8;
	deviceExtension->LineControl.Parity		= 0;
	deviceExtension->LineControl.StopBits	= 1;
	deviceExtension->CurrentBaud			= 1200;
	
	deviceExtension->SpecialChars.XonChar	= SERIAL_DEF_XON;
	deviceExtension->SpecialChars.XoffChar	= SERIAL_DEF_XOFF;
	deviceExtension->SpecialChars.EofChar	= 0;
	deviceExtension->SpecialChars.ErrorChar	= 0;
	deviceExtension->SpecialChars.BreakChar	= 0;
	deviceExtension->SpecialChars.EventChar	= 0;

	deviceExtension->HandFlow.ControlHandShake	= SERIAL_DTR_CONTROL;
	deviceExtension->HandFlow.FlowReplace		= SERIAL_DSR_SENSITIVITY;//SERIAL_RTS_CONTROL;
	deviceExtension->HandFlow.XonLimit			= 4096;
	deviceExtension->HandFlow.XoffLimit			= 1024;

	return STATUS_SUCCESS;
}
//++ Register device interface for win32app
NTSTATUS
AddInterface(
	IN	PDEVICE_EXTENSION	deviceExtension
	)
{
	NTSTATUS status;
	status = IoRegisterDeviceInterface( deviceExtension->PhysicalDeviceObject,
					(LPGUID)&GUID_CLASS_COMPORT,
					NULL,
					&deviceExtension->InterfaceName );
	if( !NT_SUCCESS( status )){
		DebugPrint(("SERIAL:  Couldn't register class association\n"));
		deviceExtension->InterfaceName.Buffer = NULL;
		return status;
	}
	status = IoSetDeviceInterfaceState( &deviceExtension->InterfaceName, TRUE );
	if( !NT_SUCCESS( status )){
		DebugPrint(("SERIAL: Couldn't set class association\n"));
	}
	return status;
}
VOID
DelInterface(
	IN	PDEVICE_EXTENSION	deviceExtension
	)
{
	NTSTATUS status;
	if( deviceExtension->InterfaceName.Buffer ){
		status = IoSetDeviceInterfaceState( &deviceExtension->InterfaceName, FALSE );
		if( !NT_SUCCESS( status )){
			DebugPrint(("SERIAL:  IoSetDeviceInterface failed\n"));
		}
		RtlFreeUnicodeString( &deviceExtension->InterfaceName );
	}
}