VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form Form1 
   BackColor       =   &H00808080&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Port Mapper"
   ClientHeight    =   2400
   ClientLeft      =   150
   ClientTop       =   435
   ClientWidth     =   5040
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   2400
   ScaleWidth      =   5040
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame5 
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      ForeColor       =   &H000000FF&
      Height          =   375
      Left            =   0
      TabIndex        =   14
      Top             =   2040
      Width           =   1575
   End
   Begin VB.Frame Frame2 
      BackColor       =   &H00000000&
      Caption         =   "Remote Admin"
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   0
      TabIndex        =   5
      Top             =   1440
      Width           =   1575
      Begin VB.CheckBox Check1 
         BackColor       =   &H00000000&
         Caption         =   "Remote Admin"
         Enabled         =   0   'False
         ForeColor       =   &H000000FF&
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   240
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      BackColor       =   &H00000000&
      Caption         =   "Winsock Settings"
      ForeColor       =   &H000000FF&
      Height          =   1455
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   1575
      Begin VB.TextBox Text2 
         BackColor       =   &H00404040&
         ForeColor       =   &H00FFFFFF&
         Height          =   285
         Left            =   120
         TabIndex        =   4
         Top             =   1080
         Width           =   1335
      End
      Begin VB.TextBox Text1 
         BackColor       =   &H00404040&
         ForeColor       =   &H00FFFFFF&
         Height          =   285
         Left            =   120
         TabIndex        =   2
         Top             =   480
         Width           =   1335
      End
      Begin VB.Label Label2 
         BackStyle       =   0  'Transparent
         Caption         =   "Sending Port:"
         ForeColor       =   &H000000FF&
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   840
         Width           =   975
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "Listing Port:"
         ForeColor       =   &H000000FF&
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   855
      End
   End
   Begin VB.Frame Frame4 
      BackColor       =   &H00404040&
      BorderStyle     =   0  'None
      Caption         =   "Frame4"
      Height          =   2055
      Left            =   1560
      TabIndex        =   13
      Top             =   360
      Width           =   135
   End
   Begin VB.ListBox List2 
      BackColor       =   &H00C0C0C0&
      Height          =   1620
      Left            =   3360
      TabIndex        =   12
      Top             =   720
      Width           =   1575
   End
   Begin VB.ListBox List1 
      BackColor       =   &H00C0C0C0&
      Height          =   1620
      Left            =   1800
      TabIndex        =   11
      Top             =   720
      Width           =   1455
   End
   Begin VB.Frame Frame3 
      BackColor       =   &H00000000&
      BorderStyle     =   0  'None
      Height          =   255
      Left            =   0
      TabIndex        =   7
      Top             =   0
      Width           =   5055
      Begin VB.Label Label5 
         BackColor       =   &H00000000&
         Caption         =   "Start"
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   3360
         TabIndex        =   17
         Top             =   0
         Width           =   375
      End
      Begin VB.Label Label6 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "Pause"
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   2520
         TabIndex        =   10
         Top             =   0
         Width           =   735
      End
      Begin VB.Label Label4 
         Alignment       =   2  'Center
         BackStyle       =   0  'Transparent
         Caption         =   "Exit"
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   1680
         TabIndex        =   9
         Top             =   0
         Width           =   855
      End
   End
   Begin MSWinsockLib.Winsock Socket 
      Index           =   0
      Left            =   0
      Top             =   0
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label Label8 
      BackStyle       =   0  'Transparent
      Caption         =   "Internet IP Address:"
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3360
      TabIndex        =   16
      Top             =   480
      Width           =   1575
   End
   Begin VB.Label Label7 
      BackStyle       =   0  'Transparent
      Caption         =   "Private IP Address:"
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   1800
      TabIndex        =   15
      Top             =   480
      Width           =   1455
   End
   Begin VB.Label Label3 
      BackColor       =   &H00404040&
      Height          =   135
      Left            =   1560
      TabIndex        =   8
      Top             =   240
      Width           =   3495
   End
   Begin VB.Menu mnuList1 
      Caption         =   "mnuList1"
      Visible         =   0   'False
      Begin VB.Menu Add 
         Caption         =   "Add"
      End
      Begin VB.Menu Sep 
         Caption         =   "-"
      End
      Begin VB.Menu Remove 
         Caption         =   "Remove"
      End
   End
   Begin VB.Menu mnuList2 
      Caption         =   "mnuList2"
      Visible         =   0   'False
      Begin VB.Menu Add1 
         Caption         =   "Add"
      End
      Begin VB.Menu Sep2 
         Caption         =   "-"
      End
      Begin VB.Menu Remove1 
         Caption         =   "Remove"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Paused As Boolean
 
