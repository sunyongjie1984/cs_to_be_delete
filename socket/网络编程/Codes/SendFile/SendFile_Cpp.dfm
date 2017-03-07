object SendFiles: TSendFiles
  Left = 297
  Top = 106
  Width = 288
  Height = 200
  Caption = #20256#36865#25991#20214
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #23435#20307
  Font.Style = []
  FormStyle = fsStayOnTop
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF004333
    3333333333333333333333333333333333333333333333333333333333333330
    0003333300003333300003333333333300333333300333333300333333333333
    0033333300333333300333333333333300333330033333333003333033333333
    0033330033333333300333300333333300033000333333333003333000333333
    3000300033333333000333303003303338000000333333300003333330030033
    3800000033333300000333330003000330008800000000008000330000330003
    30088880000088088800000003338003308888888008888FFF80000033338003
    30888FFF8088FFFF08880003333308030088FFFFF88FFFF0F088003333330800
    0088FF0FFFFFFFFFFF0803333333008000088FF000FF88FFFF80033333330003
    300088008FF8888FFF800333303330333388000000F80888FFF0033030003333
    33300088FF8000888FF0000030003333333000000800000888F0000808803333
    30008888F8080000888088FF880033330000000F800F80000888F0F880033330
    088888F800F880000088F0080033330000008F800F00003000088F8003333000
    88FF8800F8880033000088000333000888880003000003333000080033330000
    0000033333333333330000033333333333333333333333333303003333333333
    3333333333333333333333333333333333333333333333333333333333330000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Scaled = False
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Notebook1: TNotebook
    Left = 0
    Top = 0
    Width = 280
    Height = 133
    Align = alClient
    TabOrder = 0
    object TPage
      Left = 0
      Top = 0
      Caption = 'Main'
      object Panel1: TPanel
        Left = 224
        Top = 0
        Width = 56
        Height = 133
        Align = alRight
        BevelOuter = bvLowered
        BevelWidth = 2
        TabOrder = 0
        object Speed: TSpeedButton
          Left = 8
          Top = 103
          Width = 41
          Height = 18
          Hint = #33258#21160#35843#25972#21040#26368#20339#36895#24230
          AllowAllUp = True
          GroupIndex = 1
          Down = True
          Caption = #33258#21160
          ParentShowHint = False
          ShowHint = True
          OnClick = SpeedClick
        end
        object Add: TButton
          Left = 8
          Top = 7
          Width = 41
          Height = 21
          Caption = #28155#21152
          TabOrder = 0
          OnClick = AddClick
        end
        object Sent: TButton
          Left = 8
          Top = 48
          Width = 41
          Height = 19
          Caption = #21457#36865
          Enabled = False
          TabOrder = 1
          OnClick = SentClick
        end
        object SetUp: TButton
          Left = 8
          Top = 85
          Width = 41
          Height = 18
          Caption = #35774#32622
          TabOrder = 2
          OnClick = SetUpClick
        end
        object Clear: TButton
          Left = 8
          Top = 28
          Width = 41
          Height = 20
          Caption = #28165#38500
          TabOrder = 3
          OnClick = ClearClick
        end
        object Cancel: TButton
          Left = 8
          Top = 67
          Width = 41
          Height = 18
          Caption = #21462#28040
          Enabled = False
          TabOrder = 4
          OnClick = CancelClick
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 224
        Height = 133
        Align = alClient
        Caption = 'Panel2'
        TabOrder = 1
        object PageControl1: TPageControl
          Left = 1
          Top = 1
          Width = 222
          Height = 131
          ActivePage = TabSheet1
          Align = alClient
          TabIndex = 0
          TabOrder = 0
          object TabSheet1: TTabSheet
            Caption = #25991#20214
            object ListView1: TListView
              Left = 0
              Top = 0
              Width = 214
              Height = 103
              Align = alClient
              Columns = <
                item
                  Caption = #24453#20256#36865#30340#25991#20214':'
                  Width = 170
                end>
              ColumnClick = False
              HideSelection = False
              ReadOnly = True
              RowSelect = True
              TabOrder = 0
              ViewStyle = vsReport
              OnResize = ListView1Resize
            end
          end
          object TabSheet2: TTabSheet
            Caption = #25910#21457#32426#24405
            ImageIndex = 1
            object Splitter1: TSplitter
              Left = 107
              Top = 13
              Width = 3
              Height = 90
              Cursor = crHSplit
            end
            object Label6: TLabel
              Left = 0
              Top = 0
              Width = 143
              Height = 13
              Align = alTop
              Caption = #21457#36865':           '#25509#25910':'
            end
            object FRError: TMemo
              Left = 110
              Top = 13
              Width = 54
              Height = 90
              Align = alClient
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
            end
            object FSRepa: TMemo
              Left = 0
              Top = 13
              Width = 57
              Height = 90
              Align = alLeft
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -10
              Font.Name = 'Arial'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
            end
            object FRCMDS: TMemo
              Left = 57
              Top = 13
              Width = 50
              Height = 90
              Align = alLeft
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = #23435#20307
              Font.Style = []
              ParentFont = False
              TabOrder = 2
            end
            object FSCMDS: TMemo
              Left = 164
              Top = 13
              Width = 50
              Height = 90
              Align = alRight
              Font.Charset = GB2312_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = #23435#20307
              Font.Style = []
              ParentFont = False
              TabOrder = 3
            end
          end
        end
      end
    end
    object TPage
      Left = 0
      Top = 0
      Caption = 'SetUp'
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 224
        Height = 133
        Align = alClient
        TabOrder = 0
        object Bevel1: TBevel
          Left = 3
          Top = 2
          Width = 217
          Height = 55
        end
        object Bevel2: TBevel
          Left = 5
          Top = 6
          Width = 33
          Height = 46
          Style = bsRaised
        end
        object Label2: TLabel
          Left = 66
          Top = 11
          Width = 21
          Height = 13
          Caption = 'IP:'
        end
        object Label3: TLabel
          Left = 52
          Top = 33
          Width = 35
          Height = 13
          Caption = 'Port:'
        end
        object Label4: TLabel
          Left = 9
          Top = 9
          Width = 26
          Height = 39
          Caption = #20256#36865' '#25991#20214#21040#65306
          Transparent = True
          WordWrap = True
        end
        object Label5: TLabel
          Left = 81
          Top = 69
          Width = 78
          Height = 13
          Caption = #20445#23384#25991#20214#21040#65306
        end
        object Label1: TLabel
          Left = 148
          Top = 33
          Width = 33
          Height = 13
          Caption = #36229#26102':'
        end
        object RemoteIP: TEdit
          Left = 94
          Top = 7
          Width = 122
          Height = 21
          TabOrder = 0
          Text = '192.168.1.30'
        end
        object RemotePort: TEdit
          Left = 94
          Top = 29
          Width = 50
          Height = 21
          TabOrder = 1
          Text = '6667'
        end
        object Dir: TEdit
          Left = 80
          Top = 94
          Width = 121
          Height = 21
          TabOrder = 2
        end
        object Button5: TButton
          Left = 200
          Top = 92
          Width = 20
          Height = 24
          Caption = '...'
          Font.Charset = GB2312_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = '??'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          OnClick = Button5Click
        end
        object MaxTimeOut: TEdit
          Left = 182
          Top = 29
          Width = 34
          Height = 21
          TabOrder = 4
          Text = '60'
        end
        object ReciveType: TRadioGroup
          Left = 2
          Top = 61
          Width = 71
          Height = 54
          Caption = #25509#25910#25991#20214
          ItemIndex = 1
          Items.Strings = (
            #26080#26465#20214
            #25552#31034
            #25298#32477)
          TabOrder = 5
        end
      end
      object Panel3: TPanel
        Left = 224
        Top = 0
        Width = 56
        Height = 133
        Align = alRight
        TabOrder = 1
        object Button4: TButton
          Left = 8
          Top = 40
          Width = 41
          Height = 49
          Caption = #23436#25104
          TabOrder = 0
          OnClick = Button4Click
        end
      end
    end
    object TPage
      Left = 0
      Top = 0
      Caption = 'ShowProce'
    end
  end
  object FRStatusBar: TStatusBar
    Left = 0
    Top = 153
    Width = 280
    Height = 20
    Panels = <
      item
        Text = #25509#25910
        Width = 30
      end
      item
        Width = 125
      end
      item
        Width = 55
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object FSStatusBar: TStatusBar
    Left = 0
    Top = 133
    Width = 280
    Height = 20
    Panels = <
      item
        Text = #21457#36865
        Width = 30
      end
      item
        Width = 125
      end
      item
        Width = 55
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object OpenDialog1: TOpenDialog
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Title = #36873#25321#25991#20214
    Left = 184
    Top = 144
  end
  object NMUDP1: TNMUDP
    RemoteHost = '192.168.1.30'
    RemotePort = 6667
    LocalPort = 6667
    ReportLevel = 1
    OnDataReceived = NMUDP1DataReceived
    Left = 218
    Top = 144
  end
  object FSTimer: TTimer
    Enabled = False
    OnTimer = FSTimerTimer
    Left = 148
    Top = 144
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 248
    Top = 144
  end
end
