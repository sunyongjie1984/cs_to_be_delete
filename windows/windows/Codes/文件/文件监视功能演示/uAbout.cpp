//---------------------------------------------------------------------------
// 关于对话框 - About Form v0.21
// by ccrun(老妖) - info@ccrun.com
// Last modify: 2005.6.8
//---------------------------------------------------------------------------
// Welcome C++Builder Study - http://www.ccrun.com
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
    : TForm(Owner)
{
    imgAppIcon->Picture->Assign(Application->Icon);
}
//---------------------------------------------------------------------------
// 63 63 72 75 6E 2E 63 6F 6D
void __fastcall TfrmAbout::lblWebClick(TObject *Sender)
{
    ShellExecute(Handle, "Open", lblWeb->Caption.c_str(), NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::lblMailClick(TObject *Sender)
{
    ShellExecute(Handle, "Open",
            (String("Mailto:") + lblMail->Caption
            + "?subject=About: " + lblAppName->Caption).c_str(),
            NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

