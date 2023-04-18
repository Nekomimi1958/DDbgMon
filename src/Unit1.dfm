object DDbgMonFrm: TDDbgMonFrm
  Left = 0
  Top = 0
  AlphaBlend = True
  Caption = 'Dual Debug Monitor'
  ClientHeight = 465
  ClientWidth = 668
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  ShowHint = True
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  TextHeight = 15
  object Splitter1: TSplitter
    Left = 473
    Top = 0
    Width = 5
    Height = 465
    Beveled = True
    ExplicitLeft = 537
    ExplicitHeight = 498
  end
  object OpePanel: TPanel
    Left = 0
    Top = 0
    Width = 273
    Height = 465
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 0
      Top = 0
      Width = 273
      Height = 465
      ActivePage = MonitorSheet
      Align = alClient
      TabOrder = 0
      TabWidth = 100
      object MonitorSheet: TTabSheet
        Caption = 'Monitor'
        DesignSize = (
          265
          435)
        object Button1: TButton
          Left = 31
          Top = 297
          Width = 90
          Height = 24
          Action = StartAction
          TabOrder = 3
        end
        object Button2: TButton
          Left = 145
          Top = 297
          Width = 90
          Height = 24
          Action = StopAction
          TabOrder = 4
        end
        object GroupBox1: TGroupBox
          Left = 3
          Top = 3
          Width = 259
          Height = 110
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Process 1'
          TabOrder = 0
          DesignSize = (
            259
            110)
          object PidEdit1: TLabeledEdit
            Left = 36
            Top = 78
            Width = 60
            Height = 23
            Alignment = taRightJustify
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 18
            EditLabel.Height = 23
            EditLabel.Caption = 'PID'
            LabelPosition = lpLeft
            NumbersOnly = True
            ReadOnly = True
            TabOrder = 2
            Text = ''
          end
          object SearchBtn1: TButton
            Left = 216
            Top = 67
            Width = 34
            Height = 34
            Action = FindAction
            ImageIndex = 2
            Images = ImageList1
            TabOrder = 5
          end
          object TargetPanel1: TPanel
            Left = 216
            Top = 24
            Width = 34
            Height = 34
            BevelOuter = bvLowered
            TabOrder = 4
            object CapToolImage1: TImage
              Left = 1
              Top = 1
              Width = 32
              Height = 32
              Hint = 'Find Window'#39's Process (drag over window)'
              Align = alClient
              OnMouseDown = CapToolImage1MouseDown
              OnMouseUp = CapToolImage1MouseUp
              ExplicitLeft = 8
              ExplicitTop = 8
              ExplicitWidth = 105
              ExplicitHeight = 105
            end
          end
          object TextEdit1: TLabeledEdit
            Left = 35
            Top = 49
            Width = 176
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 21
            EditLabel.Height = 23
            EditLabel.Caption = 'Text'
            LabelPosition = lpLeft
            TabOrder = 1
            Text = ''
          end
          object ClassEdit1: TLabeledEdit
            Left = 36
            Top = 24
            Width = 176
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 27
            EditLabel.Height = 23
            EditLabel.Caption = 'Class'
            LabelPosition = lpLeft
            TabOrder = 0
            Text = ''
          end
          object HWndEdit1: TLabeledEdit
            Left = 150
            Top = 78
            Width = 62
            Height = 23
            Alignment = taRightJustify
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 38
            EditLabel.Height = 23
            EditLabel.Caption = 'Handle'
            LabelPosition = lpLeft
            NumbersOnly = True
            ReadOnly = True
            TabOrder = 3
            Text = ''
          end
        end
        object GroupBox2: TGroupBox
          Left = 3
          Top = 121
          Width = 259
          Height = 110
          Caption = 'Process 2'
          TabOrder = 1
          DesignSize = (
            259
            110)
          object ClassEdit2: TLabeledEdit
            Left = 36
            Top = 24
            Width = 176
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 27
            EditLabel.Height = 23
            EditLabel.Caption = 'Class'
            LabelPosition = lpLeft
            TabOrder = 0
            Text = ''
          end
          object PidEdit2: TLabeledEdit
            Left = 36
            Top = 78
            Width = 60
            Height = 23
            Alignment = taRightJustify
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 18
            EditLabel.Height = 23
            EditLabel.Caption = 'PID'
            LabelPosition = lpLeft
            NumbersOnly = True
            ReadOnly = True
            TabOrder = 2
            Text = ''
          end
          object SearchBtn2: TButton
            Tag = 1
            Left = 216
            Top = 67
            Width = 34
            Height = 34
            Action = Find2Action
            ImageIndex = 2
            Images = ImageList1
            TabOrder = 5
          end
          object TargetPanel2: TPanel
            Left = 216
            Top = 24
            Width = 34
            Height = 34
            BevelOuter = bvLowered
            TabOrder = 4
            object CapToolImage2: TImage
              Tag = 1
              Left = 1
              Top = 1
              Width = 32
              Height = 32
              Hint = #12454#12451#12531#12489#12454#12395#12489#12521#12483#12464#12375#12390#12503#12525#12475#12473#12434#36984#25246
              Align = alClient
              OnMouseDown = CapToolImage1MouseDown
              OnMouseUp = CapToolImage1MouseUp
              ExplicitLeft = 8
              ExplicitTop = 8
              ExplicitWidth = 105
              ExplicitHeight = 105
            end
          end
          object TextEdit2: TLabeledEdit
            Left = 36
            Top = 51
            Width = 176
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 21
            EditLabel.Height = 23
            EditLabel.Caption = 'Text'
            LabelPosition = lpLeft
            TabOrder = 1
            Text = ''
          end
          object HWndEdit2: TLabeledEdit
            Left = 150
            Top = 78
            Width = 62
            Height = 23
            Alignment = taRightJustify
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 38
            EditLabel.Height = 23
            EditLabel.Caption = 'Handle'
            LabelPosition = lpLeft
            NumbersOnly = True
            ReadOnly = True
            TabOrder = 3
            Text = ''
          end
        end
        object ModeRadioGroup: TRadioGroup
          Left = 3
          Top = 237
          Width = 259
          Height = 44
          Caption = 'Log Display Mode'
          Columns = 2
          Items.Strings = (
            'Separate'
            'Synchronous')
          TabOrder = 2
          OnClick = ModeRadioGroupClick
        end
      end
      object OptionSheet: TTabSheet
        Caption = 'Option'
        ImageIndex = 1
        object TopMostCheckBox: TCheckBox
          Left = 146
          Top = 8
          Width = 110
          Height = 17
          Action = TopMostAction
          TabOrder = 1
        end
        object TransBar: TTrackBar
          Left = 9
          Top = 6
          Width = 120
          Height = 35
          Hint = 'Opacity'
          Max = 255
          Min = 64
          Frequency = 32
          Position = 64
          TabOrder = 0
          OnChange = TransBarChange
        end
        object ColorGroupBox: TGroupBox
          Left = 8
          Top = 190
          Width = 240
          Height = 116
          Caption = 'Colors'
          TabOrder = 3
          DesignSize = (
            240
            116)
          object ColorListBox: TListBox
            Left = 10
            Top = 24
            Width = 221
            Height = 84
            Style = lbOwnerDrawFixed
            Anchors = [akLeft, akTop, akRight, akBottom]
            ItemHeight = 15
            TabOrder = 0
            OnDblClick = ColorListBoxDblClick
            OnDrawItem = ColorListBoxDrawItem
          end
        end
        object PtnGroupBox: TGroupBox
          Left = 8
          Top = 45
          Width = 240
          Height = 137
          Hint = 'specify multiple by separating with '#39';'#39' (/re/)'
          Caption = 'Highlight Pattern '
          TabOrder = 2
          DesignSize = (
            240
            137)
          object Em1Edit: TLabeledEdit
            Left = 19
            Top = 24
            Width = 211
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 6
            EditLabel.Height = 23
            EditLabel.Caption = '1'
            LabelPosition = lpLeft
            TabOrder = 0
            Text = ''
          end
          object Em2Edit: TLabeledEdit
            Left = 19
            Top = 51
            Width = 211
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 6
            EditLabel.Height = 23
            EditLabel.Caption = '2'
            LabelPosition = lpLeft
            TabOrder = 1
            Text = ''
          end
          object Em3Edit: TLabeledEdit
            Left = 19
            Top = 78
            Width = 211
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 6
            EditLabel.Height = 23
            EditLabel.Caption = '3'
            LabelPosition = lpLeft
            TabOrder = 2
            Text = ''
          end
          object Em4Edit: TLabeledEdit
            Left = 19
            Top = 105
            Width = 211
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            EditLabel.Width = 6
            EditLabel.Height = 23
            EditLabel.Caption = '4'
            LabelPosition = lpLeft
            TabOrder = 3
            Text = ''
          end
        end
        object SndWatchGroupBox: TGroupBox
          Left = 8
          Top = 314
          Width = 240
          Height = 49
          Caption = 'Match Sound'
          TabOrder = 4
          DesignSize = (
            240
            49)
          object SndMatchEdit: TEdit
            Left = 10
            Top = 18
            Width = 162
            Height = 23
            Anchors = [akLeft, akTop, akRight]
            TabOrder = 0
          end
          object RefSndWatchBtn: TButton
            Tag = 3
            Left = 174
            Top = 17
            Width = 36
            Height = 22
            Hint = #21442#29031
            Anchors = [akTop, akRight]
            Caption = '...'
            TabOrder = 1
            OnClick = RefSndWatchBtnClick
          end
          object TestSndWatchBtn: TButton
            Tag = 3
            Left = 211
            Top = 17
            Width = 22
            Height = 22
            Hint = 'Test'
            Anchors = [akTop, akRight]
            Caption = '>'
            TabOrder = 2
            OnClick = TestSndWatchBtnClick
          end
        end
        object ExlcudeEdit: TLabeledEdit
          Left = 15
          Top = 391
          Width = 223
          Height = 23
          Hint = 'specify multiple by separating with '#39';'#39' (/re/)'
          EditLabel.Width = 82
          EditLabel.Height = 15
          EditLabel.Caption = 'Exclude Pattern'
          TabOrder = 5
          Text = ''
        end
      end
    end
  end
  object LogPanel1: TPanel
    Left = 273
    Top = 0
    Width = 200
    Height = 465
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object Splitter2: TSplitter
      Left = 0
      Top = 328
      Width = 200
      Height = 4
      Cursor = crVSplit
      Align = alBottom
      OnMoved = Splitter2Moved
      ExplicitTop = 301
      ExplicitWidth = 185
    end
    object LogListBox1: TListBox
      Left = 0
      Top = 29
      Width = 200
      Height = 299
      Style = lbVirtualOwnerDraw
      Align = alClient
      DoubleBuffered = False
      ParentDoubleBuffered = False
      TabOrder = 0
      OnClick = LogListBoxClick
      OnData = LogListBoxData
      OnDataObject = LogListBoxDataObject
      OnDrawItem = LogListBoxDrawItem
    end
    object ToolBar1: TToolBar
      Left = 0
      Top = 0
      Width = 200
      Height = 29
      ButtonHeight = 26
      ButtonWidth = 28
      Caption = 'ToolBar1'
      Flat = False
      Images = ImageList2
      List = True
      AllowTextButtons = True
      TabOrder = 1
      object ToolButton7: TToolButton
        Left = 0
        Top = 0
        Action = CloseAction
      end
      object ToolButton9: TToolButton
        Left = 28
        Top = 0
        Action = TerminateAction
      end
      object ToolButton10: TToolButton
        Left = 56
        Top = 0
        Width = 8
        Caption = 'ToolButton10'
        ImageIndex = 2
        Style = tbsSeparator
      end
      object ToolButton3: TToolButton
        Left = 64
        Top = 0
        Action = SaveLogAction
      end
      object ToolButton5: TToolButton
        Left = 92
        Top = 0
        Action = ClearLogAction
      end
      object ToolButton15: TToolButton
        Left = 120
        Top = 0
        Width = 8
        Caption = 'ToolButton15'
        ImageIndex = 6
        Style = tbsSeparator
      end
      object ToolButton13: TToolButton
        Left = 128
        Top = 0
        Action = TopOfLog1Action
      end
      object ToolButton1: TToolButton
        Left = 156
        Top = 0
        Action = EndOfLog1Action
      end
    end
    object MatchPanel1: TPanel
      Left = 0
      Top = 332
      Width = 200
      Height = 133
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
      object MatchListBox1: TListBox
        Left = 0
        Top = 25
        Width = 200
        Height = 108
        Style = lbOwnerDrawFixed
        Align = alClient
        DoubleBuffered = False
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = MatchListBoxClick
        OnDrawItem = LogListBoxDrawItem
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 200
        Height = 25
        Align = alTop
        AutoSize = True
        BevelOuter = bvLowered
        TabOrder = 1
        object SpeedButton1: TSpeedButton
          Left = 176
          Top = 1
          Width = 23
          Height = 23
          Action = ReMatch1Action
          Align = alRight
          ExplicitTop = 2
          ExplicitHeight = 22
        end
        object MatchComboBox1: TComboBox
          Left = 1
          Top = 1
          Width = 175
          Height = 23
          Hint = 'specify multiple by separating with '#39';'#39' (/re/)'
          Align = alClient
          TabOrder = 0
          OnChange = MatchStrChange
        end
      end
    end
  end
  object LogPanel2: TPanel
    Left = 478
    Top = 0
    Width = 190
    Height = 465
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    object Splitter3: TSplitter
      Left = 0
      Top = 328
      Width = 190
      Height = 4
      Cursor = crVSplit
      Align = alBottom
      OnMoved = Splitter3Moved
      ExplicitTop = 29
      ExplicitWidth = 212
    end
    object LogListBox2: TListBox
      Tag = 1
      Left = 0
      Top = 29
      Width = 190
      Height = 299
      Style = lbVirtualOwnerDraw
      Align = alClient
      DoubleBuffered = False
      ParentDoubleBuffered = False
      TabOrder = 0
      OnClick = LogListBoxClick
      OnData = LogListBoxData
      OnDataObject = LogListBoxDataObject
      OnDrawItem = LogListBoxDrawItem
    end
    object ToolBar2: TToolBar
      Left = 0
      Top = 0
      Width = 190
      Height = 29
      ButtonHeight = 26
      ButtonWidth = 28
      Caption = 'ToolBar1'
      Images = ImageList2
      List = True
      AllowTextButtons = True
      TabOrder = 1
      object ToolButton8: TToolButton
        Left = 0
        Top = 0
        Action = Close2Action
      end
      object ToolButton12: TToolButton
        Left = 28
        Top = 0
        Action = Terminate2Action
      end
      object ToolButton11: TToolButton
        Left = 56
        Top = 0
        Width = 8
        Caption = 'ToolButton11'
        ImageIndex = 2
        Style = tbsSeparator
      end
      object ToolButton4: TToolButton
        Left = 64
        Top = 0
        Action = SaveLog2Action
      end
      object ToolButton6: TToolButton
        Left = 92
        Top = 0
        Action = ClearLog2Action
      end
      object ToolButton16: TToolButton
        Left = 120
        Top = 0
        Width = 8
        Caption = 'ToolButton16'
        ImageIndex = 6
        Style = tbsSeparator
      end
      object ToolButton14: TToolButton
        Left = 128
        Top = 0
        Action = TopOfLog2Action
      end
      object ToolButton2: TToolButton
        Left = 156
        Top = 0
        Action = EndOfLog2Action
      end
    end
    object MatchPanel2: TPanel
      Left = 0
      Top = 332
      Width = 190
      Height = 133
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
      object MatchListBox2: TListBox
        Tag = 1
        Left = 0
        Top = 26
        Width = 190
        Height = 107
        Style = lbOwnerDrawFixed
        Align = alClient
        DoubleBuffered = False
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = MatchListBoxClick
        OnDrawItem = LogListBoxDrawItem
      end
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 190
        Height = 26
        Align = alTop
        AutoSize = True
        BevelOuter = bvLowered
        TabOrder = 1
        object SpeedButton2: TSpeedButton
          Left = 166
          Top = 1
          Width = 23
          Height = 24
          Action = ReMatch2Action
          Align = alRight
          ExplicitTop = 2
          ExplicitHeight = 23
        end
        object MatchComboBox2: TComboBox
          Tag = 1
          Left = 1
          Top = 1
          Width = 165
          Height = 23
          Hint = ';'#12391#21306#20999#12387#12390#35079#25968#25351#23450#21487#12289'/'#65374'/ '#12399#27491#35215#34920#29694
          Align = alClient
          TabOrder = 0
          OnChange = MatchStrChange
        end
      end
    end
  end
  object ActionList1: TActionList
    Images = ImageList2
    Left = 304
    Top = 40
    object FindAction: TAction
      Hint = 'Find Process'
      OnExecute = FindActionExecute
      OnUpdate = FindActionUpdate
    end
    object Find2Action: TAction
      Tag = 1
      Hint = 'Find Process'
      OnExecute = FindActionExecute
      OnUpdate = FindActionUpdate
    end
    object StartAction: TAction
      Caption = 'Start'
      OnExecute = StartActionExecute
      OnUpdate = StartActionUpdate
    end
    object StopAction: TAction
      Caption = 'Stop'
      OnExecute = StopActionExecute
      OnUpdate = StopActionUpdate
    end
    object CloseAction: TAction
      Hint = 'Close Handle'
      ImageIndex = 2
      OnExecute = CloseActionExecute
      OnUpdate = CloseActionUpdate
    end
    object Close2Action: TAction
      Tag = 1
      Hint = 'Close Handle'
      ImageIndex = 2
      OnExecute = CloseActionExecute
      OnUpdate = CloseActionUpdate
    end
    object TerminateAction: TAction
      Hint = 'Kill Process'
      ImageIndex = 3
      OnExecute = TerminateActionExecute
      OnUpdate = TerminateActionUpdate
    end
    object Terminate2Action: TAction
      Tag = 1
      Hint = 'Kill Process'
      ImageIndex = 3
      OnExecute = TerminateActionExecute
      OnUpdate = TerminateActionUpdate
    end
    object SaveLogAction: TAction
      Hint = 'Save Log As...'
      ImageIndex = 0
      OnExecute = SaveLogActionExecute
      OnUpdate = SaveLogActionUpdate
    end
    object SaveLog2Action: TAction
      Tag = 1
      Hint = 'Save Log As...'
      ImageIndex = 0
      OnExecute = SaveLogActionExecute
      OnUpdate = SaveLogActionUpdate
    end
    object ClearLogAction: TAction
      Hint = 'Clear Log'
      ImageIndex = 1
      OnExecute = ClearLogActionExecute
      OnUpdate = ClearLogActionUpdate
    end
    object ClearLog2Action: TAction
      Tag = 1
      Hint = 'Clear Log'
      ImageIndex = 1
      OnExecute = ClearLogActionExecute
      OnUpdate = ClearLogActionUpdate
    end
    object TopMostAction: TAction
      Caption = 'Always On Top'
      OnExecute = TopMostActionExecute
    end
    object TopOfLog1Action: TAction
      Caption = 'TopOfLog1Action'
      Hint = 'Top of Log'
      ImageIndex = 4
      OnExecute = TopOfLogActionExecute
      OnUpdate = TopOfLogActionUpdate
    end
    object TopOfLog2Action: TAction
      Tag = 1
      Caption = 'TopOfLog2Action'
      Hint = 'Top of Log'
      ImageIndex = 4
      OnExecute = TopOfLogActionExecute
      OnUpdate = TopOfLogActionUpdate
    end
    object EndOfLog1Action: TAction
      Hint = 'End of Log'
      ImageIndex = 5
      OnExecute = EndOfLogActionExecute
      OnUpdate = EndOfLogActionUpdate
    end
    object EndOfLog2Action: TAction
      Tag = 1
      Hint = 'End of Log'
      ImageIndex = 5
      OnExecute = EndOfLogActionExecute
      OnUpdate = EndOfLogActionUpdate
    end
    object ReMatch1Action: TAction
      Hint = 'Update Matching List'
      ImageIndex = 6
      OnExecute = ReMatchActionExecute
      OnUpdate = ReMatchActionUpdate
    end
    object ReMatch2Action: TAction
      Tag = 1
      Hint = 'Update Matching List'
      ImageIndex = 6
      OnExecute = ReMatchActionExecute
      OnUpdate = ReMatchActionUpdate
    end
  end
  object Timer1: TTimer
    Interval = 250
    OnTimer = Timer1Timer
    Left = 384
    Top = 40
  end
  object ImageList1: TImageList
    Height = 32
    Width = 32
    Left = 304
    Top = 104
    Bitmap = {
      494C010103000800040020002000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000800000002000000001002000000000000040
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B3B3B3004B4B4B004B4B4B00B3B3B300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D9D9D900A8A8A800A8A8A800D9D9D900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C9C9C9009696
      9600636363004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B006363
      630096969600C9C9C90000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E4E4E400CBCB
      CB00B2B2B200A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800B2B2
      B200CBCBCB00E4E4E40000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000DEDEDE007B7B7B004B4B4B004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B004B4B4B007B7B7B00DEDEDE000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000EEEEEE00BFBFBF00A8A8A800A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800A8A8A800BFBFBF00EEEEEE000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000BBBBBB004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B00737373009B9B9B004B4B4B004B4B4B009B9B9B00737373004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B00BBBBBB0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000DDDDDD00A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800BABABA00CDCDCD00A8A8A800A8A8A800CDCDCD00BABABA00A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800DDDDDD0000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FFDADADA004C4C4C00BDBD
      BD00000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000737373004B4B4B004B4B4B004B4B4B0079797900B9B9
      B900E2E2E20000000000D1D1D1007676760076767600D1D1D10000000000E2E2
      E200B9B9B900797979004B4B4B004B4B4B004B4B4B0073737300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000BABABA00A8A8A800A8A8A800A8A8A800BDBDBD00DCDC
      DC00F0F0F00000000000E7E7E700BCBCBC00BCBCBC00E7E7E70000000000F0F0
      F000DCDCDC00BDBDBD00A8A8A800A8A8A800A8A8A800BABABA00000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FFDADADA0044444400000000004C4C
      4C00000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000636363004B4B4B004B4B4B004B4B4B00AEAEAE00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000AEAEAE004B4B4B004B4B4B004B4B4B00636363000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000B2B2B200A8A8A800A8A8A800A8A8A800D7D7D700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D7D7D700A8A8A800A8A8A800A8A8A800B2B2B2000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FFDCDCDC002B2B2B000000000045454500DADA
      DA00000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000969696004B4B4B004B4B4B004B4B4B00E3E3E30000000000000000000000
      00000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      0000000000000000000000000000E3E3E3004B4B4B004B4B4B004B4B4B009696
      9600000000000000000000000000000000000000000000000000000000000000
      0000CBCBCB00A8A8A800A8A8A800A8A8A800F1F1F10000000000000000000000
      00000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      0000000000000000000000000000F1F1F100A8A8A800A8A8A800A8A8A800CBCB
      CB0000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FFDDDDDD0049494900000000002A2A2A00DBDBDB000000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C9C9
      C9004B4B4B004B4B4B004B4B4B00D2D2D2000000000000000000000000000000
      00000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      000000000000000000000000000000000000D2D2D2004B4B4B004B4B4B004B4B
      4B00C9C9C900000000000000000000000000000000000000000000000000E4E4
      E400A8A8A800A8A8A800A8A8A800E8E8E8000000000000000000000000000000
      00000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      000000000000000000000000000000000000E8E8E800A8A8A800A8A8A800A8A8
      A800E4E4E400000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FFDEDEDE002F2F2F000000000049494900DCDCDC00000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007474
      74004B4B4B004B4B4B008F8F8F00000000000000000000000000000000000000
      0000A3A3A300686868004B4B4B004B4B4B004B4B4B004B4B4B0068686800A3A3
      A30000000000000000000000000000000000000000008F8F8F004B4B4B004B4B
      4B0074747400000000000000000000000000000000000000000000000000BBBB
      BB00A8A8A800A8A8A800C8C8C800000000000000000000000000000000000000
      0000D1D1D100B5B5B500A8A8A800A8A8A800A8A8A800A8A8A800B5B5B500D1D1
      D1000000000000000000000000000000000000000000C8C8C800A8A8A800A8A8
      A800BBBBBB00000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF4D4D4D00000000002E2E2E00DDDDDD00000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D3D3D3004B4B
      4B004B4B4B007272720000000000000000000000000000000000000000007B7B
      7B004B4B4B004B4B4B007B7B7B004B4B4B004B4B4B007B7B7B004B4B4B004B4B
      4B007B7B7B000000000000000000000000000000000000000000727272004B4B
      4B004B4B4B00D3D3D30000000000000000000000000000000000E8E8E800A8A8
      A800A8A8A800B9B9B9000000000000000000000000000000000000000000BFBF
      BF00A8A8A800A8A8A800BFBFBF00A8A8A800A8A8A800BFBFBF00A8A8A800A8A8
      A800BFBFBF000000000000000000000000000000000000000000B9B9B900A8A8
      A800A8A8A800E8E8E8000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FFD9D9D900000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF33333300000000004E4E4E00DEDEDE00000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000A9A9A9004B4B
      4B004B4B4B00B8B8B80000000000000000000000000000000000686868004B4B
      4B004B4B4B00BBBBBB00D1D1D1004B4B4B004B4B4B00D1D1D100BBBBBB004B4B
      4B004B4B4B006868680000000000000000000000000000000000B8B8B8004B4B
      4B004B4B4B00A9A9A90000000000000000000000000000000000D4D4D400A8A8
      A800A8A8A800DBDBDB0000000000000000000000000000000000B5B5B500A8A8
      A800A8A8A800DDDDDD00E7E7E700A8A8A800A8A8A800E7E7E700DDDDDD00A8A8
      A800A8A8A800B5B5B50000000000000000000000000000000000DBDBDB00A8A8
      A800A8A8A800D4D4D4000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FFDADADA00868686003D3D3D003535
      35002F2F2F003B3B3B00595959008C8C8C00000000FF000000FF000000FF5252
      52000000000033333300000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000006D6D6D004B4B
      4B004B4B4B00DFDFDF00000000000000000000000000A3A3A3004B4B4B004B4B
      4B000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      00004B4B4B004B4B4B00A3A3A300000000000000000000000000DFDFDF004B4B
      4B004B4B4B006D6D6D0000000000000000000000000000000000B7B7B700A8A8
      A800A8A8A800EEEEEE00000000000000000000000000D1D1D100A8A8A800A8A8
      A8000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      0000A8A8A800A8A8A800D1D1D100000000000000000000000000EEEEEE00A8A8
      A800A8A8A800B7B7B7000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FFA5A5A5001111110000000000020202001010
      1000222222001212120000000000000000002828280090909000373737000000
      000052525200000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004B4B4B004B4B
      4B007070700000000000000000000000000000000000727272004B4B4B009393
      93000000000000000000D1D1D100A3A3A300A3A3A300D1D1D100000000000000
      0000939393004B4B4B0072727200000000000000000000000000000000007070
      70004B4B4B004B4B4B0000000000000000000000000000000000A8A8A800A8A8
      A800B9B9B90000000000000000000000000000000000B9B9B900A8A8A800CACA
      CA000000000000000000E7E7E700D1D1D100D1D1D100E7E7E700000000000000
      0000CACACA00A8A8A800B9B9B90000000000000000000000000000000000B9B9
      B900A8A8A800A8A8A8000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF8989890014141400000000003737370097979700BABA
      BA00CCCCCC00BCBCBC008E8E8E0046464600000000000E0E0E00000000003838
      3800000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D1D1D100B5B5B5004B4B4B004B4B
      4B0099999900D1D1D10000000000D1D1D100D1D1D1004B4B4B0069696900D1D1
      D100D1D1D100D1D1D10000000000000000000000000000000000D1D1D100D1D1
      D100D1D1D100696969004B4B4B00D1D1D100D1D1D10000000000D1D1D1009999
      99004B4B4B004B4B4B00B5B5B500D1D1D100E7E7E700DADADA00A8A8A800A8A8
      A800CDCDCD00E7E7E70000000000E7E7E700E7E7E700A8A8A800B5B5B500E7E7
      E700E7E7E700E7E7E70000000000000000000000000000000000E7E7E700E7E7
      E700E7E7E700B5B5B500A8A8A800E7E7E700E7E7E70000000000E7E7E700CDCD
      CD00A8A8A800A8A8A800DADADA00E7E7E700000000FF000000FF000000FF0000
      00FF000000FF9B9B9B0000000000141414009F9F9F00000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF9C9C9C001C1C1C000D0D0D009292
      9200000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B0076767600000000004B4B4B004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B00A3A3A30000000000000000000000000000000000A3A3A3004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B0000000000767676004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B00A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800BCBCBC0000000000A8A8A800A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800D1D1D10000000000000000000000000000000000D1D1D100A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A80000000000BCBCBC00A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800000000FF000000FF000000FF0000
      00FFDBDBDB00363636000101010087878700000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF90909000000000002626
      2600000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B0076767600000000004B4B4B004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B00A3A3A30000000000000000000000000000000000A3A3A3004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B0000000000767676004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B00A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800BCBCBC0000000000A8A8A800A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800D1D1D10000000000000000000000000000000000D1D1D100A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A80000000000BCBCBC00A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800000000FF000000FF000000FF0000
      00FF9D9D9D00080808004B4B4B00000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF545454000000
      00007B7B7B00000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D1D1D100B3B3B3004B4B4B004B4B
      4B009B9B9B00D1D1D10000000000D1D1D100D1D1D1004B4B4B007B7B7B00D1D1
      D100D1D1D100D1D1D10000000000000000000000000000000000D1D1D100D1D1
      D100D1D1D1007B7B7B004B4B4B00D1D1D100D1D1D10000000000D1D1D1009B9B
      9B004B4B4B004B4B4B00B3B3B300D1D1D100E7E7E700D9D9D900A8A8A800A8A8
      A800CDCDCD00E7E7E70000000000E7E7E700E7E7E700A8A8A800BFBFBF00E7E7
      E700E7E7E700E7E7E70000000000000000000000000000000000E7E7E700E7E7
      E700E7E7E700BFBFBF00A8A8A800E7E7E700E7E7E70000000000E7E7E700CDCD
      CD00A8A8A800A8A8A800D9D9D900E7E7E700000000FF000000FF000000FF0000
      00FF575757000000000099999900000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FFACACAC000909
      090048484800000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004B4B4B004B4B
      4B007373730000000000000000000000000000000000686868004B4B4B00BBBB
      BB000000000000000000D1D1D100A3A3A300A3A3A300D1D1D100000000000000
      0000BBBBBB004B4B4B0068686800000000000000000000000000000000007373
      73004B4B4B004B4B4B0000000000000000000000000000000000A8A8A800A8A8
      A800BABABA0000000000000000000000000000000000B5B5B500A8A8A800DDDD
      DD000000000000000000E7E7E700D1D1D100D1D1D100E7E7E700000000000000
      0000DDDDDD00A8A8A800B5B5B50000000000000000000000000000000000BABA
      BA00A8A8A800A8A8A8000000000000000000000000FF000000FF000000FF0000
      00FF2828280000000000D1D1D100000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FFC5C5C5001B1B
      1B0039393900000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000636363004B4B
      4B004B4B4B00E2E2E200000000000000000000000000A3A3A3004B4B4B004B4B
      4B000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      00004B4B4B004B4B4B00A3A3A300000000000000000000000000E2E2E2004B4B
      4B004B4B4B006363630000000000000000000000000000000000B2B2B200A8A8
      A800A8A8A800F0F0F000000000000000000000000000D1D1D100A8A8A800A8A8
      A8000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      0000A8A8A800A8A8A800D1D1D100000000000000000000000000F0F0F000A8A8
      A800A8A8A800B2B2B2000000000000000000000000FF000000FF000000FF0000
      00FF0B0B0B0000000000000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FFCFCFCF002525
      25002E2E2E00D8D8D800000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000969696004B4B
      4B004B4B4B00B9B9B900000000000000000000000000000000007B7B7B004B4B
      4B004B4B4B0093939300D1D1D1004B4B4B004B4B4B00D1D1D100939393004B4B
      4B004B4B4B007B7B7B0000000000000000000000000000000000B9B9B9004B4B
      4B004B4B4B009696960000000000000000000000000000000000CBCBCB00A8A8
      A800A8A8A800DCDCDC0000000000000000000000000000000000BFBFBF00A8A8
      A800A8A8A800CACACA00E7E7E700A8A8A800A8A8A800E7E7E700CACACA00A8A8
      A800A8A8A800BFBFBF0000000000000000000000000000000000DCDCDC00A8A8
      A800A8A8A800CBCBCB000000000000000000000000FF000000FF000000FF0000
      00FF2929290000000000C6C6C600000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FFC2C2C2001818
      180035353500000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C9C9C9004B4B
      4B004B4B4B007979790000000000000000000000000000000000000000006868
      68004B4B4B004B4B4B00696969004B4B4B004B4B4B00696969004B4B4B004B4B
      4B00686868000000000000000000000000000000000000000000797979004B4B
      4B004B4B4B00C9C9C90000000000000000000000000000000000E4E4E400A8A8
      A800A8A8A800BDBDBD000000000000000000000000000000000000000000B5B5
      B500A8A8A800A8A8A800B5B5B500A8A8A800A8A8A800B5B5B500A8A8A800A8A8
      A800B5B5B5000000000000000000000000000000000000000000BDBDBD00A8A8
      A800A8A8A800E4E4E4000000000000000000000000FF000000FF000000FF0000
      00FF4B4B4B00000000009B9B9B00000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FFB5B5B5000B0B
      0B003D3D3D00000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007B7B
      7B004B4B4B004B4B4B00AEAEAE00000000000000000000000000000000000000
      0000A3A3A300727272004B4B4B004B4B4B004B4B4B004B4B4B0072727200A3A3
      A3000000000000000000000000000000000000000000AEAEAE004B4B4B004B4B
      4B007B7B7B00000000000000000000000000000000000000000000000000BFBF
      BF00A8A8A800A8A8A800D7D7D700000000000000000000000000000000000000
      0000D1D1D100B9B9B900A8A8A800A8A8A800A8A8A800A8A8A800B9B9B900D1D1
      D1000000000000000000000000000000000000000000D7D7D700A8A8A800A8A8
      A800BFBFBF00000000000000000000000000000000FF000000FF000000FF0000
      00FF9E9E9E000808080049494900000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF4B4B4B000000
      000080808000000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000DEDE
      DE004B4B4B004B4B4B004B4B4B00E3E3E3000000000000000000000000000000
      00000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      000000000000000000000000000000000000E3E3E3004B4B4B004B4B4B004B4B
      4B00DEDEDE00000000000000000000000000000000000000000000000000EEEE
      EE00A8A8A800A8A8A800A8A8A800F1F1F1000000000000000000000000000000
      00000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      000000000000000000000000000000000000F1F1F100A8A8A800A8A8A800A8A8
      A800EEEEEE00000000000000000000000000000000FF000000FF000000FF0000
      00FFD6D6D6002C2C2C000D0D0D00A3A3A300000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FFADADAD00020202000000
      0000CECECE00000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000BBBBBB004B4B4B004B4B4B004B4B4B00D2D2D20000000000000000000000
      00000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      0000000000000000000000000000D2D2D2004B4B4B004B4B4B004B4B4B00BBBB
      BB00000000000000000000000000000000000000000000000000000000000000
      0000DDDDDD00A8A8A800A8A8A800A8A8A800E8E8E80000000000000000000000
      00000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      0000000000000000000000000000E8E8E800A8A8A800A8A8A800A8A8A800DDDD
      DD0000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FFC0C0C000090909000000000091919100000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF87878700131313000D0D0D008C8C
      8C00000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000737373004B4B4B004B4B4B004B4B4B008F8F8F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000008F8F8F004B4B4B004B4B4B004B4B4B00737373000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000BABABA00A8A8A800A8A8A800A8A8A800C8C8C800000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C8C8C800A8A8A800A8A8A800A8A8A800BABABA000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF8181810005050500080808003D3D3D00A0A0A000CBCB
      CB00000000FFD0D0D000999999004B4B4B000101010000000000666666000000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000636363004B4B4B004B4B4B004B4B4B0072727200B8B8
      B800DFDFDF0000000000D1D1D1007676760076767600D1D1D10000000000DFDF
      DF00B8B8B800727272004B4B4B004B4B4B004B4B4B0063636300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B2B2B200A8A8A800A8A8A800A8A8A800B9B9B900DBDB
      DB00EEEEEE0000000000E7E7E700BCBCBC00BCBCBC00E7E7E70000000000EEEE
      EE00DBDBDB00B9B9B900A8A8A800A8A8A800A8A8A800B2B2B200000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FFB0B0B0002121210004040400000000000000
      000000000000000000000000000000000000202020007C7C7C00000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000969696004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B0070707000999999004B4B4B004B4B4B0099999900707070004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B009696960000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000CBCBCB00A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800B9B9B900CDCDCD00A8A8A800A8A8A800CDCDCD00B9B9B900A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800CBCBCB0000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FFCBCBCB008B8B8B00262626001515
      150006060600121212002B2B2B006C6C6C00CACACA00000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C9C9C900747474004B4B4B004B4B
      4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B
      4B004B4B4B004B4B4B0074747400C9C9C9000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E4E4E400BBBBBB00A8A8A800A8A8
      A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8
      A800A8A8A800A8A8A800BBBBBB00E4E4E4000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D3D3D300A9A9
      A9006D6D6D004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B004B4B4B006D6D
      6D00A9A9A900D3D3D30000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E8E8E800D4D4
      D400B7B7B700A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800A8A8A800B7B7
      B700D4D4D400E8E8E80000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B5B5B5004B4B4B004B4B4B00B5B5B500000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000DADADA00A8A8A800A8A8A800DADADA00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D1D1D1004B4B4B004B4B4B00D1D1D100000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000E7E7E700A8A8A800A8A8A800E7E7E700000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000080000000200000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF00FFFC3FFFFFFC3FFFFFFFFFFF00000000
      FFFC3FFFFFFC3FFFFFFFFFFF00000000FFC003FFFFC003FFFFFFFFFF00000000
      FF0000FFFF0000FFFFFFFFFF00000000FE00007FFE00007FFFFFFF8F00000000
      FC04203FFC04203FFFFFFF0F00000000F83FFC1FF83FFC1FFFFFFE0F00000000
      F07C3E0FF07C3E0FFFFFFC1F00000000E0FC3F07E0FC3F07FFFFF83F00000000
      E1F00F87E1F00F87FFFFF87F00000000C3E007C3C3E007C3FFF7F0FF00000000
      C3C003C3C3C003C3FF00E3FF00000000C38C31C3C38C31C3FE0007FF00000000
      C78C31E3C78C31E3FC000FFF000000000203C0400203C040F87F0FFF00000000
      0203C0400203C040F0FF8FFF000000000203C0400203C040F1FFC7FF00000000
      0203C0400203C040F1FFC7FF00000000C78C31E3C78C31E3F1FFC7FF00000000
      C38C31C3C38C31C3F3FFC3FF00000000C3C003C3C3C003C3F1FFC7FF00000000
      C3E007C3C3E007C3F1FFC7FF00000000E1F00F87E1F00F87F1FFC7FF00000000
      E0FC3F07E0FC3F07F0FF87FF00000000F07C3E0FF07C3E0FF87F0FFF00000000
      F83FFC1FF83FFC1FFC081FFF00000000FC04203FFC04203FFE003FFF00000000
      FE00007FFE00007FFF007FFF00000000FF0000FFFF0000FFFFFFFFFF00000000
      FFC003FFFFC003FFFFFFFFFF00000000FFFC3FFFFFFC3FFFFFFFFFFF00000000
      FFFC3FFFFFFC3FFFFFFFFFFF0000000000000000000000000000000000000000
      000000000000}
  end
  object SaveDialog1: TSaveDialog
    Left = 512
    Top = 104
  end
  object ColorDialog1: TColorDialog
    Left = 592
    Top = 104
  end
  object ImageList2: TImageList
    Height = 20
    Width = 20
    Left = 305
    Top = 168
    Bitmap = {
      494C010107001000040014001400FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000500000002800000001002000000000000032
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007E7E7E007E7E7E00000000000000000000000000000000000000
      0000000000007E7E7E007E7E7E00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007E7E7E007E7E7E00000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FFADADAD007E7E7E00545454005B5B5B008E8E
      8E00B9B9B900000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007E7E7E0000000000000000007E7E7E000000000000000000000000000000
      00007E7E7E0000000000000000007E7E7E000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007E7E7E0000000000000000007E7E7E000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF6E6E6E00000000000000000000000000000000000000
      0000000000004C4C4C00000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D4D4D4002A2A2A0000000000000000007E7E7E0000000000000000007E7E
      7E0000000000000000002A2A2A00D4D4D4000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007E7E
      7E00000000000000000000000000000000007E7E7E0000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF0000000000000000000000000E0E0E002C2C2C002D2D2D000808
      080000000000000000001C1C1C00000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D4D4D4002A2A2A0000000000000000007E7E7E007E7E7E000000
      0000000000002A2A2A00D4D4D400000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000002A2A2A002A2A2A0000000000000000007E7E7E00000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF5858580000000000000000007E7E7E00000000FF000000FF000000FF0000
      00FF6B6B6B00000000000000000073737300000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000D4D4D4002A2A2A000000000000000000000000000000
      00002A2A2A00D4D4D40000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007E7E7E00000000000000
      00002A2A2A00D4D4D400D4D4D4002A2A2A0000000000000000007E7E7E000000
      000000000000000000000000000000000000000000FF000000FF000000FFB9B9
      B900000000000000000054545400000000FF000000FF000000FF000000FF0000
      00FF000000FF676767000000000000000000CDCDCD00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000D4D4D4002A2A2A0000000000000000002A2A
      2A00D4D4D4000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7E7E0000000000000000002A2A
      2A00D4D4D4000000000000000000D4D4D4002A2A2A0000000000000000007E7E
      7E0000000000000000000000000000000000000000FF000000FF000000FF8E8E
      8E00000000000F0F0F00000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FFCECECE0000000000000000008B8B8B00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000D4D4D400D4D4D40000000000D4D4D4002A2A2A002A2A2A00D4D4
      D40000000000D4D4D400D4D4D400000000000000000000000000000000000000
      000000000000000000000000000000000000D4D4D4002A2A2A002A2A2A00D4D4
      D40000000000D4D4D400D4D4D40000000000D4D4D4002A2A2A002A2A2A00D4D4
      D40000000000000000000000000000000000000000FF000000FF000000FF5B5B
      5B00000000002F2F2F00000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF7E7E7E007E7E7E007E7E7E00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000D4D4D4002A2A2A002A2A2A00D4D4D40000000000D4D4D400D4D4D4000000
      0000D4D4D4002A2A2A002A2A2A00D4D4D4000000000000000000000000000000
      00000000000000000000000000000000000000000000D4D4D400D4D4D4000000
      0000D4D4D4002A2A2A002A2A2A00D4D4D40000000000D4D4D400D4D4D4000000
      000000000000000000000000000000000000000000FF000000FF000000FF5B5B
      5B00000000002F2F2F00000000FF000000FF000000FF000000FFBEBEBE00BEBE
      BE00BEBEBE00BEBEBE00BEBEBE00BEBEBE00BEBEBE00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007E7E7E0000000000000000002A2A2A00D4D4D4000000000000000000D4D4
      D4002A2A2A0000000000000000007F7F7F000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000D4D4
      D4002A2A2A0000000000000000002A2A2A00D4D4D40000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF8E8E
      8E00000000000F0F0F00000000FF000000FF000000FF000000FFBEBEBE000000
      0000000000000000000000000000000000003F3F3F00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007E7E7E0000000000000000002A2A2A00D4D4D400D4D4D4002A2A
      2A0000000000000000007F7F7F00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000D4D4D4002A2A
      2A00000000000000000000000000000000002A2A2A00D4D4D400000000000000
      000000000000000000000000000000000000000000FF000000FF000000FFB9B9
      B900000000000000000054545400000000FF000000FF000000FFBEBEBE007E7E
      7E007E7E7E005E5E5E0000000000000000003F3F3F00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007E7E7E0000000000000000002A2A2A002A2A2A000000
      0000000000007F7F7F0000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D4D4D4002A2A2A000000
      0000000000007E7E7E007E7E7E0000000000000000002A2A2A00D4D4D4000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF5858580000000000000000007E7E7E00000000FF000000FF000000FFC7C7
      C7003D3D3D000000000000000000000000003F3F3F00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007E7E7E000000000000000000000000000000
      00007F7F7F000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D4D4D4002A2A2A00000000000000
      00007E7E7E0000000000000000007E7E7E0000000000000000002A2A2A00D4D4
      D40000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF0000000000000000000000000E0E0E002C2C2C001F1F1F000000
      000000000000000000005C5C5C00000000003F3F3F00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7E7E0000000000000000007E7E
      7E00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7E7E0000000000000000007E7E
      7E00000000000000000000000000000000007E7E7E0000000000000000007E7E
      7E0000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF6E6E6E00000000000000000000000000000000000000
      0000000000008A8A8A00000000FF000000003F3F3F00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007E7E7E007E7E7E000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000007E7E7E007E7E7E000000
      000000000000000000000000000000000000000000007E7E7E007E7E7E000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FFADADAD007E7E7E005454540065656500A9A9
      A900000000FF000000FF000000FF3F3F3F003F3F3F00000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800000000000000000000000
      000000000000000000000000000000000000000000007E7E7E00000000000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF000000FF0000000000000080808000FF000000FF000000FFFFFF00C0C0
      C000C0C0C00000000000FF000000FF0000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007E7E7E007E7E
      7E007E7E7E007E7E7E007E7E7E007E7E7E007E7E7E007E7E7E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF000000FF0000000000000080808000FF000000FF000000FFFFFF00C0C0
      C000C0C0C00000000000FF000000FF0000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      000000000000000000000000000000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007E7E7E007E7E7E00000000000000000000000000000000000000
      0000000000007E7E7E007E7E7E00000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      0000000000000000000000000000000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000007F7F7F007E7E7E0000000000000000007E7E7E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007E7E7E00000000007E7E7E000000000000000000000000000000
      00007E7E7E00000000007E7E7E00000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF00000000000000000000000000000000000000FF000000FF000000FF000000
      00000000000000000000000000000000000080808000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000007F7F7F007E7E7E0000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007E7E7E00000000007E7E7E0000000000000000007E7E
      7E00000000007E7E7E0000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF0000000000000000000000FF000000FF000000FF00000000000000
      00000000000000000000000000000000000080808000FFFFFF00FFFFFF000000
      0000FFFFFF0000000000FFFFFF00FFFFFF00000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000007E7E7E007E7E7E0000000000000000007F7F7F00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007E7E7E00000000007E7E7E007E7E7E000000
      00007E7E7E000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF0000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00FFFFFF000000
      00000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000007E7E7E007E7E7E0000000000000000007E7E7E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7E7E0000000000000000007E7E
      7E00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF000000FF000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00FFFFFF000000
      0000FFFFFF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000007E7E7E007E7E7E0000000000000000007E7E7E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7E7E0000000000000000007E7E
      7E00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF000000FF000000000000000000000000000000
      00000000000000000000000000000000000080808000FFFFFF00FFFFFF00FFFF
      FF0000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000007E7E7E007E7E7E0000000000000000007E7E7E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007E7E7E00000000007E7E7E007E7E7E000000
      00007E7E7E000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF0000000000000000000000
      0000000000000000000000000000000000008080800080808000808080008080
      8000808080008080800080808000808080008080800080808000808080008080
      8000808080008080800080808000808080008080800080808000808080008080
      80000000000000000000000000000000000000000000000000007E7E7E000000
      0000000000007E7E7E007E7E7E0000000000000000007E7E7E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007E7E7E00000000007E7E7E0000000000000000007E7E
      7E00000000007E7E7E0000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF0000000000000000000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF00000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000FF0000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007E7E7E000000
      000000000000000000000000000000000000000000007E7E7E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007E7E7E00000000007E7E7E000000000000000000000000000000
      00007E7E7E00000000007E7E7E00000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF00000000000000000000000000000000000000FF000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7E7E00000000007E7E7E007E7E
      7E007E7E7E007E7E7E007E7E7E007E7E7E007E7E7E007E7E7E00000000007E7E
      7E00000000000000000000000000000000000000000000000000000000000000
      0000000000007E7E7E007E7E7E00000000000000000000000000000000000000
      0000000000007E7E7E007E7E7E00000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF00000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000FF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000050000000280000000100010000000000E00100000000000000000000
      000000000000000000000000FFFFFF00FFFFFFFFFFFFFFF000000000FFFFFFFF
      FFFFFFF000000000FFFFFFFFFFFFFFF000000000F9F9FFF9FFFE07F000000000
      F0F0FFF0FFFC03F000000000F060FFE07FF801F000000000F801FFC03FF0F0F0
      00000000FC03FF801FE1F87000000000FE07FF060FE3F87000000000F909FF09
      0FE3FC7000000000F090FF909FE3C07000000000F060FFE07FE3C07000000000
      F801FFC03FE1C07000000000FC03FF801FF0E07000000000FE07FF060FF80070
      00000000FF0FFF0F0FFC027000000000FF9FFF9F9FFE0E7000000000FFFFFFFF
      FFFFFFF000000000FFFFFFFFFFFFFFF000000000FFFFFFFFFFFFFFF000000000
      FFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFF
      FFFF0000E0007F801FFFFFFFFFFF0000E0007F801FFFFFFFFFFF0000E0007F9F
      9FF9F9FF9F9F000000000F909FF8F1FF8F1F000000000F909FFC63FFC63F0000
      00000F909FFE07FFE07F000000000F909FFF0FFFF0FF000000000F909FFF0FFF
      F0FF000000000F909FFE07FFE07F000000000F909FFC63FFC63F0000E0007F9F
      9FF8F1FF8F1F0000E0007F000FF9F9FF9F9F0000E0007F000FFFFFFFFFFF0000
      E0007FF0FFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFF
      FFFF0000FFFFFFFFFFFFFFFFFFFF000000000000000000000000000000000000
      000000000000}
  end
  object OpenDialog1: TOpenDialog
    Left = 510
    Top = 176
  end
  object Timer2: TTimer
    Interval = 100
    OnTimer = Timer2Timer
    Left = 385
    Top = 104
  end
end
