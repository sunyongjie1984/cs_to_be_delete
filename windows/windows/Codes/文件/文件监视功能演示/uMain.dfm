object frmMain: TfrmMain
  Left = 192
  Top = 133
  Width = 544
  Height = 442
  Color = clBtnFace
  Font.Charset = GB2312_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  DesignSize = (
    536
    415)
  PixelsPerInch = 96
  TextHeight = 12
  object bvlLine: TBevel
    Left = 8
    Top = 376
    Width = 521
    Height = 3
    Shape = bsBottomLine
  end
  object mmoResult: TMemo
    Left = 8
    Top = 8
    Width = 521
    Height = 361
    Anchors = [akLeft, akTop, akRight, akBottom]
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object btnStart: TButton
    Left = 8
    Top = 385
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #24320#22987#30417#35270'(&S)'
    TabOrder = 1
    OnClick = btnStartClick
  end
  object btnStop: TButton
    Left = 96
    Top = 385
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #20572#27490#30417#35270'(&P)'
    TabOrder = 2
    OnClick = btnStopClick
  end
  object btnAbout: TButton
    Left = 184
    Top = 384
    Width = 75
    Height = 25
    Caption = #20851#20110#31243#24207'(&A)'
    TabOrder = 3
    OnClick = btnAboutClick
  end
end
