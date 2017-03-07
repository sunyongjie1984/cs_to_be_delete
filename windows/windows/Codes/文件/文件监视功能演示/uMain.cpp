//---------------------------------------------------------------------------
#define  NO_WIN32_LEAN_AND_MEAN  // 从 Windows 头中排除极少使用的资料
#include  "shlobj.h"
#include  <vcl.h>
#pragma hdrstop

#include "uMain.h"
#include "uAbout.h"
#include "uFileMoniter.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmMain *frmMain;    
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
    Caption = Application->Title;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::WndProc(TMessage &Message)
{
	switch(Message.Msg)
    {
    	case WM_SHNOTIFY:
        	mmoResult->Lines->Add(NotifyReceipt(Message.WParam, Message.LParam));
            break;
        default:
        	break;
    }
    TForm::WndProc(Message);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnStartClick(TObject *Sender)
{
	g_HSHNotify = 0;
    mmoResult->Lines->Add(String("开始监视程序-->")
            + (RegSHNotify(Handle)? String("成功!"): String("失败!")));
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(g_pidlDesktop)
        UnregSHNotify();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnAboutClick(TObject *Sender)
{
    frmAbout = new TfrmAbout(this);
    frmAbout->ShowModal();
    delete frmAbout;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnStopClick(TObject *Sender)
{
	if(g_pidlDesktop)
    {
        mmoResult->Lines->Add(String("停止监视程序-->")
                + (UnregSHNotify()? String("成功!"): String("失败!")));
    }
}
//---------------------------------------------------------------------------

