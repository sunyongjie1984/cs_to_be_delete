unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, Buttons, Winsock, ExtCtrls;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    edtPort: TEdit;
    SaveDialog1: TSaveDialog;
    btnListen: TBitBtn;
    btnRecv: TBitBtn;
    btnstop: TBitBtn;
    btnExit: TBitBtn;
    StatusBar1: TStatusBar;
    procedure btnExitClick(Sender: TObject);
    procedure btnstopClick(Sender: TObject);
    procedure btnRecvClick(Sender: TObject);
    procedure btnListenClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
    stopTrans: boolean;
    InTrans: boolean;
    server: TSocket;
    procedure RecvFile(filename: string);
  end;

var
  Form1: TForm1;
const
  BlockLen = 1024 * 4;

implementation

{$R *.dfm}

procedure TForm1.btnExitClick(Sender: TObject);
begin
  close;
end;

procedure TForm1.btnstopClick(Sender: TObject);
begin
  stopTrans:= true;
  if server <> INVALID_SOCKET then
    closesocket(server);
  server:= INVALID_SOCKET;
  btnstop.Enabled:= false;
  btnListen.Enabled:= true;
end;

procedure TForm1.btnRecvClick(Sender: TObject);
begin
  if (server = INVALID_SOCKET) then
  begin
    MessageBox(handle, 'have no listening', 'info', MB_OK);
  end;
  if SaveDialog1.Execute then
    RecvFile(SaveDialog1.filename);
end;

procedure TForm1.btnListenClick(Sender: TObject);
var
  ca: SOCKADDR_IN;
begin
  server:= socket(PF_INET, SOCK_sTREAM, IPPROTO_IP);
  if server = INVALID_SOCKET then
  begin
    StatusBar1.SimpleText:= 'connection error!';
    Exit;
  end;
  ca.sin_family:= PF_INET;
  ca.sin_port:= htons(StrToInt(Trim(edtPort.Text)));
  ca.sin_addr.S_addr:= INADDR_ANY;
  if bind(server, ca, SizeOf(ca)) = SOCKET_ERROR then
  begin
    StatusBar1.SimpleText:= 'binding error,please change other port';
    closesocket(server);
  end
  else
    StatusBar1.SimpleText:= 'binding succeed';
  listen(server, 5);
  btnListen.Enabled:= false;
  btnstop.Enabled:= true;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  aWSAData: TWSAData;
begin
  if WSAStartup($0101, aWSAData) <> 0 then
    raise Exception.Create('不能启动WinSock动态链接库！');
  MessageBox(handle, aWSAData.szDesCription, 'WinSock动态链接库版本', MB_OK);
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if InTrans then
    if MessageBox(handle, '正在传输文件，停止吗？', '提示', MB_YESNO) = IDNO
      then
      abort;
  if server <> INVALID_SOCKET then
    closesocket(server);
  if WSACleanup <> 0 then
    MessageBox(handle, '清除WinSock动态连接库错误', '提示', MB_OK)
  else
    MessageBox(handle, '清除WinSock动态连接库成功', '提示', MB_OK);
end;

procedure TForm1.RecvFile(filename: string);
var
  Ftrans: file of byte;
  Recelen: integer;
  BlockBuf: array[0..BlockLen - 1] of byte;
  RecvSocket: TSocket;
  ra: SOCKADDR_IN;
  ra_len: integer;
begin
  ra_len:= SizeOf(ra);
  RecvSocket:= accept(server, @ra, @ra_len);
  AssignFile(Ftrans, filename);
  Rewrite(Ftrans);
  stopTrans:= false;
  InTrans:= true;
  Recelen:= recv(RecvSocket, BlockBuf, BlockLen, 0);
  while (Recelen > 0) and (not stopTrans) do
  begin
    BlockWrite(Ftrans, BlockBuf[0], Recelen);
    Application.ProcessMessages;
    Recelen:= recv(RecvSocket, BlockBuf, BlockLen, 0);
    if stopTrans then
    begin
      CloseFile(Ftrans);
      closesocket(RecvSocket);
      InTrans:= false;
      MessageBox(handle, 'stop transmission', 'info', MB_OK);
      Exit;
    end;
  end;
  CloseFile(Ftrans);
  closesocket(RecvSocket);
  InTrans:= false;
  if (Recelen = SOCKET_ERROR) then
    MessageBox(handle, 'trans error', 'info', MB_OK)
  else
    MessageBox(handle, 'custom shut down,trans complete', 'info', MB_OK);
end;

end.

