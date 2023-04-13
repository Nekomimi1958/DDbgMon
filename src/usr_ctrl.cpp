//----------------------------------------------------------------------//
// �ėp���ʊ֐�(�R���g���[��)											//
//																		//
//----------------------------------------------------------------------//
#ifndef USE_COMMON_PCH
#include <vcl.h>
#include <tchar.h>
#include <memory>
#include <algorithm>
#pragma hdrstop
#endif

#include "usr_str.h"
#include "usr_ctrl.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//�w��t�H���g�̕`�捂���擾
//---------------------------------------------------------------------------
int get_FontHeight(TFont *font, int mgn)
{
	int fh = abs(font->Height) + mgn;
	HWND hWnd = Application->MainForm? Application->MainForm->Handle : NULL;
	HDC dc = ::GetDC(hWnd);
	if (dc) {
		try {
			std::unique_ptr<TCanvas> cv(new TCanvas());
			cv->Handle = dc;
			cv->Font->Assign(font);
			fh = cv->TextHeight("Q") + mgn;
		}
		__finally {
			::ReleaseDC(hWnd, dc);
		}
	}

	return fh;
}

//---------------------------------------------------------------------------
//�w��L�����o�X�̃t�H���g���������f�B���O�������Ă��邩�H
//---------------------------------------------------------------------------
bool has_Leading(TCanvas *cv)
{
	return (cv->TextHeight("Q")>abs(cv->Font->Height));
}

//---------------------------------------------------------------------------
//ListBox �̍��ڂ̍�����ݒ�
//---------------------------------------------------------------------------
void set_ListBoxItemHi(TListBox *lp, double r)
{
	if (r<1.0) r = 1.0;
	lp->ItemHeight = get_FontHeight(lp->Font, abs(lp->Font->Height) * (r - 1.0) + 1);
}
//---------------------------------------------------------------------------
void set_ListBoxItemHi(TCheckListBox *lp, double r)
{
	if (r<1.0) r = 1.0;
	lp->ItemHeight = get_FontHeight(lp->Font, abs(lp->Font->Height) * (r - 1.0) + 1);
}
//---------------------------------------------------------------------------
void set_ListBoxInterLn(TListBox *lp, int d)
{
	lp->ItemHeight = get_FontHeight(lp->Font, d);
}

//---------------------------------------------------------------------------
//ListBox �� TStringList �����蓖�Ă� 
//---------------------------------------------------------------------------
void assign_ListBoxItems(TListBox *lp, TStringList *lst, int idx)
{
	lp->LockDrawing();
	lp->Items->Assign(lst);
	if (idx>=0 && idx<lp->Count) {
		lp->ItemIndex = idx;
		lp->TopIndex = std::max(lp->ItemIndex - (lp->ClientHeight/lp->ItemHeight/3), 0);
	}
	lp->UnlockDrawing();
}

//---------------------------------------------------------------------------
//ListBox �̃J�[�\���ړ�
//---------------------------------------------------------------------------
void ListBoxSetIndex(TListBox *lp, int idx)
{
	if (lp->Count==0) return;

	if (idx<0) {
		lp->ItemIndex = 0;
	}
	else if (idx==lp->ItemIndex) {
		//���̈�O��������X�N���[��
		int pn = lp->ClientHeight/lp->ItemHeight;
		if (lp->ItemIndex<lp->TopIndex)
			lp->TopIndex = std::max(lp->ItemIndex - LISTBOX_SCRMGN, 0);
		else if (lp->ItemIndex > lp->TopIndex + pn - 1)
			lp->TopIndex = std::max(lp->ItemIndex - pn + 1 + LISTBOX_SCRMGN, 0);
	}
	else {
		if (idx>=lp->Count) idx = lp->Count - 1;
		//���
		if (idx<lp->ItemIndex) {
			if (idx < lp->TopIndex+LISTBOX_SCRMGN)
				lp->TopIndex = std::max(idx - LISTBOX_SCRMGN, 0);
		}
		//����
		else {
			int pn = lp->ClientHeight/lp->ItemHeight;
			if (idx > (lp->TopIndex+pn - 1 - LISTBOX_SCRMGN))
				lp->TopIndex = std::max(idx - pn + 1 + LISTBOX_SCRMGN, 0);
		}
		lp->ItemIndex = idx;
	}
}
//---------------------------------------------------------------------------
void ListBoxCursorDown(TListBox *lp)
{
	int idx = lp->ItemIndex + 1;
	if (idx<lp->Count) ListBoxSetIndex(lp, idx);
}
//---------------------------------------------------------------------------
void ListBoxCursorDown(TListBox *lp, int n)
{
	ListBoxSetIndex(lp, std::min(lp->ItemIndex + n, lp->Count - 1));
}
//---------------------------------------------------------------------------
void ListBoxCursorUp(TListBox *lp)
{
	int idx = lp->ItemIndex - 1;
	if (idx>=0) ListBoxSetIndex(lp, idx);
}
//---------------------------------------------------------------------------
void ListBoxCursorUp(TListBox *lp, int n)
{
	ListBoxSetIndex(lp, std::max(lp->ItemIndex - n, 0));
}
//---------------------------------------------------------------------------
void ListBoxPageDown(TListBox *lp)
{
	ListBoxCursorDown(lp, lp->ClientHeight/lp->ItemHeight - 1);
}
//---------------------------------------------------------------------------
void ListBoxPageUp(TListBox *lp)
{
	ListBoxCursorUp(lp, lp->ClientHeight/lp->ItemHeight - 1);
}