Private Sub Add_Click()
Form2.Show
End Sub

Private Sub Add1_Click()
Form2.Show
End Sub

Private Sub Form_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
If RespondToTray(X) <> 0 Then Call ShowFormAgain(Me)
End Sub

Private Sub Form_Unload(Cancel As Integer)
WriteSettings
Call RemoveFromTray
Socket(1).Close: Unload Socket(1)
End
End Sub

Private Sub Form_Load()
'Get Config
GetConfig
'Load Socket 1
Load Socket(1)
'Listen
Listen
End Sub

Private Sub Form_Resize()
If (Me.WindowState = 1) Then
AddToTray Me.Icon, "Port Mapper", Me
Me.WindowState = 0
End If
End Sub

Private Sub Label4_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Label4.Left = Label4.Left + 35
Label4.Top = Label4.Top + 35
End Sub

Private Sub Label4_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
Label4.Left = Label4.Left - 35
Label4.Top = Label4.Top - 35
Form_Unload (1)
End
End Sub

Private Sub Label5_Click()
Listen
End Sub

Private Sub Label6_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Label6.Top = Label6.Top + 35
Label6.Left = Label6.Left + 35
End Sub

Private Sub Label6_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
Label6.Top = 0
Label6.Left = 2520
'Event
If (Paused = True) Then
Paused = False
Label6.FontItalic = False
Else
Paused = True
Label6.FontItalic = True
End If
End Sub

Private Sub List1_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
If (Button = 2) Then
Me.PopupMenu mnuList1, , X + 1100, Y + 500
End If
End Sub

Private Sub List2_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
If (Button = 2) Then
Me.PopupMenu mnuList2, , X + 2500, Y + 500
End If
End Sub

Private Sub Remove_Click()
a = MsgBox("Are you sure you want to do this?", vbOKCancel, "Remove Item")
'ok
If (a = 1) Then
For a = 0 To List1.ListCount
If (List1.List(a) = List1) Then
List1.RemoveItem (a)
List2.RemoveItem (a)
WriteSettings
Exit Sub
End If
Next a
End If
End Sub

Private Sub GetConfig()
On Error Resume Next
Open App.Path + "\" + "Settings.ini" For Input As #1
Do
Line Input #1, Data$

If (InStr(UCase$(Data$), UCase$("ListingPort=")) <> 0) Then
Text1.Text = Right$(Data$, Len(Data$) - 12)
End If

If (InStr(UCase$(Data$), UCase$("SendingPort=")) <> 0) Then
Text2.Text = Right$(Data$, Len(Data$) - 12)
End If

If (InStr(UCase$(Data$), UCase$("RemoteAdmin=")) <> 0) Then
Value$ = Right$(Data$, Len(Data$) - 12)
If (Value$ = True) Then
Check1.Value = 1
Else
Check1.Value = 0
End If
End If

If (InStr(UCase$(Data$), UCase$("PrivateIPs=")) <> 0) Then
Code$ = Right$(Data$, Len(Data$) - 11)
List1.Clear
For Location = 1 To Len(Code$)
 Letter$ = Mid$(Code$, Location, 1)
  If (Letter$ = ",") Then
   If (Word$ <> "") Then List1.AddItem (Word$)
   Word$ = ""
  End If
 If (Letter$ <> ",") Then Word$ = Word$ + Letter$
Next Location
If (Word$ <> "") Then List1.AddItem (Word$)
Word$ = ""
End If

