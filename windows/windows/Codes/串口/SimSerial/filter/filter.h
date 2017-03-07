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

#define DRIVERNAME "filter.sys: "

#if BUS_LOWER

#undef DRIVERNAME
#define DRIVERNAME "BFdoLwr.sys: "

#endif

#if BUS_UPPER

#undef DRIVERNAME
#define DRIVERNAME "BFdoUpr.sys: "

#endif

#if DEVICE_LOWER

#undef DRIVERNAME
#define DRIVERNAME "DevLower.sys: "

#endif

#if DEVICE_UPPER

#undef DRIVERNAME
#define DRIVERNAME "DevUpper.sys: "

#endif

#if CLASS_LOWER

#undef DRIVERNAME
#define DRIVERNAME "ClsLower.sys: "

#endif

#if CLASS_UPPER

#undef DRIVERNAME
#define DRIVERNAME "ClsUpper.sys: "

#endif

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


typedef struct _DEVICE_EXTENSION
{
    //
    // A back pointer to the device object.
    //
    
    PDEVICE_OBJECT  Self;

    //
    // The top of the stack before this filter was added.
    //
    
    PDEVICE_OBJECT  NextLowerDriver;

    //
    // current PnP state of the device
    //
    
    DEVICE_PNP_STATE  DevicePnPState;

    //
    // Remembers the previous pnp state
    //
    
    DEVICE_PNP_STATE    PreviousPnPState;

} DEVICE_EXTENSION, *PDEVICE_EXTENSION;


PCHAR
PnPMinorFunctionString (
    UCHAR MinorFunction
);

NTSTATUS
FilterAddDevice(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT PhysicalDeviceObject
    );


NTSTATUS
FilterDispatchPnp (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );

NTSTATUS
FilterDispatchPower(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );

VOID
FilterUnload(
    IN PDRIVER_OBJECT DriverObject
    );
    
NTSTATUS
FilterPass (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    );
NTSTATUS
FilterIoControl(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );
NTSTATUS
FilterCleanup(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );
NTSTATUS
FilterClose(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );
NTSTATUS
FilterCreate(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );
VOID
PrintIoControlCode(
	IN ULONG	IoControlCode
	);
NTSTATUS
FilterRead(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );
NTSTATUS
FilterWrite(
    IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );
NTSTATUS
FilterCommonRoutine(
	IN PDEVICE_OBJECT    DeviceObject,
    IN PIRP              Irp
    );
NTSTATUS
FilterReturnRoutine(
    IN PDEVICE_OBJECT   DeviceObject,
    IN PIRP             Irp,
    IN PVOID            Context
    );
NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    );

#endif
