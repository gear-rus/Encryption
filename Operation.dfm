object OpWindow: TOpWindow
  Left = 533
  Top = 81
  Cursor = crArrow
  BorderStyle = bsToolWindow
  Caption = 'Operation'
  ClientHeight = 223
  ClientWidth = 600
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Droid'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 15
  object i: TLabel
    Left = 8
    Top = 8
    Width = 66
    Height = 15
    Caption = 'Input File:'
  end
  object o: TLabel
    Left = 8
    Top = 73
    Width = 79
    Height = 15
    Caption = 'Output File:'
  end
  object ipath: TLabel
    Left = 8
    Top = 31
    Width = 35
    Height = 15
    Caption = 'ipath'
  end
  object opath: TLabel
    Left = 8
    Top = 96
    Width = 41
    Height = 15
    Caption = 'Opath'
  end
  object percentage: TLabel
    Left = 551
    Top = 159
    Width = 43
    Height = 15
    Caption = '100.0%'
  end
  object isize: TLabel
    Left = 8
    Top = 52
    Width = 32
    Height = 15
    Caption = 'isize'
  end
  object osize: TLabel
    Left = 8
    Top = 117
    Width = 36
    Height = 15
    Caption = 'osize'
  end
  object Elapsed: TLabel
    Left = 184
    Top = 195
    Width = 3
    Height = 15
  end
  object mainBar: TProgressBar
    Left = 8
    Top = 149
    Width = 537
    Height = 33
    Step = 1
    TabOrder = 0
  end
  object autoClose: TCheckBox
    Left = 8
    Top = 194
    Width = 169
    Height = 17
    Caption = 'Close after completion'
    TabOrder = 1
    OnClick = autoCloseClick
  end
  object cancelOp: TButton
    Left = 493
    Top = 188
    Width = 103
    Height = 29
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = cancelOpClick
  end
  object pauseThread: TButton
    Left = 370
    Top = 188
    Width = 103
    Height = 29
    Caption = 'Pause'
    TabOrder = 3
    OnClick = pauseThreadClick
  end
end
