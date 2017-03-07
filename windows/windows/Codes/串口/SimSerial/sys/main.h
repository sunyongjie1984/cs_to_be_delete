/*++

Copyright (c) 1990-98    Microsoft Corporation All Rights Reserved

Module Name:

    filter.h

Abstract:

    Device driver that controls the Filter device.

Environment:

    Kernel mode

Revision History:

    Eliyas Yakub Oct 29 1998

--*/
#if !defined(_FILTER_H_)
#define _FILTER_H_

#include <ntddser.h>

#define DRIVERNAME "Serial.sys: "


#if DBG
#define DebugPrint(_x_) \
               DbgPrint (DRIVERNAME); \
               DbgPrint _x_;

#define TRAP() DbgBreakPoint()

#else
#define DebugPrint(_x_)
#define TRAP()
#endif

//
// These are the states Filter transition to upon
// receiving a specific PnP Irp. Refer to the PnP Device States
// diagram in DDK documentation for better understanding.
//

typedef enum _DEVICE_PNP_STATE {

    NotStarted = 0,         // Not started yet
    Started,                // Device has received the START_DEVICE IRP
    StopPending,            // Device has received the QUERY_STOP IRP
    Stopped,                // Device has received the STOP_DEVICE IRP
    RemovePending,          // Device has received the QUERY_REMOVE IRP
    SurpriseRemovePending,  // Device has received the SURPRISE_REMOVE IRP
    Deleted                 // Device has received the REMOVE_DEVICE IRP

} DEVICE_PNP_STATE;

#define INITIALIZE_PNP_STATE(_Data_)    \
        (_Data_)->DevicePnPState =  NotStarted;\
        (_Data_)->PreviousPnPState = NotStarted;

#define SET_NEW_PNP_STATE(_Data_, _state_) \
        (_Data_)->PreviousPnPState =  (_Data_)->DevicePnPState;\
        (_Data_)->DevicePnPState = (_state_);

#define RESTORE_PREVIOUS_PNP_STATE(_Data_)   \
        (_Data_)->DevicePnPState =   (_Data_)->PreviousPnPState;\


// for Virtual serial
#define DEVICE_OBJECT_NAME_LENGTH	128
#define SYMBOLIC_NAME_LENGTH		128
#define SERIAL_DEVICE_MAP			L"SERIALCOMM"
#define DEVICE_NAME					L"\\Device\\SiSerial"
#define DOS_DEVICE_NAME				L"\\DosDevices\\COM"
#define MAX_NUM_DEV					256
#define INVALID_INSTANCE			0xFFFFFFFF
#define MAX_PACKET_NUM				8
#define PACKET_SIZE					1024


//DEFINE_GUID(GUID_CLASS_COMPORT,          0x86e0d1e0L, 0x8089, 0x11d0, 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73);

//++	Serial section
// These defines are used to set the line control register.
#define SERIAL_5_DATA       ((UCHAR)0x00)
#define SERIAL_6_DATA       ((UCHAR)0x01)
#define SERIAL_7_DATA       ((UCHAR)0x02)
#define SERIAL_8_DATA       ((UCHAR)0x03)
#define SERIAL_DATA_MASK    ((UCHAR)0x03)

#define SERIAL_1_STOP       ((UCHAR)0x00)
#define SERIAL_1_5_STOP     ((UCHAR)0x04) // Only valid for 5 data bits
#define SERIAL_2_STOP       ((UCHAR)0x04) // Not valid for 5 data bits
#define SERIAL_STOP_MASK    ((UCHAR)0x04)

#define SERIAL_NONE_PARITY  ((UCHAR)0x00)
#define SERIAL_ODD_PARITY   ((UCHAR)0x08)
#define SERIAL_EVEN_PARITY  ((UCHAR)0x18)
#define SERIAL_MARK_PARITY  ((UCHAR)0x28)
#define SERIAL_SPACE_PARITY ((UCHAR)0x38)
#define SERIAL_PARITY_MASK  ((UCHAR)0x38)
//--
//++	default xon/xoff characters
#define SERIAL_DEF_XON 0x11
#define SERIAL_DEF_XOFF 0x13
//--