//---------------------------------------------------------------------------
//�J���[�ݒ荀�ڂ̕`��
//---------------------------------------------------------------------------
void draw_ColorItem(TColor col, UnicodeString s, TCanvas *cv, TRect rc, bool hl)
{
	int yp = rc.Top;
	int col_wd = rc.Height() * 2;

	cv->Brush->Color = hl? clHighlight : clWindow;
	cv->Font->Color  = hl? clHighlightText : clWindowText;
	cv->FillRect(rc);
	cv->TextOut(rc.Left + col_wd + 2, yp, s);

	//�J���[
	TRect col_rc = rc;  col_rc.Right = rc.Left + col_wd;
	cv->Brush->Color = col;
	if (cv->Brush->Color!=Graphics::clNone) {
		cv->FillRect(col_rc);
	}
	else {
		cv->Brush->Color = clBtnFace;
		cv->FillRect(col_rc);
		cv->Font->Color  = clWindowText;
		cv->TextOut(col_rc.Left + 2, yp, "����");
	}
}

//---------------------------------------------------------------------------
//�t�H���g�ݒ荀�ڂ̕`��
//---------------------------------------------------------------------------
void draw_FontItem(TFont *fnt, UnicodeString s, TCanvas *cv, TRect rc, bool hl)
{
	int xp = rc.Left + 2;
	int yp = rc.Top;
	int fh = abs(cv->Font->Height);

	cv->Brush->Color = hl? clHighlight : clWindow;
	cv->Font->Color  = hl? clHighlightText : clWindowText;
	cv->FillRect(rc);
	cv->TextOut(xp, yp, s);
	xp += fh*10;	//***

	if (fnt) {
		//�T�C�Y
		UnicodeString szstr = fnt->Size;
		cv->TextOut(xp + cv->TextWidth(" 99") - cv->TextWidth(szstr), yp, szstr);
		xp += fh*2;
		//���O
		int sz = cv->Font->Size;
		cv->Font->Assign(fnt);
		cv->Font->Size	 = sz;
		cv->Brush->Color = hl? clHighlight : clWindow;
		cv->Font->Color  = hl? clHighlightText : clWindowText;
		cv->TextOut(xp, yp, fnt->Name);
	}
}

//---------------------------------------------------------------------------
//�O���b�h�̌��o���ݒ�
//---------------------------------------------------------------------------
void str_to_GridHeadder(TStringGrid *gp, UnicodeString s,
	UnicodeString sp)	//��؂� (default = "|")
{
	for (int i=0; i<gp->ColCount; i++) {
		UnicodeString itm = get_tkn(s, sp);
		if (itm.IsEmpty()) break;
		gp->Cells[i][0] = itm;
		s = get_tkn_r(s, sp);
	}
}
//---------------------------------------------------------------------------
//�f�[�^�O���b�h�̕����w�肵�āA�s�ƌ��o����ݒ�
//---------------------------------------------------------------------------
void set_GridWdHdr(TStringGrid *gp, int wd, int dtmax)
{
	if (wd==0) wd = 20;
	gp->ColCount = wd + 1;
	gp->RowCount = (int)(ceil(1.0*dtmax/wd) + 1);

	for (int i=1; i<gp->ColCount; i++) gp->Cells[i][0] = IntToStr(i);
	for (int i=1; i<gp->RowCount; i++) gp->Cells[0][i] = IntToStr((i - 1)*(gp->ColCount - 1));
}