If (InStr(UCase$(Data$), UCase$("InternetIPs=")) <> 0) Then
Code$ = Right$(Data$, Len(Data$) - 12)
List2.Clear
For Location = 1 To Len(Code$)
 Letter$ = Mid$(Code$, Location, 1)
  If (Letter$ = ",") Then
   If (Word$ <> "") Then List2.AddItem (Word$)
   Word$ = ""
  End If
 If (Letter$ <> ",") Then Word$ = Word$ + Letter$
Next Location
If (Word$ <> "") Then List2.AddItem (Word$)
Word$ = ""
End If
Loop Until EOF(1)
Close #1
End Sub

Public Sub WriteSettings()
File% = FreeFile
Open App.Path + "\" + "Settings.ini" For Output As #File%

TheIps$ = ""
 If (List2.ListCount <> 0) Then
  For Location = 0 To List2.ListCount
   TheIps$ = TheIps$ + List2.List(Location) + ","
  Next Location
  TheIps$ = Left$(TheIps$, Len(TheIps$) - 1)
 End If
 Print #File%, "InternetIPs=" + TheIps$
 
TheIps$ = ""
 If (List1.ListCount <> 0) Then
  For Location = 0 To List1.ListCount
   TheIps$ = TheIps$ + List1.List(Location) + ","
  Next Location
  TheIps$ = Left$(TheIps$, Len(TheIps$) - 1)
 End If
 Print #File%, "PrivateIPs=" + TheIps$
 
 If (Check1.Value = 1) Then
 Print #File%, "RemoteAdmin=" + "True"
 Else
 Print #File%, "RemoteAdmin=" + "False"
 End If
 
 Print #File%, "ListingPort=" + Text1.Text
 
 Print #File%, "SendingPort=" + Text2.Text

Close #File%
End Sub

Private Sub Remove1_Click()
a = MsgBox("Are you sure you want to do this?", vbOKCancel, "Remove Item")
'ok
If (a = 1) Then
For a = 0 To List2.ListCount
If (List2.List(a) = List2) Then
List2.RemoveItem (a)
List1.RemoveItem (a)
WriteSettings
Exit Sub
End If
Next a
End If
End Sub

Private Sub Socket_DataArrival(Index As Integer, ByVal bytesTotal As Long)
If (Paused = False) Then

'Get Data
Socket(1).GetData Data$
'Check For User On Internet List

For a = 0 To List1.ListCount
If (List1.List(a) = Socket(1).RemoteHostIP) Then
'We Know Its a user.. we have to send the data to the ip adjacent
RedirectIP$ = List2.List(a)
'Now we have the ip, lets redirect the data
SendData RedirectIP$, Text2.Text, Data$
End If
Next a

For a = 0 To List2.ListCount
If (List2.List(a) = Socket(1).RemoteHostIP) Then
'We Know Its a user.. we have to send the data to the ip adjacent
RedirectIP$ = List1.List(a)
'Now we have the ip, lets redirect the data
SendData RedirectIP$, Text2.Text, Data$
End If
Next a

End If
End Sub

Private Sub Text1_Change()
'WriteSettings
End Sub

Private Sub Text2_Change()
'WriteSettings
End Sub

Private Sub SendData(IP As String, Port As Integer, Data As String)
On Error Resume Next
'Use main Socket for transmitting data (If you spawn a socket it will crash)
Socket(0).Protocol = sckUDPProtocol
Socket(0).RemoteHost = IP
Socket(0).RemotePort = Port
Socket(0).Bind
Socket(0).SendData Data
Socket(0).Close
End Sub

Private Sub Listen()
On Error GoTo Crash
Socket(1).Close
Socket(1).LocalPort = Text1.Text
Socket(1).Protocol = sckUDPProtocol
Socket(1).Bind
Label5.Visible = False
Exit Sub
Crash:
MsgBox "An Error Occured While Trying To Start Winsock! Listing Aborted!", vbCritical, "Winsock Error!"
Label5.Visible = True
End Sub
