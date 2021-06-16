object Form8: TForm8
  Left = 0
  Top = 0
  Caption = 'Form8'
  ClientHeight = 651
  ClientWidth = 266
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 16
    Width = 197
    Height = 13
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1082#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1087#1086#1083#1080#1085#1086#1084' '#1062#1077#1088#1085#1080#1082#1077
  end
  object Label2: TLabel
    Left = 8
    Top = 117
    Width = 101
    Height = 13
    Caption = 'm<=n, n-m - '#1095#1077#1090#1085#1086#1077
    Visible = False
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 136
    Width = 203
    Height = 504
    ColCount = 3
    FixedCols = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    ParentFont = False
    TabOrder = 0
    Visible = False
  end
  object Edit1: TEdit
    Left = 8
    Top = 35
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '1'
  end
  object Button1: TButton
    Left = 8
    Top = 75
    Width = 75
    Height = 25
    Caption = #1086#1082
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 208
    Top = 292
    Width = 59
    Height = 25
    Caption = #1086#1082
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 208
    Top = 331
    Width = 59
    Height = 25
    Caption = #1086#1090#1084#1077#1085#1072
    TabOrder = 4
    OnClick = Button3Click
  end
end
