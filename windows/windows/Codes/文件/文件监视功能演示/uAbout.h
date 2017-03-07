//---------------------------------------------------------------------------

#ifndef uAboutH
#define uAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmAbout : public TForm
{
__published:	// IDE-managed Components
    TBevel *bvlBottom;
    TLabel *lblAppName;
    TLabel *lblCopyright;
    TLabel *lblWeb;
    TLabel *lblVersion;
    TBevel *bvlTop;
    TLabel *lblDesc;
    TButton *btnClose;
    TPanel *pnlHorLogo;
    TImage *imgHorLogo;
    TLabel *lblWebDisp;
    TLabel *lblMailDisp;
    TLabel *lblMail;
    TImage *imgAppIcon;
    void __fastcall lblWebClick(TObject *Sender);
    void __fastcall lblMailClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
#endif
