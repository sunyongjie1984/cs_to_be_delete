program OICQpass;

uses
  Forms,
  main in 'main.pas' {fmMain};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfmMain, fmMain);
  Application.Run;
end.
