//----------------------------------------------------------------------//
// Dual Debug Monitor													//
//																		//
//----------------------------------------------------------------------//
#include "usr_env.h"
#include "usr_str.h"
#include "usr_ctrl.h"
#include "usr_misc.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDDbgMonFrm *DDbgMonFrm;

//---------------------------------------------------------------------------
__fastcall TDDbgMonFrm::TDDbgMonFrm(TComponent *Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::FormCreate(TObject *Sender)
{
	Working    = false;
	Pausing    = false;
	Capturing  = false;
	CaptureTag = 0;

	TargetPID1  = TargetPID2  = 0;
	TargetHWnd1 = TargetHWnd2 = NULL;

	LogBuffer  = new TStringList();
	LogBuffer2 = new TStringList();

	crTarget = (TCursor)6;
	Screen->Cursors[crTarget] = (HCURSOR)::LoadImage(HInstance, _T("TARGET_TOOL"), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);

	Caption = "Dual Debug Monitor - V" + get_version_str();

	IniFile = new TIniFile(ChangeFileExt(Application->ExeName, ".INI"));
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::FormShow(TObject *Sender)
{
	load_form_pos(this, IniFile, 680, 480);

	UnicodeString sct = "General";
	LogPanel1->Width    = IniFile->ReadInteger(sct, "LogListWidth",		(ClientWidth - OpePanel->Width)/2);
	MatchPanel1->Height = IniFile->ReadInteger(sct, "MatchList1Height",	150);
	MatchPanel2->Height = IniFile->ReadInteger(sct, "MatchList2Height",	150);

	sct = "Option";
	TopMostAction->Checked = IniFile->ReadBool(sct, "TopMost", false);
	set_TopMost(this, TopMostAction->Checked);
	TransBar->Position = IniFile->ReadInteger(sct, "AlphaBlend",	255);
	ClassEdit1->Text   = IniFile->ReadString( sct, "LastClass",		EmptyStr);
	ClassEdit2->Text   = IniFile->ReadString( sct, "LastClass2",	EmptyStr);
	Em1Edit->Text      = IniFile->ReadString( sct, "EmMatchStr1",	EmptyStr);
	Em2Edit->Text      = IniFile->ReadString( sct, "EmMatchStr2",	EmptyStr);
	Em3Edit->Text      = IniFile->ReadString( sct, "EmMatchStr3",	EmptyStr);
	Em4Edit->Text      = IniFile->ReadString( sct, "EmMatchStr4",	EmptyStr);
	ExlcudeEdit->Text  = IniFile->ReadString( sct, "ExcludePtn",	"recv msg;attach;detach");

	sct = "Color";
	col_fgEm1  = (TColor)IniFile->ReadInteger(sct, "fgEm1",	0x33cc33);
	col_fgEm2  = (TColor)IniFile->ReadInteger(sct, "fgEm2",	0x999999);
	col_fgEm3  = (TColor)IniFile->ReadInteger(sct, "fgEm3",	0x993333);
	col_fgEm4  = (TColor)IniFile->ReadInteger(sct, "fgEm4",	0x333399);
	col_fgMark = (TColor)IniFile->ReadInteger(sct, "fgMark",0xcc33cc);

	ColorListBox->Items->Text =
		"Highlight Color 1\r\n"
		"Highlight Color 2\r\n"
		"Highlight Color 3\r\n"
		"Highlight Color 4\r\n"
		"Matched Line\r\n";

	load_ComboBoxItems(MatchComboBox1,	IniFile, "MatchHistory1",	20);
	if (MatchComboBox1->Items->Count>0) MatchComboBox1->ItemIndex = 0;
	load_ComboBoxItems(MatchComboBox2,	IniFile, "MatchHistory2",	20);
	if (MatchComboBox2->Items->Count>0) MatchComboBox2->ItemIndex = 0;

	ImageList1->GetBitmap(0, CapToolImage1->Picture->Bitmap);
	ImageList1->GetBitmap(0, CapToolImage2->Picture->Bitmap);
	CapToolImage1->Repaint();
	CapToolImage2->Repaint();

	UnicodeString ptn_hint = "Specify multiple by separating with ';' (/re/)";
	ExlcudeEdit->Hint    = ptn_hint;
	MatchComboBox1->Hint = ptn_hint;
	MatchComboBox2->Hint = ptn_hint;
	PtnGroupBox->Hint    = ptn_hint;
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (Working) {
		set_TopMost(this, false);
		msgbox_WARN("is being monitored...");
		CanClose = false;
		set_TopMost(this, TopMostAction->Checked);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
	save_form_pos(this, IniFile);

	UnicodeString sct = "General";
	IniFile->WriteInteger(sct, "LogListWidth",		LogPanel1->Width);
	IniFile->WriteInteger(sct, "MatchList1Height",	MatchPanel1->Height);
	IniFile->WriteInteger(sct, "MatchList2Height",	MatchPanel2->Height);

	sct = "Option";
	IniFile->WriteBool(   sct, "TopMost",		TopMostAction->Checked);
	IniFile->WriteInteger(sct, "AlphaBlend",	TransBar->Position);
	IniFile->WriteString( sct, "LastClass",		ClassEdit1->Text);
	IniFile->WriteString( sct, "LastClass2",	ClassEdit2->Text);
	IniFile->WriteString( sct, "EmMatchStr1",	Em1Edit->Text);
	IniFile->WriteString( sct, "EmMatchStr2",	Em2Edit->Text);
	IniFile->WriteString( sct, "EmMatchStr3",	Em3Edit->Text);
	IniFile->WriteString( sct, "EmMatchStr4",	Em4Edit->Text);
	IniFile->WriteString( sct, "ExcludePtn",	ExlcudeEdit->Text);

	sct = "Color";
	IniFile->WriteInteger(sct, "fgEm1",		(int)col_fgEm1);
	IniFile->WriteInteger(sct, "fgEm2",		(int)col_fgEm2);
	IniFile->WriteInteger(sct, "fgEm3",		(int)col_fgEm3);
	IniFile->WriteInteger(sct, "fgEm4",		(int)col_fgEm4);
	IniFile->WriteInteger(sct, "fgMark",	(int)col_fgMark);

	save_ComboBoxItems(MatchComboBox1,	IniFile, "MatchHistory1",	20);
	save_ComboBoxItems(MatchComboBox2,	IniFile, "MatchHistory2",	20);
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::FormDestroy(TObject *Sender)
{
	delete LogBuffer;
	delete LogBuffer2;
	delete IniFile;
}

//---------------------------------------------------------------------------
//タイマー処理	(Interval = 250ms)
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::Timer1Timer(TObject *Sender)
{
	//対象ウィンドウの取得
	if (Capturing) {
		HWND hWnd = GetTopWindow(NULL);
		do {
			if (GetWindowLong(hWnd, GWL_HWNDPARENT)!=0 || !IsWindowVisible(hWnd)) continue;
			TRect rc;
			GetWindowRect(hWnd, &rc);
			if (rc.PtInRect(Mouse->CursorPos)) {
				PrepareTarget(hWnd, CaptureTag);
				break;
			}
		} while (hWnd = GetNextWindow(hWnd, GW_HWNDNEXT));
	}

	//無効になったプロセスの監視を停止
	if (Working) {
		if (TargetPID1>0) {
			HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, TargetPID1);
			if (hProc) ::CloseHandle(hProc); else ClearID(0);
		}
		if (TargetPID2>0) {
			HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, TargetPID2);
			if (hProc) ::CloseHandle(hProc); else ClearID(1);
		}
	}
}
//---------------------------------------------------------------------------
//プロセス指定情報をクリア
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::ClearID(int tag)
{
	if (tag==1) {
		TargetPID2      = 0;
		TargetHWnd2     = NULL;
		TargetFname2    = EmptyStr;
		PidEdit2->Text  = EmptyStr;
		HWndEdit2->Text = EmptyStr;
		SetEditColor(PidEdit2);
		SetEditColor(HWndEdit2);
		GroupBox2->Caption = get_tkn(GroupBox2->Caption, " -");
	}
	else {
		TargetPID1      = 0;
		TargetHWnd1     = NULL;
		TargetFname1    = EmptyStr;
		PidEdit1->Text  = EmptyStr;
		HWndEdit1->Text = EmptyStr;
		SetEditColor(PidEdit1);
		SetEditColor(HWndEdit1);
		GroupBox1->Caption = get_tkn(GroupBox1->Caption, " -");
	}
}
//---------------------------------------------------------------------------
//ハンドルから対象プロセスを準備
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::PrepareTarget(HWND hWnd, int tag)
{
	if (hWnd) {
		bool is2 = (tag==1);
		(is2? ClassEdit2 : ClassEdit1)->Text = get_ClassName(hWnd);
		(is2? TextEdit2  : TextEdit1)->Text  = get_WindowText(hWnd);
		DWORD pid;
		DWORD tid = ::GetWindowThreadProcessId(hWnd, &pid);
		(is2? PidEdit2  : PidEdit1)->Text  = pid;
		(is2? HWndEdit2 : HWndEdit1)->Text = (NativeInt)hWnd;

		HANDLE hProc = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
		if (hProc) {
			_TCHAR sbuf[MAX_PATH];
			DWORD sz = MAX_PATH;
			UnicodeString fnam = ::QueryFullProcessImageName(hProc, 0, sbuf, &sz)? sbuf : _T("");
			(is2? TargetFname2 : TargetFname1) = fnam;
			TGroupBox *gp = is2? GroupBox2 : GroupBox1;
			UnicodeString s = get_tkn(gp->Caption, " -");
			gp->Caption = s.cat_sprintf(_T(" - %s"), ExtractFileName(fnam).c_str());
		}
	}
	else {
		ClearID(tag);
	}
}

//---------------------------------------------------------------------------
//プロセスの監視
//---------------------------------------------------------------------------
bool __fastcall TDDbgMonFrm::WaitOutputDebugStr(DWORD pid, HWND hWnd, DWORD pid2, HWND hWnd2)
{
	if (pid==0 && pid2==0) return false;

	try {
		Working = true;
		Pausing = false;

		TargetPID1  = pid;
		TargetPID2  = pid2;
		TargetHWnd1 = hWnd;
		TargetHWnd2 = hWnd2;

		if (TargetPID1!=0) AddLog(">>> Monitor1 - " + ExtractFileName(TargetFname1), 0);
		if (TargetPID2!=0) AddLog(">>> Monitor2 - " + ExtractFileName(TargetFname2), 1);
		UpdateActions();

		SECURITY_ATTRIBUTES sa;
		SECURITY_DESCRIPTOR sd;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = TRUE;
		sa.lpSecurityDescriptor = &sd;

		if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))	Abort();
		if (!SetSecurityDescriptorDacl(&sd, TRUE, (PACL)NULL, FALSE))			Abort();

		HANDLE hEvAck = CreateEvent(&sa, FALSE, FALSE, _T("DBWIN_BUFFER_READY"));
		if (!hEvAck || GetLastError() == ERROR_ALREADY_EXISTS) 		Abort();
		HANDLE hEvReady = CreateEvent(&sa, FALSE, FALSE, _T("DBWIN_DATA_READY"));
		if (!hEvReady || GetLastError() == ERROR_ALREADY_EXISTS)	Abort();
		HANDLE hMapFile = CreateFileMapping((HANDLE)0xFFFFFFFF, &sa, PAGE_READWRITE, 0, 4096, _T("DBWIN_BUFFER"));
		if (!hMapFile) Abort();
		LPVOID pMem = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 4096);
		if (!pMem) Abort();

		LPDWORD pPID = (LPDWORD)pMem;
		LPSTR pSTR = (LPSTR)(pPID + 1);

		SetEvent(hEvAck);
		while (TargetPID1>0 || TargetPID2>0) {
			Application->ProcessMessages();
			UpdateActions();

			switch (WaitForSingleObject(hEvReady, 100)) {
			case WAIT_OBJECT_0:
				if (!Pausing) {
					UnicodeString msg = pSTR;
					msg = get_tkn(msg, "\r");
					if (!ptn_match_str(ExlcudeEdit->Text, msg).IsEmpty()) msg = EmptyStr;
					if (!msg.IsEmpty()) {
						if (TargetPID1 == *pPID) AddLog(msg, 0);
						if (TargetPID2 == *pPID) AddLog(msg, 1);
					}
				}
				if (TargetPID1>0 || TargetPID2>0) SetEvent(hEvAck);
				break;
			case WAIT_FAILED:
				msgbox_ERR(SysErrorMessage(GetLastError()));
				break;
			}
		}

		::UnmapViewOfFile(pMem);
		::CloseHandle(hMapFile);
		::CloseHandle(hEvAck);
		::CloseHandle(hEvReady);

		if (!MatchComboBox1->Text.IsEmpty()) add_ComboBox_history(MatchComboBox1, MatchComboBox1->Text);
		if (!MatchComboBox2->Text.IsEmpty()) add_ComboBox_history(MatchComboBox2, MatchComboBox2->Text);

		Working = false;
		Pausing = false;
		return true;
	}
	catch (...) {
		msgbox_ERR(SysErrorMessage(EVENT_E_INTERNALEXCEPTION));
		Working = false;
		return false;
	}
}
//---------------------------------------------------------------------------
//ログの追加
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::AddLog(UnicodeString s, int tag)
{
	bool is2 = (tag==1);

	UnicodeString lbuf = FormatDateTime("hh:nn:ss.zzz ", Now()) + s;
	TStringList *sp = (is2? LogBuffer2 : LogBuffer);
	sp->Add(lbuf);

	TListBox *lp  = is2? LogListBox2 : LogListBox1;
	int  last_idx = lp->ItemIndex;
	int  last_top = lp->TopIndex;
	bool is_btm   = (last_idx == lp->Count - 1);

	lp->Count     = sp->Count;
	if (is_btm) {
		lp->ItemIndex = lp->Count - 1;
	}
	else {
		lp->TopIndex  = last_top;
		lp->ItemIndex = last_idx;
	}

	(is2? TopOfLog2Action : TopOfLog1Action)->Update();
	(is2? EndOfLog2Action : EndOfLog1Action)->Update();

	UnicodeString ptn = (tag==1)? MatchComboBox2->Text : MatchComboBox1->Text;
	if (!ptn_match_str(ptn, s).IsEmpty()) {
		(is2? MatchListBox2 : MatchListBox1)->Items->AddObject(lbuf, (TObject*)lp->ItemIndex);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::CapToolImage1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (!Capturing && Button == mbLeft) {
		int tag = ((TComponent*)Sender)->Tag;
		Screen->Cursor = crTarget;
		TImage *ip = (tag==1)? CapToolImage2 : CapToolImage1;
		ImageList1->GetBitmap(1, ip->Picture->Bitmap);
		ip->Repaint();
		Capturing  = true;
		CaptureTag = tag;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::CapToolImage1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (!Capturing) return;

	// マウス位置のウィンドウを取得
	if (Button == mbLeft) {
		Capturing = false;
		Screen->Cursor = crDefault;
		TImage *ip = (((TComponent*)Sender)->Tag==1)? CapToolImage2 : CapToolImage1;
		ImageList1->GetBitmap(0, ip->Picture->Bitmap);
		ip->Repaint();
	}
}
//---------------------------------------------------------------------------
// 検索
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::FindActionExecute(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	TLabeledEdit *c_ep = (tag==1)? ClassEdit2 : ClassEdit1;
	TLabeledEdit *t_ep = (tag==1)? TextEdit2  : TextEdit1;
	TLabeledEdit *p_ep = (tag==1)? PidEdit2   : PidEdit1;
	TLabeledEdit *h_ep = (tag==1)? HWndEdit2  : HWndEdit1;
	std::unique_ptr<TList> hlst(new TList());
	if (GetHwndList(c_ep->Text, t_ep->Text, hlst.get())) {
		PrepareTarget((HWND)hlst->Items[0], tag);
	}
	else {
		ClearID(tag);
		::MessageBeep(MB_ICONEXCLAMATION);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::FindActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Enabled = !Working;
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::LogListBoxData(TWinControl *Control, int Index, UnicodeString &Data)
{
	Data = LogBuffer->Strings[Index];
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::LogListBox2Data(TWinControl *Control, int Index, UnicodeString &Data)
{
	Data = LogBuffer2->Strings[Index];
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::LogListBoxDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State)
{
	TListBox *lp = (TListBox *)Control;
	TCanvas  *cv = lp->Canvas;

	cv->Brush->Color = State.Contains(odSelected)? clHighlight : clWindow;
	cv->FillRect(Rect);

	UnicodeString lbuf = lp->Items->Strings[Index];
	UnicodeString t = get_tkn(lbuf, " ") + " ";
	UnicodeString s = get_tkn_r(lbuf, " ");
	cv->Font->Color = State.Contains(odSelected)? clHighlightText : clDkGray;
	int xp = Rect.Left + 2;
	cv->TextOut(xp, Rect.Top, t);
	xp += cv->TextWidth(t);
	UnicodeString ptn = ((lp->Tag==1)? MatchComboBox2 : MatchComboBox1)->Text;
	cv->Font->Color =   State.Contains(odSelected)? clHighlightText :
				  !ptn_match_str(ptn, s).IsEmpty()? col_fgMark :
		!ptn_match_str(Em1Edit->Text, s).IsEmpty()? col_fgEm1 :
		!ptn_match_str(Em2Edit->Text, s).IsEmpty()? col_fgEm2 :
		!ptn_match_str(Em3Edit->Text, s).IsEmpty()? col_fgEm3 :
		!ptn_match_str(Em4Edit->Text, s).IsEmpty()? col_fgEm4 : clWindowText;
	cv->TextOut(xp, Rect.Top, s);
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::LogListBoxClick(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	TListBox *lp  = (tag==1)? LogListBox2 : LogListBox1;
	TListBox *lp2 = (tag==1)? LogListBox1 : LogListBox2;
	int idx = (tag==1)? lp->ItemIndex : lp->ItemIndex;
	if (idx!=-1) {
		int d_idx = idx - lp->TopIndex;
		try {
			TDateTime t = TDateTime(get_tkn(lp->Items->Strings[idx], " "));
			for (int i=0; i<lp2->Count; i++) {
				TDateTime t2 = TDateTime(get_tkn(lp2->Items->Strings[i], " "));
				if (t2>t) {
					lp2->ItemIndex = i;
					lp2->TopIndex  = i - d_idx;
					break;
				}
			}
		}
		catch (EConvertError &e) {
			::MessageBeep(MB_ICONEXCLAMATION);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::MatchListBoxClick(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	TListBox *mp = (tag==1)? MatchListBox2 : MatchListBox1;
	int idx = mp->ItemIndex;	if (idx==-1) return;
	UnicodeString s = mp->Items->Strings[idx];

	TListBox *lp = (tag==1)? LogListBox2 : LogListBox1;
	for (int i=0; i<lp->Count; i++) {
		if (SameText(s, lp->Items->Strings[i])) {
			lp->ItemIndex = i;
			lp->TopIndex  = i - 4;
			LogListBoxClick(lp);
			break;
		}
	}
}
//---------------------------------------------------------------------------
//マーク行強調
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::MatchStrChange(TObject *Sender)
{
	LogListBox1->Invalidate();
	LogListBox2->Invalidate();
}

//---------------------------------------------------------------------------
// 開始
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::StartActionExecute(TObject *Sender)
{
	WaitOutputDebugStr(
		PidEdit1->Text.ToIntDef(0), (HWND)HWndEdit1->Text.ToIntDef(0),
		PidEdit2->Text.ToIntDef(0), (HWND)HWndEdit2->Text.ToIntDef(0));
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::StartActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Enabled = !Working && (!PidEdit1->Text.IsEmpty() || !PidEdit2->Text.IsEmpty());

	GroupBox1->Enabled = !Working;
	GroupBox2->Enabled = !Working;

	SetEditColor(PidEdit1);
	SetEditColor(PidEdit2);
	SetEditColor(HWndEdit1);
	SetEditColor(HWndEdit2);
}
//---------------------------------------------------------------------------
//休止/再開
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::PauseActionExecute(TObject *Sender)
{
	Pausing = !Pausing;
	UpdateActions();
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::PauseActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	ap->Caption = Pausing? "Resume" : "Pause";
	ap->Enabled = Working;
}
//---------------------------------------------------------------------------
//停止
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::StopActionExecute(TObject *Sender)
{
	ClearID(0);
	ClearID(1);
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::StopActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction *)Sender;
	ap->Enabled = Working;
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::StopProcActionExecute(TObject *Sender)
{
	ClearID(((TComponent*)Sender)->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::StopProcActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	ap->Enabled = Working & (((ap->Tag==1)? TargetPID2 : TargetPID1) > 0);
}

//---------------------------------------------------------------------------
//アプリケーションを閉じる
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::CloseActionExecute(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	HWND hWnd = (tag==1)? TargetHWnd2 : TargetHWnd1;
	::PostMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
	ClearID(tag);
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::CloseActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	ap->Enabled = (((ap->Tag==1)? TargetPID2 : TargetPID1) > 0);
}
//---------------------------------------------------------------------------
//プロセスの強制終了
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::TerminateActionExecute(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	HANDLE hProc = ::OpenProcess(PROCESS_TERMINATE, FALSE, (tag==1)? TargetPID2 : TargetPID1);
	if (hProc) {
		if (::TerminateProcess(hProc, 0)) {
			ClearID(tag);
		}
		else {
			msgbox_ERR("Failed!");
		}
		::CloseHandle(hProc);
		UpdateActions();
	}
	else {
		msgbox_ERR(SysErrorMessage(GetLastError()));
	}
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::TerminateActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	ap->Enabled = (((ap->Tag==1)? TargetPID2 : TargetPID1) > 0);
}

//---------------------------------------------------------------------------
// ログを保存
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::SaveLogActionExecute(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	SaveDialog1->Filter     = "ログ (*.log)|*.LOG";
	SaveDialog1->DefaultExt = "LOG";
	SaveDialog1->FileName   = FormatDateTime(
								(tag==1)? "yyyymmddhhnnss'_2.log'" : "yyyymmddhhnnss'_1.log'", Now());
	SaveDialog1->InitialDir = ExtractFileDir(Application->ExeName);
	SaveDialog1->Options.Clear();
	SaveDialog1->Options << ofOverwritePrompt;
	if (SaveDialog1->Execute()) LogBuffer->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::SaveLogActionUpdate(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	((TAction *)Sender)->Enabled = (((tag==1)? LogListBox2->Count : LogListBox1->Count) > 0);
}
//---------------------------------------------------------------------------
// ログをクリア
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::ClearLogActionExecute(TObject *Sender)
{
	if (((TComponent*)Sender)->Tag==1) {
		LogListBox2->Count = 0;
		LogBuffer2->Clear();
		MatchListBox2->Clear();
	}
	else {
		LogListBox1->Count = 0;
		LogBuffer->Clear();
		MatchListBox1->Clear();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::ClearLogActionUpdate(TObject *Sender)
{
	int tag = ((TComponent*)Sender)->Tag;
	((TAction *)Sender)->Enabled = !Working && (((tag==1)? LogListBox2->Count : LogListBox1->Count) > 0);
}
//---------------------------------------------------------------------------
// 透明度
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::TransBarChange(TObject *Sender)
{
	AlphaBlendValue = TransBar->Position;
}
//---------------------------------------------------------------------------
// 常に手前に
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::TopMostActionExecute(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	ap->Checked = !ap->Checked;
	set_TopMost(this, ap->Checked);
}

//---------------------------------------------------------------------------
//配色
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::ColorListBoxDrawItem(TWinControl *Control, int Index,
	TRect &Rect, TOwnerDrawState State)
{
	TColor col = clNone;
	switch (Index) {
	case  0: col = col_fgEm1;	break;
	case  1: col = col_fgEm2;	break;
	case  2: col = col_fgEm3;	break;
	case  3: col = col_fgEm4;	break;
	case  4: col = col_fgMark;	break;
	}

	TListBox *cp = (TListBox *)Control;
	draw_ColorItem(col, cp->Items->Strings[Index], cp->Canvas, Rect, State.Contains(odSelected));
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::ColorListBoxDblClick(TObject *Sender)
{
	TListBox *lp = ColorListBox;
	int idx = lp->ItemIndex;	if (idx==-1) return;

	switch (idx) {
	case  0: ColorDialog1->Color = col_fgEm1;	break;
	case  1: ColorDialog1->Color = col_fgEm2;	break;
	case  2: ColorDialog1->Color = col_fgEm3;	break;
	case  3: ColorDialog1->Color = col_fgEm4;	break;
	case  4: ColorDialog1->Color = col_fgMark;	break;
	}

	if (ColorDialog1->Execute()) {
		switch (idx) {
		case 0: col_fgEm1  = ColorDialog1->Color;	break;
		case 1: col_fgEm2  = ColorDialog1->Color;	break;
		case 2: col_fgEm3  = ColorDialog1->Color;	break;
		case 3: col_fgEm4  = ColorDialog1->Color;	break;
		case 4: col_fgMark = ColorDialog1->Color;	break;
		}
	}
}

//---------------------------------------------------------------------------
//ログの先頭に移動
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::TopOfLogActionExecute(TObject *Sender)
{
	TListBox *lp = (((TComponent*)Sender)->Tag==1)? LogListBox2 : LogListBox1;
	lp->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::TopOfLogActionUpdate(TObject *Sender)
{
	TListBox *lp = (((TComponent*)Sender)->Tag==1)? LogListBox2 : LogListBox1;
	((TAction*)Sender)->Enabled = (lp->Count>0);
}
//---------------------------------------------------------------------------
//ログの最後に移動
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::EndOfLogActionExecute(TObject *Sender)
{
	TListBox *lp = (((TComponent*)Sender)->Tag==1)? LogListBox2 : LogListBox1;
	lp->ItemIndex = lp->Count - 1;
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::EndOfLogActionUpdate(TObject *Sender)
{
	TListBox *lp = (((TComponent*)Sender)->Tag==1)? LogListBox2 : LogListBox1;
	((TAction*)Sender)->Enabled = (lp->Count>1 && lp->ItemIndex<lp->Count-1); 
}

//---------------------------------------------------------------------------
//マッチリストを更新
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::ReMatchActionExecute(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	bool is2 = (ap->Tag==1);
	TComboBox *cp = is2? MatchComboBox2 : MatchComboBox1;
	TStringList *sp = (is2? LogBuffer2 : LogBuffer);
	TListBox *mp = is2? MatchListBox2 : MatchListBox1;
	mp->Clear();
	for (int i=0; i<sp->Count; i++) {
		UnicodeString lbuf = sp->Strings[i];
		UnicodeString s = get_tkn_r(lbuf, " ");
		if (!ptn_match_str(cp->Text, s).IsEmpty()) mp->Items->AddObject(lbuf, (TObject*)i);
	}
	if (mp->Count>0) add_ComboBox_history(cp, cp->Text);
}
//---------------------------------------------------------------------------
void __fastcall TDDbgMonFrm::ReMatchActionUpdate(TObject *Sender)
{
	TAction *ap = (TAction*)Sender;
	ap->Enabled = !((ap->Tag==1)? MatchComboBox2 : MatchComboBox1)->Text.IsEmpty();
}
//---------------------------------------------------------------------------