typedef struct _DEVICE_EXTENSION
{
    //
    // A back pointer to the device object.
    //
    
    PDEVICE_OBJECT  Self;

	//PDRIVER_OBJECT  DriverObject;

    //
    // The top of the stack before this filter was added.
    //
	PDEVICE_OBJECT	PhysicalDeviceObject;
    
    PDEVICE_OBJECT  NextLowerDriver;

    //
    // current PnP state of the device
    //
    
    DEVICE_PNP_STATE  DevicePnPState;

    //
    // Remembers the previous pnp state
    //
    
    DEVICE_PNP_STATE    PreviousPnPState;


	//++ names aboug device object
    UNICODE_STRING      InterfaceName; // The name returned from 
                                       // IoRegisterDeviceInterface,
	UNICODE_STRING		DeviceName;

	UNICODE_STRING		SymbolicLinkName;
	BOOLEAN				CreatedSymbolicLink;

	UNICODE_STRING		DosName;
	BOOLEAN				CreatedSerialCommEntry;

	ULONG				ComX;
	ULONG				localInstance;
	ULONG				remoteInstance;
	//--
	
	DEVICE_POWER_STATE	PowerState;

	BOOLEAN				bIsOpen;

	BOOLEAN				bIsConnected;


	//++	settings for Serial Ports
	KSPIN_LOCK			CancelSpinLock;

	LIST_ENTRY			ReadIrpQueue;
	LIST_ENTRY			WriteIrpQueue;
	PIRP				WaitOnMaskIrp;
	LIST_ENTRY			ReadDataQueue;
	KSPIN_LOCK			ReadQueueSpinLock;

	ULONG				CurrentBaud;
	ULONG				BufferSize;
	ULONG				WaitMask;
	BOOLEAN				bIsWaitOnMask;
    SERIAL_CHARS		SpecialChars;
    SERIAL_HANDFLOW		HandFlow;
	SERIAL_TIMEOUTS		Timeouts;
	SERIAL_LINE_CONTROL	LineControl;

	//--

} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

typedef struct _Device_Description{
	PDEVICE_EXTENSION  deviceExtension;
}DEVICE_ARRAY, *PDEVICE_ARRAY;

typedef struct _Packet{
	ULONG		nTotalNum;
	ULONG		nReadBytes;
	LIST_ENTRY	ListEntry;
	UCHAR		Buffer[ PACKET_SIZE ];
}PACKET,*PPACKET;
PCHAR
PnPMinorFunctionString (
    UCHAR MinorFunction
);

NTSTATUS
AddDevice(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT PhysicalDeviceObject
    );


NTSTATUS
DispatchPnp (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
DispatchPower(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );

VOID
Unload(
    IN PDRIVER_OBJECT DriverObject
    );
NTSTATUS DefaultPnpHandler(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);

NTSTATUS PnpStartDevice(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);
NTSTATUS PnpRemoveDevice(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);
NTSTATUS ForwardAndWait(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);
NTSTATUS RequestCreate (
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);

NTSTATUS RequestClose(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);

NTSTATUS RequestControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);

NTSTATUS CompleteRequest ( 
	IN PIRP Irp,
	IN NTSTATUS status,
	IN ULONG info
	);
NTSTATUS OnRequestComplete(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp,
    IN PKEVENT event
	);

NTSTATUS
SerialCreateDevObj(
	IN PDRIVER_OBJECT DriverObject,
	OUT PDEVICE_OBJECT *NewDeviceObject
	);
NTSTATUS
SerialRemoveDevObj(
	IN PDEVICE_OBJECT DeviceObject
	);

NTSTATUS
SerialFinishStartDevice(
	IN	PDEVICE_EXTENSION	deviceExtension
	);

NTSTATUS
DispatchRead(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);

NTSTATUS
DispatchWrite(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);

BOOLEAN
RequestCancelRoutine(
	IN PLIST_ENTRY		QueueToProcess,
	IN PKSPIN_LOCK		CancelSpinLock,
	IN PIRP				Irp
	);
NTSTATUS
RequestCleanup(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
	);
VOID
RequestPurgeIrpQueue(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PLIST_ENTRY		QueueToProcess
	);
VOID
RequestCancelReadRoutine(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PIRP				Irp
	);
VOID
RequestCancelWriteRoutine(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PIRP				Irp
	);
VOID
RequestCancelMaskRoutine(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PIRP				Irp
	);
VOID
OnTimer(
    IN PDEVICE_OBJECT DeviceObject,
    IN PVOID Context
    );
VOID
CompleteReadIrpOnTimer(
	IN PDEVICE_EXTENSION	deviceExtension,
	IN PIRP					Irp
	);

NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    );
NTSTATUS
SerialDoExternalNaming(
	IN PDEVICE_EXTENSION	deviceExtension,
	IN LONG					ComX
	);
NTSTATUS
SerialUndoExternalNaming(
	IN PDEVICE_EXTENSION	deviceExtension
	);
NTSTATUS
AddInterface(
	IN	PDEVICE_EXTENSION	deviceExtension
	);
VOID
DelInterface(
	IN	PDEVICE_EXTENSION	deviceExtension
	);
NTSTATUS Disconnect(	IN PDEVICE_EXTENSION deviceExtension );
VOID
RequestPurgeDataQueue(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PLIST_ENTRY		QueueToProcess
	);
NTSTATUS
CompleteReadIrp(
	IN PDEVICE_EXTENSION	deviceExtension,
	IN PIRP					Irp
	);
#endif