//---------------------------------------------------------------------------
//TStringGrid �̃X�N���[���o�[�̂܂݃T�C�Y��ݒ�
//---------------------------------------------------------------------------
void set_GridScrBar(TStringGrid *gp)
{
	int invisi_rowcnt = gp->RowCount - gp->FixedRows -gp->VisibleRowCount;
	if (invisi_rowcnt>0 && gp->VisibleRowCount>0) {
		SCROLLINFO si_v0;
		::ZeroMemory(&si_v0, sizeof(SCROLLINFO));
		si_v0.cbSize = sizeof(SCROLLINFO);
		si_v0.fMask  = SIF_RANGE | SIF_PAGE;
		::GetScrollInfo(gp->Handle, SB_VERT, &si_v0);
		SCROLLINFO si_v1 = si_v0;

		int max0 = 127;
		si_v1.nPage = max0 * gp->VisibleRowCount / invisi_rowcnt;
		if (si_v1.nPage>127) si_v1.nPage = 127;
		int thumb_sz = (gp->ClientHeight - ::GetSystemMetrics(SM_CYVSCROLL)) * si_v1.nPage / (127 + si_v1.nPage);
		int thumb_min = ::GetSystemMetrics(SM_CXVSCROLL);
		if (thumb_sz<thumb_min) {
			si_v1.nMax = 127; si_v1.nPage = 0;
		}
		else {
			si_v1.nMax = max0 + si_v1.nPage - 1;
		}

		if (si_v0.nPage!=si_v1.nPage || si_v0.nMax!=si_v1.nMax) ::SetScrollInfo(gp->Handle, SB_VERT, &si_v1, TRUE);
	}

	int invisi_colcnt = gp->ColCount - gp->FixedCols -gp->VisibleColCount;
	if (invisi_colcnt>0) {
		SCROLLINFO si_h0;
		::ZeroMemory(&si_h0, sizeof(SCROLLINFO));
		si_h0.cbSize = sizeof(SCROLLINFO);
		si_h0.fMask  = SIF_RANGE | SIF_PAGE;
		::GetScrollInfo(gp->Handle, SB_HORZ, &si_h0);
		SCROLLINFO si_h1 = si_h0;

		int max0 = 127;
		si_h1.nPage = max0 * gp->VisibleColCount / invisi_colcnt;
		if (si_h1.nPage>127) si_h1.nPage = 127;
		int thumb_sz = (gp->ClientHeight - ::GetSystemMetrics(SM_CXHSCROLL)) * si_h1.nPage / (127 + si_h1.nPage);
		int thumb_min = ::GetSystemMetrics(SM_CYHSCROLL);
		if (thumb_sz<thumb_min) {
			si_h1.nMax = 127; si_h1.nPage = 0;
		}
		else {
			si_h1.nMax = max0 + si_h1.nPage - 1;
		}

		if (si_h0.nPage!=si_h1.nPage || si_h0.nMax!=si_h1.nMax) ::SetScrollInfo(gp->Handle, SB_HORZ, &si_h1, TRUE);
	}
}

//---------------------------------------------------------------------------
//������̏����\�[�g�֐�
//---------------------------------------------------------------------------
int __fastcall sort_comp_Str(TStringList *List, int Index1, int Index2)
{
	UnicodeString s1 = List->Strings[Index1];
	UnicodeString s2 = List->Strings[Index2];

	if (s1.IsEmpty() && s2.IsEmpty()) return 0;
	if (s1.IsEmpty()) return  1;
	if (s2.IsEmpty()) return -1;

	return CompareStr(s1, s2);
}
//---------------------------------------------------------------------------
//������̍~���\�[�g�֐�
//---------------------------------------------------------------------------
int __fastcall sort_comp_Str_Rev(TStringList *List, int Index1, int Index2)
{
	return -sort_comp_Str(List, Index1, Index2);
}
//---------------------------------------------------------------------------
//������𐔒l�Ƃ݂Ȃ��������\�[�g�֐�
//---------------------------------------------------------------------------
int __fastcall sort_comp_Number(TStringList *List, int Index1, int Index2)
{
	return (List->Strings[Index1].ToIntDef(0) - List->Strings[Index2].ToIntDef(0));
}
//---------------------------------------------------------------------------
//������𐔒l�Ƃ݂Ȃ����~���\�[�g�֐�
//---------------------------------------------------------------------------
int __fastcall sort_comp_Number_Rev(TStringList *List, int Index1, int Index2)
{
	return (List->Strings[Index2].ToIntDef(0) - List->Strings[Index1].ToIntDef(0));
}

