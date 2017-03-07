VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form Phone 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "网络电话演示"
   ClientHeight    =   1920
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1920
   ScaleWidth      =   3750
   StartUpPosition =   3  '窗口缺省
   Begin MSWinsockLib.Winsock Listen 
      Left            =   1200
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock Connect 
      Left            =   2040
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.CommandButton Command3 
      Caption         =   "退出"
      Height          =   495
      Left            =   2640
      TabIndex        =   5
      ToolTipText     =   "结束程序运行"
      Top             =   840
      Width           =   855
   End
   Begin VB.CommandButton Command2 
      Caption         =   "挂机"
      Enabled         =   0   'False
      Height          =   495
      Left            =   1440
      TabIndex        =   4
      ToolTipText     =   "挂断与远程主机的连接"
      Top             =   840
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "呼叫"
      Height          =   495
      Left            =   240
      TabIndex        =   3
      ToolTipText     =   "利用输入地址呼叫远程主机"
      Top             =   840
      Width           =   975
   End
   Begin VB.TextBox Text1 
      Height          =   270
      Left            =   960
      TabIndex        =   1
      ToolTipText     =   "请输入对方主机名或 IP 地址"
      Top             =   240
      Width           =   2535
   End
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   315
      Left            =   0
      TabIndex        =   0
      Top             =   1605
      Width           =   3750
      _ExtentX        =   6615
      _ExtentY        =   556
      Style           =   1
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
         EndProperty
      EndProperty
   End
   Begin VB.Label Label1 
      Caption         =   "主机名："
      Height          =   270
      Left            =   240
      TabIndex        =   2
      Top             =   285
      Width           =   855
   End
End
Attribute VB_Name = "Phone"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
'定义动态库函数
'phone.dll 为自定义DLL库，由VC++生成，包含 StartPhone 和 ClosePhone 两个函数
Private Declare Function StartPhone Lib "phone" (ByVal Name As String, ByVal LocalPort As Long, ByVal RemotePort As Long) As Long
Private Declare Sub ClosePhone Lib "phone" ()
'定义常量
Const TcpPort As Long = 2048
Const LocalPort As Long = 2049
Const RemotePort As Long = 2049
Dim InputData As Long
Dim OutputData As Long


Private Sub Command1_Click()
    If Len(Text1) > 0 Then
        Connecting '申请连接
    End If
End Sub

Private Sub Command2_Click()
    OutputData = 4
    Connect.SendData OutputData '发送数据
End Sub

Private Sub Command3_Click()
    Unload Me '关闭窗体
End Sub

Private Sub Connect_Close()
'当对方执行Connect.Close方法关闭连接时，触发该事件
    Disconnect
End Sub

Private Sub Connect_Connect()
'当对方同意连接申请时，触发该事件
    OutputData = 0
    Connect.SendData OutputData '发送数据
End Sub

Private Sub Connect_DataArrival(ByVal bytesTotal As Long)
'Connect对象收到数据时，触发该事件
    Connect.GetData InputData '接收数据
    Select Case InputData
        Case 0
            Message "实现远程连接"
            If MsgBox("收到‘" + Connect.RemoteHostIP + "’呼叫，是否应答？", vbYesNo, "呼叫显示") = vbNo Then
                Disconnect
            ElseIf OpenPhone Then
                OutputData = 1
                Connect.SendData OutputData '发送数据
                Message "已经开始通话"
            Else
                OutputData = 3
                Connect.SendData OutputData '发送数据
                MsgBox "无法打开音频设备", vbOKOnly, ""
            End If
        Case 1
            If OpenPhone Then
                OutputData = 2
                Connect.SendData OutputData '发送数据
                Message "主叫方正在通话..."
                Command1.Enabled = False
                Command2.Enabled = True
                Text1.Enabled = False
            Else
                OutputData = 3
                Connect.SendData OutputData '发送数据
                MsgBox "本机无法打开音频设备", vbOKOnly, ""
            End If
        Case 2
            Message "被叫方正在通话..."
            Command1.Enabled = False
            Command2.Enabled = True
            Text1.Text = Connect.RemoteHostIP
            Text1.Enabled = False
        Case 3
            Disconnect
            MsgBox "对方无法开始通话，连接终止", vbOKOnly, "终止"
        Case 4
            Disconnect
            MsgBox "对方挂断，连接终止", vbOKOnly, "终止"
    End Select
End Sub

Private Sub Connect_Error(ByVal Number As Integer, Description As String, ByVal Scode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    Disconnect
End Sub

Private Sub Form_Load()
    Dim CurrentDrive As String
    
    CurrentDrive = Left(App.Path, 1)  '获得当前工程所在驱动器号
    ChDrive CurrentDrive '设置当前驱动器
    ChDir App.Path '设置当前目录，以上设置用于实现对工程目录中 phone.dll 文件的调用
    Listen.LocalPort = TcpPort
    Listen.Listen '开始监听
    Message "正在监听网络..."
End Sub

Private Sub Disconnect()
    Connect.Close
    Listen.Listen
    ClosePhone
    Message "正在监听网络..."
    Command1.Enabled = True
    Command2.Enabled = False
    Text1.Enabled = True
End Sub

Private Sub Connecting()
    Listen.Close
    Connect.RemoteHost = Text1.Text
    Connect.RemotePort = TcpPort
    Connect.Connect
    Message "开始申请连接..."
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Connect.Close
    Listen.Close
    ClosePhone
End Sub

Private Sub Listen_ConnectionRequest(ByVal requestID As Long)
'有连接申请时，触发该函数
    Message "收到连接申请"
    Listen.Close
    Connect.Accept requestID
End Sub

Private Sub Message(s As String)
'显示信息函数
    StatusBar1.SimpleText = s
End Sub

Private Function OpenPhone() As Boolean
    Dim Sta As Long
    Dim ErrString As String
    
    '调用 StartPhone 函数开始通话
    '第一个参数必须是IP地址，否则无法接听对方声音
    '如果调用成功，函数返回 0
    Sta = StartPhone(Connect.RemoteHostIP, LocalPort, RemotePort)
    Select Case Sta
        Case 0
            OpenPhone = True
            Exit Function
        Case -1
            ErrString = "设备正在使用"
        Case -2
            ErrString = "主机地址为空，请检查函数调用参数"
        Case -3
            ErrString = "套接字创建失败，无法实现网络通信"
        Case 1
            ErrString = "播音设备被其他程序占用"
        Case 2
            ErrString = "录音设备打开失败，可能声卡不支持全双工"
        Case 3
            ErrString = "无法锁定录音内存"
        Case 4
            ErrString = "无法增加录音内存"
        Case 5
            ErrString = "无法开始录音"
    End Select
    Message ErrString
    OpenPhone = False '返回值
End Function

Private Sub Text1_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
    '回车符的 ASCII 码值为 13
        Command1_Click
    End If
End Sub
