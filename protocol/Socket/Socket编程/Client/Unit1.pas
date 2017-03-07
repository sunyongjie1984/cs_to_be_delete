unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, Buttons, Winsock, ExtCtrls;

type
  TForm1 = class(TForm)
    ProgressBar1: TProgressBar;
    edtIP: TEdit;
    edtport: TEdit;
    BtnConnect: TBitBtn;
    BtnSend: TBitBtn;
    BtnStop: TBitBtn;
    BtnExit: TBitBtn;
    StatusBar1: TStatusBar;
    OpenDialog1: TOpenDialog;
    Label1: TLabel;
    Label2: TLabel;
    procedure BtnExitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure BtnSendClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
    procedure BtnConnectClick(Sender: TObject);
  private
    client: TSocket;
    { Private declarations }
  public
    { Public declarations }
    StopTrans: boolean;
    InTrans: boolean;
    procedure TransFile(filename: string);
  end;

const
  BlockLen = 1024 * 4;
var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.BtnExitClick(Sender: TObject);
begin
  close;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  aWSAData: TWSAData;
begin
  if WSAStartup($0101, aWSAData) <> 0 then
    raise Exception.Create('不能启动WinSock动态链接库！');
  MessageBox(Handle, aWSAData.szDesCription, 'WinSock动态链接库版本', MB_OK);
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
var
  tim: Tdatetime;
begin
  if InTrans then
    if MessageBox(Handle, '正在传输文件，停止吗？', '提示', MB_YESNO) = IDNO
      then
      abort;
  if WSACleanup <> 0 then
    MessageBox(Handle, '清除WinSock动态连接库错误', '提示', MB_OK)
  else
    MessageBox(Handle, '清除WinSock动态连接库成功', '提示', MB_OK);
  closesocket(client);
end;

procedure TForm1.BtnSendClick(Sender: TObject);
begin
  if (OpenDialog1.Execute) and (FileExists(OpenDialog1.filename)) then
    TransFile(OpenDialog1.filename);
end;

procedure TForm1.BtnStopClick(Sender: TObject);
begin
  StopTrans:= true;
end;

procedure TForm1.BtnConnectClick(Sender: TObject);
var
  ca: SOCKADDR_IN;
  hostaddr: u_long;
begin
  client:= socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
  if client = INVALID_SOCKET then
  begin
    StatusBar1.simpleText:= '创建socket错误！';
    Exit;
  end;
  ca.sin_family:= PF_INET;
  ca.sin_port:= htons(StrToInt(Trim(edtport.Text)));
  hostaddr:= inet_addr(pchar(Trim(edtIP.Text)));
  if (hostaddr = -1) then
  begin
    StatusBar1.simpleText:= 'host ip:' + Trim(edtIP.Text) + 'error';
    Exit;
  end
  else
    ca.sin_addr.S_addr:= hostaddr;
  if connect(client, ca, SizeOf(ca)) <> 0 then
  begin
    StatusBar1.simpleText:= 'connect socket error!';
    Exit;
  end
  else
    StatusBar1.simpleText:= 'connection  succeed!'
end;

procedure TForm1.TransFile(filename: string);
var
  Ftrans: file of byte;
  Flen: integer;
  Blocknum, Remainlen: integer;
  BlockBuf: array[0..BlockLen - 1] of byte;
  i: integer;
  SendLen: integer;
begin
  AssignFile(Ftrans, filename);
  Reset(Ftrans);
  Flen:= FileSize(Ftrans);
  Blocknum:= Flen div BlockLen;
  ProgressBar1.Max:= 1 + Blocknum;
  Remainlen:= Flen mod BlockLen;
  StopTrans:= False;
  InTrans:= true;
  SendLen:= 1;
  for i:= 0 to Blocknum - 1 do
  begin
    if (StopTrans) or (SendLen <= 0) then
      Break;
    BlockRead(Ftrans, BlockBuf[0], BlockLen);
    SendLen:= send(client, BlockBuf, BlockLen, 0);
    ProgressBar1.Position:= i;
    application.ProcessMessages;
  end;
  if StopTrans then
  begin
    CloseFile(Ftrans);
    InTrans:= False;
    StatusBar1.simpleText:= '';
    MessageBox(Handle, 'stop trans', 'info', MB_OK);
    ProgressBar1.Position:= 0;
    Exit;
  end;
  if (SendLen <= 0) then
  begin
    CloseFile(Ftrans);
    InTrans:= False;
    StatusBar1.simpleText:= '';
    MessageBox(Handle, 'exception stop trans ', 'info', MB_OK);
    ProgressBar1.Position:= 0;
    Exit;
  end;
  if Remainlen > 0 then
  begin
    BlockRead(Ftrans, BlockBuf[0], Remainlen);
    SendLen:= send(client, BlockBuf, Remainlen, 0);
    if (SendLen <= 0) then
    begin
      CloseFile(Ftrans);
      InTrans:= False;
      StatusBar1.simpleText:= '';
      MessageBox(Handle, 'exception stop trans ', 'info', MB_OK);
      ProgressBar1.Position:= 0;
      Exit;
    end;
  end;
  ProgressBar1.Position:= ProgressBar1.Max;
  CloseFile(Ftrans);
  InTrans:= False;
  StatusBar1.simpleText:= '';
  MessageBox(Handle, 'trans complete! ', 'info', MB_OK);
  ProgressBar1.Position:= 0;
end;

end.
.
 .
