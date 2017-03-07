VERSION 5.00
Begin VB.Form Form2 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Add IPs"
   ClientHeight    =   3540
   ClientLeft      =   45
   ClientTop       =   360
   ClientWidth     =   4245
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   ScaleHeight     =   3540
   ScaleWidth      =   4245
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command5 
      Caption         =   "Remove"
      Height          =   255
      Left            =   2160
      TabIndex        =   9
      Top             =   2880
      Width           =   2055
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Add"
      Height          =   255
      Left            =   0
      TabIndex        =   8
      Top             =   2880
      Width           =   2055
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
      Height          =   255
      Left            =   2160
      TabIndex        =   7
      Top             =   3240
      Width           =   2055
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   255
      Left            =   0
      TabIndex        =   6
      Top             =   3240
      Width           =   2055
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   2160
      TabIndex        =   3
      Top             =   2520
      Width           =   2055
   End
   Begin VB.ListBox List2 
      Height          =   2205
      Left            =   2160
      TabIndex        =   2
      Top             =   240
      Width           =   2055
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   0
      TabIndex        =   1
      Top             =   2520
      Width           =   2055
   End
   Begin VB.ListBox List1 
      Height          =   2205
      Left            =   0
      TabIndex        =   0
      Top             =   240
      Width           =   2055
   End
   Begin VB.Label Label2 
      Alignment       =   2  'Center
      Caption         =   "Private IP:"
      Height          =   255
      Left            =   0
      TabIndex        =   5
      Top             =   0
      Width           =   2055
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Internet IP:"
      Height          =   255
      Left            =   2160
      TabIndex        =   4
      Top             =   0
      Width           =   2055
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
'Save thing...
Form1.List1.Clear
Form1.List2.Clear
If (List1.ListCount <> 0) Then
For a = 0 To List1.ListCount - 1
 Form1.List1.AddItem List1.List(a)
Next a
End If
If (List2.ListCount <> 0) Then
For a = 0 To List2.ListCount - 1
 Form1.List2.AddItem List2.List(a)
Next a
End If
Me.Hide
End Sub

Private Sub Command2_Click()
Me.Hide
End Sub

Private Sub Command3_Click()
If (Text1.Text <> "") Then
List1.AddItem Text1.Text
List2.AddItem Text2.Text
Text1.Text = ""
Text2.Text = ""
End If
End Sub

Private Sub Command5_Click()
If (List1 <> "") Then
 For a = 0 To List1.ListCount - 1
  If (List1.Selected(a) = True) Then
    List1.RemoveItem (a)
    List2.RemoveItem (a)
    Exit Sub
  End If
 Next a
End If
End Sub

Private Sub Form_Load()
List1.Clear
List2.Clear
If (Form1.List1.ListCount <> 0) Then
For a = 0 To Form1.List1.ListCount - 1
DoEvents
List1.AddItem Form1.List1.List(a)
Next a
End If
If (Form1.List2.ListCount <> 0) Then
For a = 0 To Form1.List2.ListCount - 1
DoEvents
List1.AddItem Form1.List2.List(a)
Next a
End If
End Sub
