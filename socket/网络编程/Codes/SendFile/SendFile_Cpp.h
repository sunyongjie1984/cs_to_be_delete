//---------------------------------------------------------------------------

#ifndef SendFile_CppH
#define SendFile_CppH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <FileCtrl.hpp>
#include <NMUDP.hpp>
#include <Buttons.hpp>
#include "math.h"
#include "mmsystem.h"
//---------------------------------------------------------------------------
enum TBlockType {blNormal,blSent,blReSent};

typedef struct
{
 char FileFlage[6];
 unsigned short CRC;
 char Ver;
 long Size;
 long Position;
 char Data[1000];
} TSendFileData;

typedef struct
{
 int Position;
 int Size;
 char Buffer[1000];
} TReadBuffer;



const unsigned short cnCRC_16    = 0x8005;
const unsigned short cnCRC_CCITT = 0x1021;
const unsigned long  cnCRC_32   = 0x04C10DB7;


class TSendFiles : public TForm
{
__published:	// IDE-managed Components
        TNotebook *Notebook1;
        TPanel *Panel1;
        TPanel *Panel2;
        TButton *Add;
        TButton *Sent;
        TStatusBar *FRStatusBar;
        TButton *SetUp;
        TOpenDialog *OpenDialog1;
        TPanel *Panel4;
        TPanel *Panel3;
        TButton *Button4;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *RemoteIP;
        TEdit *RemotePort;
        TLabel *Label5;
        TEdit *Dir;
        TButton *Button5;
        TNMUDP *NMUDP1;
        TButton *Clear;
        TTimer *FSTimer;
        TButton *Cancel;
        TLabel *Label1;
        TEdit *MaxTimeOut;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TRadioGroup *ReciveType;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TListView *ListView1;
        TMemo *FRError;
        TMemo *FSRepa;
        TSplitter *Splitter1;
        TTimer *Timer1;
        TLabel *Label6;
        TStatusBar *FSStatusBar;
        TMemo *FRCMDS;
        TMemo *FSCMDS;
        TSpeedButton *Speed;
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall SetUpClick(TObject *Sender);
        void __fastcall AddClick(TObject *Sender);
        void __fastcall ListView1Resize(TObject *Sender);
        void __fastcall ClearClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall NMUDP1DataReceived(TComponent *Sender,
          int NumberBytes, AnsiString FromIP, int Port);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SentClick(TObject *Sender);
        void __fastcall FSTimerTimer(TObject *Sender);
        void __fastcall CancelClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall SpeedClick(TObject *Sender);
private:	// User declarations
        unsigned long Table_CRC[256];
        TStringList   *FullFileName;
        TSendFileData  LastSendData;
        int            WriteListCount;
        int            BlockSize;
        bool           *WriteList;
        char           LastReciveCMD[6];
        TFileStream    *ReadFile,*WriteFile;
        int            ReadFileSize,WriteFileSize;
        int            ErrorCount;
        int            FSTimeOut;
        int            TimerCount;
        int            FSBlocks,FRBlocks;
        int            SleepTime;
        float          Rate,LastFRRate,LastFSRate;
        AnsiString     FSCMD,FRCMD;
        void __fastcall BuildTable16( unsigned short aPoly );
        unsigned short __fastcall CRC_16( unsigned char * aData, unsigned long aSize );
        void __fastcall SendData_1(AnsiString CMD,char *Buffer,long Size);
        void __fastcall SendData_1(AnsiString CMD,char *Buffer,long Size,long Position);
        void __fastcall WriteToUDF(char *Buffer,int Size);
        void __fastcall Proce_Send_F_1(TSendFileData FileData);
        void __fastcall StartSend();
        void __fastcall WriteToStream();
        void __fastcall Delay(int n);
        int  __fastcall SendFile_1(int Position);
        AnsiString __fastcall GetDir();

public:		// User declarations
        __fastcall TSendFiles(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSendFiles *SendFiles;
//---------------------------------------------------------------------------
#endif
