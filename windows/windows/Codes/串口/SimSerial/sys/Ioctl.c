#include <ntddk.h>
#include <ntddser.h>

#include "main.h"
#include "..\inc\wdmioctl.h"


#ifdef ALLOC_PRAGMA

#endif

extern DEVICE_ARRAY	gDeviceArray[ MAX_NUM_DEV ];
extern KSPIN_LOCK		gSpinLock;
extern KSPIN_LOCK		gPoolSpinLock;
extern LIST_ENTRY		gIdleQueue;

NTSTATUS RequestControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
/*++
Routine Description:

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.

Return Value:

    NT Status is returned.
--*/
{
	PIO_STACK_LOCATION IrpStack;
	ULONG				ControlCode;
	ULONG				InputLength,OutputLength;
	NTSTATUS			status;
	PDEVICE_EXTENSION	deviceExtension;
	ULONG				info;

	DebugPrint(("Enter IoControl routine\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;

	if( !deviceExtension->bIsOpen ){
		status = STATUS_INVALID_DEVICE_REQUEST;
		return CompleteRequest( Irp, status, 0 );
	}


	IrpStack=IoGetCurrentIrpStackLocation(Irp);
	
	ControlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	InputLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
	OutputLength= IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
	DbgPrint("InputBufferLength:  %d     OutputBufferLength:   %d\n", InputLength, OutputLength );
	
	status = STATUS_INVALID_DEVICE_REQUEST;
	info = 0;
	switch(ControlCode)
	{
		case IOCTL_GET_IDENTITIER:
			// 得到本驱动的ID，用来指明该设备是本驱动生成的虚拟串口设备
			DebugPrint(("-----  IOCTL_GET_IDENTITIER   ----\n"));
			if( IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof( ULONG ) ){
				status = STATUS_BUFFER_TOO_SMALL;
				break;
			}
			*( (PULONG)Irp->AssociatedIrp.SystemBuffer ) = VIRTUAL_SERIAL_DEVICE_ID;
			status=STATUS_SUCCESS;
			info = sizeof( ULONG );
			break;
		case IOCTL_GET_CURRENT_COMX:
			DebugPrint(("-----  IOCTL_GET_CURRENT_COMX   ----\n"));
			if( IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof( ULONG ) ){
				status = STATUS_BUFFER_TOO_SMALL;
				break;
			}
			if( deviceExtension->CreatedSymbolicLink ){
				*( (PULONG)Irp->AssociatedIrp.SystemBuffer ) = deviceExtension->ComX;
				info = sizeof( ULONG );
				status = STATUS_SUCCESS;
			}
			break;
		case IOCTL_CREATE_DOS_NAME:
			{
				LONG ComX;
				DebugPrint(("-----  IOCTL_INIT_SETTING   ----\n"));
				if( IrpStack->Parameters.DeviceIoControl.InputBufferLength < sizeof( LONG ) ){
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				ComX = *((PLONG)Irp->AssociatedIrp.SystemBuffer);
				// 此处注意Dos名不要重复
				if( ( ComX > 255 ) || ( ComX < 1 ) ){
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				if( !deviceExtension->CreatedSymbolicLink ){
					status = SerialDoExternalNaming( deviceExtension, ComX);
				}
				break;
			}
		case IOCTL_DEL_DOS_NAME:
			DebugPrint(("-----  IOCTL_FINISH_SETTING   ----\n"));
			if( deviceExtension->CreatedSymbolicLink ){
				status = SerialUndoExternalNaming( deviceExtension );
			}
			break;
		case IOCTL_GET_CURRENT_INSTANCE:
			{
				DebugPrint(("--  IOCTL_GET_CURRENT_INSTANCE  ---\n"));
				if( IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof( ULONG ) ){
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				DebugPrint(("localInstance:  %d\n", deviceExtension->localInstance ));
				*( (PULONG)Irp->AssociatedIrp.SystemBuffer ) = deviceExtension->localInstance;
				status = STATUS_SUCCESS;
				info = sizeof( ULONG );
				break;
			}
		case IOCTL_SET_REMOTE_INSTANCE:
			{
				LONG	remoteInstance;
				KIRQL				OldIrql;
				DebugPrint(("--  IOCTL_SET_REMOTE_INSTANCE  ---\n"));
				if( IrpStack->Parameters.DeviceIoControl.InputBufferLength < sizeof( ULONG ) ){
					DebugPrint(("buffer is too small\n"));
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				// 若已经Connected，则返回错误。此时win32app 需要调用disconnect首先断开连接
				if( deviceExtension->remoteInstance != INVALID_INSTANCE ){
					break;
				}
				remoteInstance = *( (PULONG)Irp->AssociatedIrp.SystemBuffer );
				if( ( remoteInstance < 0 ) || ( remoteInstance > 255 ) ||
					( gDeviceArray[ remoteInstance ].deviceExtension == NULL ) ){
					DebugPrint(("remoteInstance error remoteInstance: %d\n", remoteInstance));
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				//Disconnect( deviceExtension );
				DebugPrint(("Connect remote ports..."));
				KeAcquireSpinLock( &gSpinLock, &OldIrql );
				if( gDeviceArray[ remoteInstance ].deviceExtension->bIsConnected ){
					KeReleaseSpinLock( &gSpinLock, OldIrql );
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				deviceExtension->remoteInstance = remoteInstance;
				deviceExtension->bIsConnected = TRUE;
				gDeviceArray[ remoteInstance ].deviceExtension->remoteInstance = deviceExtension->localInstance;
				gDeviceArray[ remoteInstance ].deviceExtension->bIsConnected = TRUE;
				KeReleaseSpinLock( &gSpinLock, OldIrql );
				status = STATUS_SUCCESS;
				info = sizeof( ULONG );
				break;
			}
		case IOCTL_GET_REMOTE_INSTANCE:
			{
				DebugPrint(("--  IOCTL_GET_REMOTE_INSTANCE  ---\n"));
				if( IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof( ULONG ) ){
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				if( !deviceExtension->bIsConnected ){
					DebugPrint(("remoteInstance:  %d\n", deviceExtension->remoteInstance ));
					status = STATUS_INVALID_DEVICE_REQUEST;
					break;
				}
				*( (PULONG)Irp->AssociatedIrp.SystemBuffer ) = deviceExtension->remoteInstance;
				status = STATUS_SUCCESS;
				info = sizeof( ULONG );
				break;
			}
		case IOCTL_DISCONNECT:
			DebugPrint(("---  IOCTL_DISCONNECT   ----\n"));
			status = Disconnect( deviceExtension );
			break;
		case IOCTL_SERIAL_SET_BAUD_RATE:
			{// to be continued
				// e.g
				DebugPrint(("--  IOCTL_SERIAL_SET_BAUD_RATE  ---\n"));
				if( IrpStack->Parameters.DeviceIoControl.InputBufferLength < sizeof( SERIAL_BAUD_RATE ) ){
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				deviceExtension->CurrentBaud = ((PSERIAL_BAUD_RATE)(Irp->AssociatedIrp.SystemBuffer))->BaudRate;
				DebugPrint(("CurrentBaud :  %d     SetBaudRate:   %d\n", deviceExtension->CurrentBaud, ((PSERIAL_BAUD_RATE)(Irp->AssociatedIrp.SystemBuffer))->BaudRate));
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_GET_BAUD_RATE:
			{
				PSERIAL_BAUD_RATE	Br = ( PSERIAL_BAUD_RATE )Irp->AssociatedIrp.SystemBuffer;
				DebugPrint(("--  IOCTL_SERIAL_GET_BAUD_RATE  ---\n"));
				if( IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof( SERIAL_BAUD_RATE ) ){
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				DebugPrint(("Br->BaudRate :  %d\n", Br->BaudRate ));
				Br->BaudRate = deviceExtension->CurrentBaud;
				DebugPrint(("CurrentBaud:  %d    Br->BaudRate   %d\n", deviceExtension->CurrentBaud, Br->BaudRate ));
				info = sizeof( SERIAL_BAUD_RATE );
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_GET_MODEM_CONTROL:
			DebugPrint(("--  IOCTL_SERIAL_GET_MODEM_CONTROL   --\n"));
			break;
		case IOCTL_SERIAL_SET_MODEM_CONTROL:
			DebugPrint(("--  IOCTL_SERIAL_SET_MODEM_CONTROL   --\n"));
			break;
		case IOCTL_SERIAL_SET_FIFO_CONTROL:
			DebugPrint(("--  IOCTL_SERIAL_SET_FIFO_CONTROL   --\n"));
			break;
		case IOCTL_SERIAL_SET_LINE_CONTROL:
			{
				PSERIAL_LINE_CONTROL Lc;
				UCHAR LData;
				UCHAR LStop;
				UCHAR LParity;
				UCHAR Mask = 0xff;
				DebugPrint(("--  IOCTL_SERIAL_SET_LINE_CONTROL   --\n"));
				if( IrpStack->Parameters.DeviceIoControl.InputBufferLength < sizeof(SERIAL_LINE_CONTROL)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				Lc = ((PSERIAL_LINE_CONTROL)(Irp->AssociatedIrp.SystemBuffer));
				deviceExtension->LineControl.WordLength = Lc->WordLength;
				deviceExtension->LineControl.Parity		= Lc->Parity;
				deviceExtension->LineControl.StopBits	= Lc->StopBits;
				DebugPrint(("IOCTL_SERIAL_SET_LINE_CONTROL:  WordLength:  %d  Parity:  %d  StopBits  %d\n", Lc->WordLength, Lc->Parity, Lc->StopBits ));
				status = STATUS_SUCCESS;
				break;

			}
		case IOCTL_SERIAL_GET_LINE_CONTROL:
			{	//	need ControlLock
				PSERIAL_LINE_CONTROL Lc = (PSERIAL_LINE_CONTROL)Irp->AssociatedIrp.SystemBuffer;
				DebugPrint(("--  IOCTL_SERIAL_GET_LINE_CONTROL   --\n"));
				
				if (IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof(SERIAL_LINE_CONTROL)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				Lc->WordLength	= deviceExtension->LineControl.WordLength;
				Lc->Parity		= deviceExtension->LineControl.Parity;
				Lc->StopBits	= deviceExtension->LineControl.StopBits;

				DebugPrint(("IOCTL_SERIAL_GET_LINE_CONTROL:  WordLength:  %d  Parity:  %d  StopBits  %d\n", Lc->WordLength, Lc->Parity, Lc->StopBits ));
				info = sizeof(SERIAL_LINE_CONTROL);
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_SET_TIMEOUTS:
			{
				PSERIAL_TIMEOUTS NewTimeouts =
					((PSERIAL_TIMEOUTS)(Irp->AssociatedIrp.SystemBuffer));
				DebugPrint(("--  IOCTL_SERIAL_SET_TIMEOUTS   --\n"));
				if ( IrpStack->Parameters.DeviceIoControl.InputBufferLength <
					sizeof(SERIAL_TIMEOUTS)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				if ((NewTimeouts->ReadIntervalTimeout == MAXULONG) &&
					(NewTimeouts->ReadTotalTimeoutMultiplier == MAXULONG) &&
					(NewTimeouts->ReadTotalTimeoutConstant == MAXULONG)) {
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				deviceExtension->Timeouts.ReadIntervalTimeout = NewTimeouts->ReadIntervalTimeout;
				deviceExtension->Timeouts.ReadTotalTimeoutMultiplier =NewTimeouts->ReadTotalTimeoutMultiplier;
				deviceExtension->Timeouts.ReadTotalTimeoutConstant = NewTimeouts->ReadTotalTimeoutConstant;
				deviceExtension->Timeouts.WriteTotalTimeoutMultiplier =	NewTimeouts->WriteTotalTimeoutMultiplier;
				deviceExtension->Timeouts.WriteTotalTimeoutConstant = NewTimeouts->WriteTotalTimeoutConstant;
				DebugPrint(("Set_Timeouts\n"));
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_GET_TIMEOUTS:
			{
				if ( IrpStack->Parameters.DeviceIoControl.OutputBufferLength <
					sizeof(SERIAL_TIMEOUTS)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				DebugPrint(("--  IOCTL_SERIAL_GET_TIMEOUTS   --\n"));
				*((PSERIAL_TIMEOUTS)Irp->AssociatedIrp.SystemBuffer) = deviceExtension->Timeouts;
				//Irp->IoStatus.Information = sizeof(SERIAL_TIMEOUTS);	// modified by zcz dec 25, 2003
				info = sizeof( SERIAL_TIMEOUTS );
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_SET_CHARS:
			{
				PSERIAL_CHARS NewChars =
					((PSERIAL_CHARS)(Irp->AssociatedIrp.SystemBuffer));
				DebugPrint(("--  IOCTL_SERIAL_SET_CHARS   --\n"));
				if ( IrpStack->Parameters.DeviceIoControl.InputBufferLength <
					sizeof(SERIAL_CHARS)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}else if( NewChars->XonChar == NewChars->XoffChar ){
					status = STATUS_INVALID_PARAMETER;
					break;
				}else{
					deviceExtension->SpecialChars.EofChar	= NewChars->EofChar;
					deviceExtension->SpecialChars.ErrorChar	= NewChars->ErrorChar;
					deviceExtension->SpecialChars.BreakChar	= NewChars->BreakChar;
					deviceExtension->SpecialChars.EventChar	= NewChars->EventChar;
					deviceExtension->SpecialChars.XonChar	= NewChars->XonChar;
					deviceExtension->SpecialChars.XoffChar	= NewChars->XoffChar;
					DebugPrint(("SetChars:  %2x %2x %2x %2x %2x %2x\n", NewChars->EofChar, NewChars->ErrorChar, NewChars->BreakChar, NewChars->EventChar, NewChars->XonChar, NewChars->XoffChar ));
					status = STATUS_SUCCESS;
				}
				break;
			}
		case IOCTL_SERIAL_GET_CHARS:
			{	//	need ControlLock
				PSERIAL_CHARS NewChars = ((PSERIAL_CHARS)(Irp->AssociatedIrp.SystemBuffer));
				DebugPrint(("--  IOCTL_SERIAL_GET_CHARS   --\n"));

				if( IrpStack->Parameters.DeviceIoControl.OutputBufferLength <
					sizeof(SERIAL_CHARS)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				((PSERIAL_CHARS)Irp->AssociatedIrp.SystemBuffer)->XonChar	= deviceExtension->SpecialChars.XonChar;
				((PSERIAL_CHARS)Irp->AssociatedIrp.SystemBuffer)->XoffChar	= deviceExtension->SpecialChars.XoffChar;
				((PSERIAL_CHARS)Irp->AssociatedIrp.SystemBuffer)->EofChar	= deviceExtension->SpecialChars.EofChar;
				((PSERIAL_CHARS)Irp->AssociatedIrp.SystemBuffer)->ErrorChar	= deviceExtension->SpecialChars.ErrorChar;
				((PSERIAL_CHARS)Irp->AssociatedIrp.SystemBuffer)->BreakChar	= deviceExtension->SpecialChars.BreakChar;
				((PSERIAL_CHARS)Irp->AssociatedIrp.SystemBuffer)->EventChar	= deviceExtension->SpecialChars.EventChar;
				DebugPrint(("GetChars:  %2x %2x %2x %2x %2x %2x\n", NewChars->EofChar, NewChars->ErrorChar, NewChars->BreakChar, NewChars->EventChar, NewChars->XonChar, NewChars->XoffChar ));
				info = sizeof( SERIAL_CHARS );
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_SET_DTR:
			{
				DebugPrint(("--  IOCTL_SERIAL_SET_DTR   --\n"));
				if (( deviceExtension->HandFlow.ControlHandShake & SERIAL_DTR_MASK) == SERIAL_DTR_HANDSHAKE){
					DebugPrint(("IOCTL_SERIAL_SET_DTR error: Current ControlHandShake 0x%x\n", deviceExtension->HandFlow.ControlHandShake ));
					status = STATUS_INVALID_PARAMETER;
				}
				info = 0;
				//*(PULONG)Irp->AssociatedIrp.SystemBuffer = 0;
				status = STATUS_SUCCESS;

				break;
			}
        case IOCTL_SERIAL_CLR_DTR:
			{
				DebugPrint(("--  IOCTL_SERIAL_CLR_DTR   --\n"));
				if (( deviceExtension->HandFlow.ControlHandShake & SERIAL_DTR_MASK) == SERIAL_DTR_HANDSHAKE){
					DebugPrint(("IOCTL_SERIAL_CLR_DTR error\n"));
					status = STATUS_INVALID_PARAMETER;
				}
				//*(PULONG)Irp->AssociatedIrp.SystemBuffer = 0;
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_RESET_DEVICE:
			DebugPrint(("--  IOCTL_SERIAL_RESET_DEVICE   --\n"));
			break;
		case IOCTL_SERIAL_SET_RTS:
			{
				DebugPrint(("--  IOCTL_SERIAL_SET_RTS   --\n"));
				if (( deviceExtension->HandFlow.FlowReplace & SERIAL_RTS_MASK) == SERIAL_RTS_HANDSHAKE ){
					DebugPrint(("IOCTL_SERIAL_SET_RTS error\n"));
					status = STATUS_INVALID_PARAMETER;
				}
				
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_CLR_RTS:
			DebugPrint(("--  IOCTL_SERIAL_CLR_RTS   --\n"));
			break;
		case IOCTL_SERIAL_SET_XOFF:
			DebugPrint(("--  IOCTL_SERIAL_SET_XOFF   --\n"));
			break;
		case IOCTL_SERIAL_SET_XON:
			DebugPrint(("--  IOCTL_SERIAL_SET_XON   --\n"));
			break;
		case IOCTL_SERIAL_SET_BREAK_ON:
			DebugPrint(("--  IOCTL_SERIAL_SET_BREAK_ON   --\n"));
			break;
		case IOCTL_SERIAL_SET_BREAK_OFF:
			DebugPrint(("--  IOCTL_SERIAL_SET_BREAK_OFF   --\n"));
			break;
		case IOCTL_SERIAL_SET_QUEUE_SIZE:
			{
				PSERIAL_QUEUE_SIZE	Rs = ( PSERIAL_QUEUE_SIZE )Irp->AssociatedIrp.SystemBuffer;
				DebugPrint(("--  IOCTL_SERIAL_SET_QUEUE_SIZE   --\n"));
				if( IrpStack->Parameters.DeviceIoControl.InputBufferLength < sizeof(SERIAL_QUEUE_SIZE)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				if( Rs->InSize > deviceExtension->BufferSize ){
					deviceExtension->BufferSize = Rs->InSize;
				}
				DebugPrint(("Buffersize :  %d\n", deviceExtension->BufferSize ));
				status = STATUS_SUCCESS;
				break;
#if 0
				try{
					IrpStack->Parameters.DeviceIoControl.Type3InputBuffer =
						ExAllocatePoolWithQuota( NonPagedPool, Rs->InSize );
				}except( EXCEPTION_EXECUTE_HANDLER ){
					IrpStack->Parameters.DeviceIoControl.Type3InputBuffer = NULL;
					status = GetExceptionCode();
				}
				if (!IrpStack->Parameters.DeviceIoControl.Type3InputBuffer) {
					break;
				}
				if( ( deviceExtension->BufferSize != 0 ) || ( deviceExtension->ReadBufferBase != NULL ) ){
					ExFreePool( deviceExtension->ReadBufferBase );
					deviceExtension->BufferSize = 0;
				}
				deviceExtension->ReadBufferBase = IrpStack->Parameters.DeviceIoControl.Type3InputBuffer;
#endif

			}
		case IOCTL_SERIAL_GET_WAIT_MASK:
			{
				DebugPrint(("--  IOCTL_SERIAL_GET_WAIT_MASK   --\n"));
				break;
			}
		case IOCTL_SERIAL_SET_WAIT_MASK:
			{
				ULONG NewMask;
				if ( IrpStack->Parameters.DeviceIoControl.InputBufferLength < sizeof(ULONG)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}else{
					NewMask = *((ULONG *)Irp->AssociatedIrp.SystemBuffer);
				}
				DebugPrint(("--  IOCTL_SERIAL_SET_WAIT_MASK   --\n"));
				
				if (NewMask & ~(SERIAL_EV_RXCHAR   |
					SERIAL_EV_RXFLAG   |
					SERIAL_EV_TXEMPTY  |
					SERIAL_EV_CTS      |
					SERIAL_EV_DSR      |
					SERIAL_EV_RLSD     |
					SERIAL_EV_BREAK    |
					SERIAL_EV_ERR      |
					SERIAL_EV_RING     |
					SERIAL_EV_PERR     |
					SERIAL_EV_RX80FULL |
					SERIAL_EV_EVENT1   |
					SERIAL_EV_EVENT2)) {
					DebugPrint(("SERIAL: Unknown mask %x\n",NewMask));
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				DebugPrint(("Set wait mask:   0x%x\n", NewMask ));
				if( deviceExtension->bIsWaitOnMask ){	// 取消上一次的WAIT_ON_MASK Irp
					ASSERT( deviceExtension->WaitOnMaskIrp );
					*((ULONG *)deviceExtension->WaitOnMaskIrp->AssociatedIrp.SystemBuffer) = 0;
					CompleteRequest( deviceExtension->WaitOnMaskIrp, STATUS_SUCCESS, sizeof( ULONG ));
					deviceExtension->WaitOnMaskIrp = NULL;
					deviceExtension->bIsWaitOnMask = FALSE;
				}
				deviceExtension->WaitMask = NewMask;
				status = STATUS_SUCCESS;
				//SerialStartMask();
				break;
			}
		case IOCTL_SERIAL_WAIT_ON_MASK:
			{
				ULONG	RetMask;
				DebugPrint(("--  IOCTL_SERIAL_WAIT_ON_MASK   --\n"));
				if ( IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof(ULONG)) {
					DebugPrint(("SERIAL: Invalid size for the buffer %d\n",
						IrpStack->Parameters.DeviceIoControl.OutputBufferLength));
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}else if( deviceExtension->bIsWaitOnMask ){
					DebugPrint(("There is a wait-on-mask request already pending\n"));
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				/*
				RetMask = SERIAL_EV_TXEMPTY | SERIAL_EV_RXCHAR | SERIAL_EV_RX80FULL;//SERIAL_EV_CTS;
				//SerialStartMask();
				*((ULONG *)Irp->AssociatedIrp.SystemBuffer) = RetMask;
				*/
				DebugPrint(("MarkIrpPending\n"));
				IoMarkIrpPending( Irp );
				IoSetCancelRoutine( Irp, RequestCancelMaskRoutine);
				ASSERT( deviceExtension->WaitOnMaskIrp == NULL );
				deviceExtension->WaitOnMaskIrp = Irp;
				deviceExtension->bIsWaitOnMask = TRUE;
				status = STATUS_PENDING;
				return status;
			}
		case IOCTL_SERIAL_IMMEDIATE_CHAR:
			DebugPrint(("--  IOCTL_SERIAL_IMMEDIATE_CHAR   --\n"));
			break;
		case IOCTL_SERIAL_PURGE:
			{
				ULONG	PurgeMask;
				DebugPrint(("--   IOCTL_SERIAL_PURGE  --\n"));
				if ( IrpStack->Parameters.DeviceIoControl.InputBufferLength <
					sizeof( ULONG )) {
					DebugPrint(("Serial purge output buffer too small\n"));
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				PurgeMask = *(PULONG)Irp->AssociatedIrp.SystemBuffer;
				DebugPrint(("IOCTL_SERIAL_PURGE:   0x%x\n", PurgeMask));
				if( PurgeMask & SERIAL_PURGE_RXABORT ){
					RequestPurgeIrpQueue( DeviceObject, &deviceExtension->ReadIrpQueue );
				}
				if( PurgeMask & SERIAL_PURGE_TXABORT ){
					RequestPurgeIrpQueue( DeviceObject, &deviceExtension->WriteIrpQueue );
				}
				if( PurgeMask & SERIAL_PURGE_RXCLEAR ){
					RequestPurgeDataQueue( DeviceObject, &deviceExtension->ReadDataQueue );
				}
				if( PurgeMask & SERIAL_PURGE_TXCLEAR ){
					DebugPrint(("Purge TxClear\n"));
				}
				info = sizeof( ULONG );
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_GET_HANDFLOW:
			{
				PSERIAL_HANDFLOW	HandFlow;
				DebugPrint(("--  IOCTL_SERIAL_GET_HANDFLOW   --\n"));
				if ( IrpStack->Parameters.DeviceIoControl.OutputBufferLength <
					sizeof(SERIAL_HANDFLOW)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				HandFlow = (PSERIAL_HANDFLOW)Irp->AssociatedIrp.SystemBuffer;
				HandFlow->ControlHandShake	= deviceExtension->HandFlow.ControlHandShake;
				HandFlow->FlowReplace		= deviceExtension->HandFlow.FlowReplace;
				HandFlow->XonLimit			= deviceExtension->HandFlow.XonLimit;
				HandFlow->XoffLimit			= deviceExtension->HandFlow.XoffLimit;
				DebugPrint(("ControlHandShake:  %d  FlowReplace:  %d  XonLimit:  %d  XoffLimit:  %d\n", HandFlow->ControlHandShake, HandFlow->FlowReplace, HandFlow->XonLimit, HandFlow->XoffLimit));
				info = sizeof(SERIAL_HANDFLOW);
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_SET_HANDFLOW:
			{
	            PSERIAL_HANDFLOW HandFlow = Irp->AssociatedIrp.SystemBuffer;
				if ( IrpStack->Parameters.DeviceIoControl.InputBufferLength <
					sizeof(SERIAL_HANDFLOW)) {
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				DebugPrint(("--  IOCTL_SERIAL_SET_HANDFLOW   --\n"));
				
				if (HandFlow->ControlHandShake & SERIAL_CONTROL_INVALID) {
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				if (HandFlow->FlowReplace & SERIAL_FLOW_INVALID) {
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				if ((HandFlow->ControlHandShake & SERIAL_DTR_MASK) ==
					SERIAL_DTR_MASK) {
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				if ((HandFlow->XonLimit < 0) ||
					((ULONG)HandFlow->XonLimit > deviceExtension->BufferSize)) {
					DebugPrint(("XonLimit( %d ) > BufferSize\n", ((ULONG)HandFlow->XonLimit )));
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				if ((HandFlow->XoffLimit < 0) ||
					((ULONG)HandFlow->XoffLimit > deviceExtension->BufferSize)) {
					DebugPrint(("XoffLimit( %d ) > BufferSize\n", ((ULONG)HandFlow->XoffLimit )));
					status = STATUS_INVALID_PARAMETER;
					break;
				}
				deviceExtension->HandFlow.ControlHandShake	= HandFlow->ControlHandShake;
				deviceExtension->HandFlow.FlowReplace		= HandFlow->FlowReplace;
				deviceExtension->HandFlow.XonLimit			= HandFlow->XonLimit;
				deviceExtension->HandFlow.XoffLimit			= HandFlow->XoffLimit;
				DebugPrint(("Set_HandFlow OK\n"));
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_GET_MODEMSTATUS:
			DebugPrint(("--  IOCTL_SERIAL_GET_MODEMSTATUS   --\n"));
			break;
		case IOCTL_SERIAL_GET_DTRRTS:
			DebugPrint(("--  IOCTL_SERIAL_GET_DTRRTS   --\n"));
			break;
		case IOCTL_SERIAL_GET_COMMSTATUS:
			DebugPrint(("--  IOCTL_SERIAL_GET_COMMSTATUS   --\n"));
			break;
		case IOCTL_SERIAL_GET_PROPERTIES:
			DebugPrint(("--  IOCTL_SERIAL_GET_PROPERTIES   --\n"));
			break;
		case IOCTL_SERIAL_XOFF_COUNTER:
			DebugPrint(("--  IOCTL_SERIAL_XOFF_COUNTER   --\n"));
			break;
		case IOCTL_SERIAL_LSRMST_INSERT:
			DebugPrint(("--  IOCTL_SERIAL_LSRMST_INSERT   --\n"));
			break;
		case IOCTL_SERIAL_CONFIG_SIZE:
			{
				DebugPrint(("--  IOCTL_SERIAL_CONFIG_SIZE   --\n"));
				if( IrpStack->Parameters.DeviceIoControl.OutputBufferLength < sizeof( ULONG ) ){
					status = STATUS_BUFFER_TOO_SMALL;
					break;
				}
				
				info = sizeof( ULONG );
				*(PULONG)Irp->AssociatedIrp.SystemBuffer = 0;
				status = STATUS_SUCCESS;
				break;
			}
		case IOCTL_SERIAL_GET_STATS:
			DebugPrint(("--  IOCTL_SERIAL_GET_STATS   --\n"));
			break;
		case IOCTL_SERIAL_CLEAR_STATS:
			DebugPrint(("--  IOCTL_SERIAL_CLEAR_STATS   --\n"));
			break;
		default:
			break;
	}
	return CompleteRequest(Irp, status, info);
}
VOID
RequestPurgeIrpQueue(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PLIST_ENTRY		QueueToProcess
	)
/*++
Routine Description:

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.

Return Value:

    NT Status is returned.
--*/
{
	PDEVICE_EXTENSION	deviceExtension;
	PLIST_ENTRY			link;
	PIRP				pendingIrp;

	DebugPrint(("Enter RequestPurgeIrpQueue routine...\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;
	link = ExInterlockedRemoveHeadList( QueueToProcess, &deviceExtension->CancelSpinLock );
	while( link ){
		pendingIrp = CONTAINING_RECORD( link, IRP, Tail.Overlay.ListEntry );
		ASSERT( pendingIrp );
		pendingIrp->IoStatus.Status = STATUS_CANCELLED;
		pendingIrp->IoStatus.Information = 0;
		IoCompleteRequest( pendingIrp, IO_NO_INCREMENT );
		link = ExInterlockedRemoveHeadList( QueueToProcess, &deviceExtension->CancelSpinLock );
	}
	return;
}
VOID
RequestCancelReadRoutine(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PIRP				Irp
	)
/*++
Routine Description:

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.

Return Value:

    NT Status is returned.
--*/
{
	BOOLEAN				bRet;
	PDEVICE_EXTENSION	deviceExtension;
	DebugPrint(("Enter RequestCancelRead routine...\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;

	bRet = RequestCancelRoutine( &deviceExtension->ReadIrpQueue, &deviceExtension->CancelSpinLock, Irp );
	return;
}
VOID
RequestCancelWriteRoutine(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PIRP				Irp
	)
/*++
Routine Description:

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.

Return Value:

    NT Status is returned.
--*/
{
	BOOLEAN				bRet;
	PDEVICE_EXTENSION	deviceExtension;
	DebugPrint(("Enter RequestCancelRead routine...\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;

	bRet = RequestCancelRoutine( &deviceExtension->WriteIrpQueue, &deviceExtension->CancelSpinLock, Irp );
	return;
}
VOID
RequestCancelMaskRoutine(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PIRP				Irp
	)
/*++
Routine Description:

Arguments:

    DeviceObject - Pointer to deviceobject
    Irp          - Pointer to a PnP Irp.

Return Value:

    NT Status is returned.
--*/
{
	PDEVICE_EXTENSION	deviceExtension;
	DebugPrint(("Enter RequestCancelRead routine...\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;

	ASSERT( deviceExtension->bIsWaitOnMask && ( deviceExtension->WaitOnMaskIrp != NULL ) );
	CompleteRequest( deviceExtension->WaitOnMaskIrp, STATUS_CANCELLED, 0 );
	deviceExtension->WaitOnMaskIrp = NULL;
	deviceExtension->bIsWaitOnMask = FALSE;
	return;
}
BOOLEAN
RequestCancelRoutine(
	IN PLIST_ENTRY		QueueToProcess,
	IN PKSPIN_LOCK		CancelSpinLock,
	IN PIRP				Irp)
/*++
Routine Description:
	A cancel routine for use when cancelling the pending IRP

Arguments:
	QueueToProcess	- The queue to be processing
	CancelSpinLock	- Cancel spin lock
    Irp				- Pointer to a PnP Irp.

Return Value:

    NT Status is returned.
	If the Irp is in the QueueToProcess, we cancel the irp and return TRUE; else return FALSE.
--*/
{
	PLIST_ENTRY			link;
	PIRP				pendingIrp;
	PIRP				IrpToComplete;
	KIRQL				oldIrpl;

	DebugPrint(("Enter RequestCancel routine...\n"));

	IrpToComplete = NULL;
	// Find the Irp in the QueueToProcess
	KeAcquireSpinLock( CancelSpinLock, &oldIrpl );
	for( link = QueueToProcess->Flink; link != QueueToProcess; link = link->Flink )
	{
		pendingIrp = CONTAINING_RECORD( link, IRP, Tail.Overlay.ListEntry );
		ASSERT( pendingIrp );
		if( pendingIrp == Irp ){
			DebugPrint(("Find out the pending irp, to remove...\n"));
			RemoveEntryList( link );
			IrpToComplete = pendingIrp;
			break;
		}
	}
	KeReleaseSpinLock( CancelSpinLock, oldIrpl );
	if( IrpToComplete ){
		// If we find out the Irp, cancel the Irp
		DebugPrint(("Cancelled Irp\n"));
		IrpToComplete->IoStatus.Status = STATUS_CANCELLED;
		IrpToComplete->IoStatus.Information = 0;
		IoCompleteRequest( IrpToComplete, IO_NO_INCREMENT );
		return TRUE;
	}else
		return FALSE;
}
NTSTATUS Disconnect(	IN PDEVICE_EXTENSION deviceExtension )
/*++
Routine Description:
	disconnect two virtual devices which are connected before
Arguments:

	deviceExtension	- Pointer to device extension

Return Value:

    NT Status is returned.
--*/
{
	PDEVICE_EXTENSION	remoteDevExt;
	KIRQL				OldIrql;

	KeAcquireSpinLock( &gSpinLock, &OldIrql );
	if( !deviceExtension->bIsConnected ){
		KeReleaseSpinLock(&gSpinLock, OldIrql );
		return STATUS_INVALID_DEVICE_REQUEST;
	}
	remoteDevExt = gDeviceArray[ deviceExtension->remoteInstance ].deviceExtension;
	deviceExtension->remoteInstance = INVALID_INSTANCE;
	deviceExtension->bIsConnected = FALSE;
	remoteDevExt->remoteInstance = INVALID_INSTANCE;
	remoteDevExt->bIsConnected = FALSE;
	KeReleaseSpinLock( &gSpinLock, OldIrql );

	return STATUS_SUCCESS;
}
VOID
RequestPurgeDataQueue(
	IN PDEVICE_OBJECT	DeviceObject,
	IN PLIST_ENTRY		QueueToProcess
	)
{
	PDEVICE_EXTENSION	deviceExtension;
	PLIST_ENTRY			link;
	PPACKET				lpPacket;

	DebugPrint(("Enter RequestPurgeDataQueue routine...\n"));
	deviceExtension = ( PDEVICE_EXTENSION )DeviceObject->DeviceExtension;
	while( link = ExInterlockedRemoveHeadList( QueueToProcess, &deviceExtension->ReadQueueSpinLock )){
		lpPacket = CONTAINING_RECORD( link, PACKET, ListEntry );
		RtlZeroMemory( lpPacket, sizeof( PACKET ) );
		ExInterlockedInsertTailList( &gIdleQueue, &( lpPacket->ListEntry ), &gPoolSpinLock );
	}
}