//---------------------------------------------------------------------------
//�O���b�h���w���Ń\�[�g
//---------------------------------------------------------------------------
void sort_GridCol(
	TStringGrid *gp,	//�ΏۃO���b�h
	int sort_col,		//�Ώۗ�
	bool rev_sw,		//�t��	(default = false)
	bool num_sw)		//���l	(default = false)
{
	std::unique_ptr<TStringList> lst(new TStringList());
	lst->Assign(gp->Cols[sort_col]);

	int fix_rows = gp->FixedRows;
	for (int i=0; i<fix_rows; i++) lst->Delete(0);
	for (int i=fix_rows; i<gp->RowCount; i++) {
		TStringList *St2 = new TStringList();
		St2->Assign(gp->Rows[i]);
		lst->Objects[i - fix_rows] = St2;
	}

	if (num_sw) {
		if (rev_sw)
			lst->CustomSort(sort_comp_Number_Rev);
		else
			lst->CustomSort(sort_comp_Number);
	}
	else {
		if (rev_sw)
			lst->CustomSort(sort_comp_Str_Rev);
		else
			lst->CustomSort(sort_comp_Str);
	}

	for (int i=fix_rows; i<gp->RowCount; i++) {
		TStringList *lp = (TStringList*)lst->Objects[i - fix_rows];
		gp->Rows[i]->Assign(lp);
		delete lp;
	}
}
//---------------------------------------------------------------------------
//�w���r�֐���p���ăO���b�h���w���Ń\�[�g
//---------------------------------------------------------------------------
void sort_GridCol_Custom(
	TStringGrid *gp, 	//�ΏۃO���b�h
	int sort_col,		//�Ώۗ� 
	TStringListSortCompare compfunc)	//��r�֐�
{
	std::unique_ptr<TStringList> lst(new TStringList());
	lst->Assign(gp->Cols[sort_col]);

	int fix_rows = gp->FixedRows;
	for (int i=0; i<fix_rows; i++) lst->Delete(0);
	for (int i=fix_rows; i<gp->RowCount; i++) {
		TStringList *St2 = new TStringList();
		St2->Assign(gp->Rows[i]);
		lst->Objects[i - fix_rows] = St2;
	}

	lst->CustomSort(compfunc);

	for (int i=fix_rows; i<gp->RowCount; i++) {
		TStringList *lp = (TStringList*)lst->Objects[i - fix_rows];
		gp->Rows[i]->Assign(lp);
		delete lp;
	}
}

//---------------------------------------------------------------------------
//�����񂩂� ComboBox �ɍ��ڂ�ǉ�
//---------------------------------------------------------------------------
void str_to_ComboBox(TComboBox *cp, UnicodeString s,
	UnicodeString sp)	//��؂� (default = "|")
{
	for (;;) {
		UnicodeString itm = get_tkn(s, sp);
		if (itm.IsEmpty()) break;
		cp->Items->Add(itm);
		s = get_tkn_r(s, sp);
	}
}

//---------------------------------------------------------------------------
//ComboBox �ɗ�����ǉ�
//---------------------------------------------------------------------------
void add_ComboBox_history(TComboBox *cp, UnicodeString kwd)
{
	if (!kwd.IsEmpty()) {
		TStrings *lp = cp->Items;
		int idx = lp->IndexOf(kwd);
		if (idx!=0) {
			if (idx>0) lp->Delete(idx);
			lp->Insert(0, kwd);	//�擪�ɒǉ�
		}
		cp->Text = kwd;
	}
}
//---------------------------------------------------------------------------
//ComboBox �ɗ�������폜
//---------------------------------------------------------------------------
void del_ComboBox_history(TComboBox *cp, UnicodeString kwd)
{
	if (!kwd.IsEmpty()) {
		TStrings *lp = cp->Items;
		int idx = lp->IndexOf(kwd);
		if (idx!=-1) lp->Delete(idx);
		cp->Text = EmptyStr;
	}
}

