unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, ExtCtrls, StdCtrls, Buttons, ImgList;

type
  TfmMain = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    OpenDialog1: TOpenDialog;
    Button1: TButton;
    Button2: TButton;
    Bevel1: TBevel;
    StatusBar1: TStatusBar;
    Label3: TLabel;
    ListView1: TListView;
    Edit1: TEdit;
    Label4: TLabel;
    Label5: TLabel;
    ImageList1: TImageList;
    ListBox1: TListBox;
    procedure Button2Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    function DecryptOICQpass(password:String):String;
  end;

var
  fmMain: TfmMain;

implementation

{$R *.DFM}

function TfmMain.DecryptOICQpass(password:String):String;
var
   i,j:integer;
   x,y,l:integer;
   x1,y1,x2,y2,x3,y3:Integer;
   S:String;
   PassResult:array [1..20] of char;
const
    seed: array [0..3,0..3] of Integer
       = ((0,1,2,3),
          (1,0,3,2),
          (2,3,0,1),
          (3,2,1,0));
begin
   for i:=1 to length(password) do
   begin
        y:=Ord(Password[i]);
        if y>=224  then
        begin
         y:=y-224;
         l:=3;
        end
        else if y>=192  then
        begin
          l:=4 ;
          y:=y - 192 ;
        end
        else
        begin
          l:=1;
          y:=y-96;
        end;
        x:=i+4;
        y2:= y div 16;
        y3:= y mod 16;
        for j:=0 to 15 do
        begin
             if y3=seed[x div 4][j div 4]*4+seed[x mod 4][j mod 4]
             then
             begin

                 PassResult[i]:=Char(j+ y2 * 16 + (l-1)* 32);
                 break;
             end;
        end;
   end;
   S:=String(PassResult);
   SetLength(S,Length(Password));
   DecryptOICQPass:=S;
end;
procedure TfmMain.Button2Click(Sender: TObject);
begin
     Close;
end;

procedure TfmMain.BitBtn1Click(Sender: TObject);
begin
      if OpenDialog1.Execute then
      begin
      end;
end;

procedure TfmMain.Button1Click(Sender: TObject);
var
  sr: TSearchRec;
  FileAttrs: Integer;
  fdResult:Integer;
  NowSearchDirectory:String;
  NowFileName:String;
  i,j:integer;
  F: File of char;
  EncryptedPassword:String;
  MBuffer:array [0..128] of char;
  NowItem:TListItem;
begin
     i:=Pos('*.*',Edit1.Text);
     if i<>0 then Edit1.Text:=Copy(Edit1.Text,1,i-1);
     if Edit1.Text[Length(Edit1.Text)]<>'\' then
        Edit1.Text:=Edit1.Text+'\';
     ListBox1.Clear;
     ListView1.Items.Clear;
     NowFileName:=Edit1.Text+'*.*';
     FileAttrs:=faDirectory;
     fdResult:= FindFirst(NowFileName, FileAttrs, sr);
     while (fdResult = 0) do
     begin
     if (sr.Attr and FileAttrs) = sr.Attr then
        begin
        if (Ord(sr.name[1])>48) and (Ord(sr.name[1])< 58) then
                  ListBox1.Items.Add(sr.name);
        end;
     fdResult:=FindNext(sr);
     end;
     FindClose(sr);
     for i:=1 to ListBox1.Items.Count do
     begin
          EncryptedPassword:='';
          NowFileName:=Edit1.Text + ListBox1.Items[i-1]+ '\'
              +ListBox1.Items[i-1]+'.cfg';
          AssignFile(F,NowFileName);
          Reset(F);
          if FileSize(F)<= 20 then
          begin
               CloseFile(F);
               continue;
          end;
          BlockRead(F,MBuffer,20);
          EncryptedPassword:=String(MBuffer);
          for j:= 1 to 20 do
          begin
               if MBuffer[j]=#0 then
               begin
                    SetLength(EncryptedPassword,j);
                    break;
               end;
          end;
          CloseFile(F);
          NowItem:=ListView1.Items.Add;
          NowItem.StateIndex:=0;
          NowItem.Caption:=ListBox1.Items[i-1];
          NowItem.SubItems.Add(DecryptOICQpass(EncryptedPassword));

     end;
end;
end.