//---------------------------------------------------------------------------
//�|�b�v�A�b�v���j���[���w��R���g���[���ʒu�ɕ\��
//---------------------------------------------------------------------------
void PopupCtrlPos(
	TPopupMenu *pp,
	TControl *cp, 		//�R���g���[��				(default = NULL : �}�E�X�ʒu�ɕ\��)
	bool show_bottom)	//�R���g���[���̉��[�ɕ\��	(default = false : ���S�ɕ\��)
{
	TPoint p;
	if (!cp)
		p = Mouse->CursorPos;
	else
		p = show_bottom? Point(cp->Left, cp->Top + cp->Height) : cp->ClientRect.CenterPoint();
	p = cp->ClientToScreen(p);
	pp->Popup(p.x, p.y);
}

//---------------------------------------------------------------------------
//�����^�u�̕`��
//���N���V�b�N�ȊO�̃e�[�}�ŉ����^�u���������`�悳��Ȃ��s��̑΍�
//---------------------------------------------------------------------------
void draw_BottomTab(TCustomTabControl *Control, int idx, const TRect rc, bool active)
{
	TTabControl *tp = (TTabControl*)Control;
	TCanvas *cv = tp->Canvas;
	//�w�i
	cv->Brush->Color = clBtnFace;
	cv->FillRect(rc);
	//����
	UnicodeString titstr = tp->Tabs->Strings[idx];
	cv->Font->Color = clBtnText;
	cv->TextOut(
		rc.Left + (rc.Width() - cv->TextWidth(titstr))/2,
		rc.Bottom - cv->TextHeight(titstr) - 4,
		titstr);
}

//---------------------------------------------------------------------------
//�`��X�V�̈ꎞ��~
//�� VCL�R���g���[���̏ꍇ�� LockDrawing() �𐄏�
//---------------------------------------------------------------------------
void set_Redraw_off(HWND h)
{
	::SendMessage(h, WM_SETREDRAW, 0, 0);
}
//---------------------------------------------------------------------------
//�`��X�V�̍ĊJ
//�� VCL�R���g���[���̏ꍇ�� UnlockDrawing() �𐄏�
//---------------------------------------------------------------------------
void set_Redraw_on(HWND h)
{
	::SendMessage(h, WM_SETREDRAW, 1, 0);
	::InvalidateRect(h, NULL, TRUE);
}

//---------------------------------------------------------------------------
//TUpDown �̏�����
//---------------------------------------------------------------------------
void init_TUpDown(TUpDown *udp, int n)
{
	udp->Position = n;
	TCustomEdit *ep = dynamic_cast<TCustomEdit *>(udp->Associate);
	if (ep) ep->Text = udp->Position;
}

//---------------------------------------------------------------------------
// TUpDown �Ɋ֘A�Â����Ă���ҏW���̒l���`�F�b�N
//---------------------------------------------------------------------------
bool check_TUpDown(TUpDown *udp)
{
	bool ret = true;
	if (udp->Associate) {
		TCustomEdit *ep = dynamic_cast<TCustomEdit *>(udp->Associate);
		if (ep) {
			int n = ep->Text.ToIntDef(udp->Min - 1);
			if (n<udp->Min || n>udp->Max) ret = false;
		}
	}
	return ret;
}

//---------------------------------------------------------------------------
//�c�[���p�[�̎w��{�^����Down
//---------------------------------------------------------------------------
void down_ToolButton(TToolBar *tb, int idx)
{
	for (int i=0; i<tb->ButtonCount; i++) {
		TToolButton *bp = tb->Buttons[i];
		if (bp->Tag == idx) {
			bp->Down = true; break;
		}
	}
}

//---------------------------------------------------------------------------
//TStringGrind �� InplaceEditor ���擾
//---------------------------------------------------------------------------
TInplaceEdit *GetInplaceEditor(TStringGrid *gp)
{
	TInplaceEdit *ep = NULL;
	for (int i=0; i<gp->ControlCount; i++) {
		if (gp->Controls[i]->ClassNameIs("TInplaceEdit")) {
			ep = (TInplaceEdit*)gp->Controls[i];	break;
		}
	}
	return ep;
}

//---------------------------------------------------------------------------
//�|�C���^�[�������I�ɋK��̃{�^����Ɉړ�
//---------------------------------------------------------------------------
void move_to_DefButton(TButton *bp)
{
	BOOL sw;
	if (::SystemParametersInfo(SPI_GETSNAPTODEFBUTTON, 0, &sw, 0) && sw) {
		Mouse->CursorPos = Point(bp->ClientOrigin.x + bp->Width/2, bp->ClientOrigin.y + bp->Height/2);
	}
}
//---------------------------------------------------------------------------
