//----------------------------------------------------------------------//
// ���̑��̔ėp�֐�														//
//----------------------------------------------------------------------//
#ifndef USE_COMMON_PCH
#include <vcl.h>
#include <tchar.h>
#include <memory>
#include <algorithm>
#include <System.StrUtils.hpp>
#include <System.Win.Registry.hpp>
#pragma hdrstop
#endif

#include "usr_str.h"
#include "usr_file_ex.h"
#include "usr_misc.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//�l�̌ܓ�
//---------------------------------------------------------------------------
int round_i(double v)
{
	return (int)(v + 0.5);
}

//---------------------------------------------------------------------------
//�w��E�B���h�E�̃e�L�X�g���擾
//---------------------------------------------------------------------------
UnicodeString get_WindowText(HWND hWnd)
{
	_TCHAR tbuf[1024];
	return ((::GetWindowText(hWnd, tbuf, 1023)>0)? UnicodeString(tbuf) : EmptyStr);
}
//---------------------------------------------------------------------------
//�w��E�B���h�E�̃N���X�����擾
//---------------------------------------------------------------------------
UnicodeString get_ClassName(HWND hWnd)
{
	_TCHAR cbuf[256];
	return ((::GetClassName(hWnd, cbuf, 255)>0)? UnicodeString(cbuf) : EmptyStr);
}

//---------------------------------------------------------------------------
// �Y������E�B���h�E�̃��X�g�A�b�v
// wcls : �N���X   (���S��v)
// wtit : �^�C�g�� (������v/���K�\����)
//---------------------------------------------------------------------------
bool GetHwndList(UnicodeString wcls, UnicodeString wtit, TList *hlist)
{
	if (wcls.IsEmpty() && wtit.IsEmpty()) return false;

	hlist->Clear();

	try {
		HWND hTemp = ::GetWindow(Application->Handle, GW_HWNDFIRST);
		while (hTemp) {
			if (::IsWindowVisible(hTemp) || ::IsIconic(hTemp)) {
				UnicodeString tbuf = get_WindowText(hTemp);
				UnicodeString cbuf = get_ClassName(hTemp);
				do {
					if (!wtit.IsEmpty() && ptn_match_str(wtit, tbuf).IsEmpty()) break;
					if (!wcls.IsEmpty() && cbuf != wcls) break;
					hlist->Add(hTemp);
				} while (0);
			}
			hTemp = ::GetWindow(hTemp, GW_HWNDNEXT);
		}
		return (hlist->Count > 0);
	}
	catch (...) {
		return false;
	}
}

//---------------------------------------------------------------------------
//�}�E�X�J�[�\���ʒu�̃E�B���h�E���擾
//---------------------------------------------------------------------------
HWND get_window_from_pos()
{
	POINT p;
	::GetCursorPos(&p);
	return ::WindowFromPoint(p);
}

//---------------------------------------------------------------------------
//�E�B���h�E�����`�̎擾 (Vista�ȍ~�̊g���t���[���ɑΉ�)
//---------------------------------------------------------------------------
TRect get_window_rect(HWND hWnd)
{
	TRect rc;
	if (::DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc, sizeof(rc))!=S_OK) ::GetWindowRect(hWnd, &rc);
	return rc;
}
//---------------------------------------------------------------------------
//�E�B���h�E�T�C�Y�ݒ� (Vista�ȍ~�̊g���t���[���ɑΉ�)
//---------------------------------------------------------------------------
void set_window_pos_ex(HWND hWnd, TRect rc)
{
	TRect rc1, rc2;
	::GetWindowRect(hWnd, &rc1);
	if (::DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc2, sizeof(rc2))!=S_OK) rc2 = rc1;
	rc.Left   += (rc1.Left   - rc2.Left);
	rc.Right  += (rc1.Right  - rc2.Right);
	rc.Top	  += (rc1.Top    - rc2.Top);
	rc.Bottom += (rc1.Bottom - rc2.Bottom);

	if (::IsIconic(hWnd)) ::ShowWindow(hWnd, SW_RESTORE);
	::SetWindowPos(hWnd, HWND_TOP, rc.Left, rc.Top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
}

//---------------------------------------------------------------------------
//��Ɏ�O�ɕ\��
//---------------------------------------------------------------------------
void set_TopMost(TForm *fp, bool enabled)
{
	::EndDeferWindowPos(::DeferWindowPos(::BeginDeferWindowPos(1),
		fp->Handle, enabled? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE));
}

//---------------------------------------------------------------------------
//�T�E���h�Đ�
//---------------------------------------------------------------------------
bool play_sound(
	UnicodeString fnam,		//�t�@�C����(���s�p�X����̑��Ύw���)/ �T�E���h���ʎq
	unsigned int  flag)		//SND_SYNC or SND_ASYNC (default = SND_ASYNC)
{
	bool is_snd_id = false;
	std::unique_ptr<TRegistry> reg(new TRegistry());
	reg->RootKey = HKEY_CURRENT_USER;
	if (reg->OpenKeyReadOnly("AppEvents\\Schemes\\Apps\\.Default")) {
		std::unique_ptr<TStringList> lst(new TStringList());
		reg->GetKeyNames(lst.get());
		is_snd_id = (lst->IndexOf(fnam)!=-1);
	}

	//�T�E���h���ʎq
	if (is_snd_id) {
		PlaySound(fnam.c_str(), NULL, SND_ALIAS|SND_NODEFAULT|flag);
		return true;
	}
	//WAV�t�@�C����
	else {
		fnam = rel_to_absdir(fnam, ExtractFilePath(Application->ExeName));
		if (FileExists(fnam)) {
			::sndPlaySound(fnam.c_str(), flag);
			return true;
		}
		else {
			return false;
		}
	}
}

//---------------------------------------------------------------------------
//�G���[���b�Z�[�W
//---------------------------------------------------------------------------
void msgbox_ERR(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "�G���[";	//�f�t�H���g
	Application->MessageBox(msg.c_str(), tit.c_str(), MB_OK|MB_ICONERROR);
}
//---------------------------------------------------------------------------
//�x�����b�Z�[�W
//---------------------------------------------------------------------------
void msgbox_WARN(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "�x��";	//�f�t�H���g
	Application->MessageBox(msg.c_str(), tit.c_str(), MB_OK|MB_ICONWARNING);
}

//---------------------------------------------------------------------------
//���b�Z�[�W
//---------------------------------------------------------------------------
void msgbox_OK(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "�m�F";	//�f�t�H���g
	Application->MessageBox(msg.c_str(), tit.c_str(), MB_OK);
}
//---------------------------------------------------------------------------
//�m�F���b�Z�[�W
//---------------------------------------------------------------------------
bool msgbox_Y_N(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "�m�F";	//�f�t�H���g
	int res = Application->MessageBox(msg.c_str(), tit.c_str(), MB_YESNO|MB_ICONQUESTION);
	return (res==IDYES);
}
//---------------------------------------------------------------------------
int msgbox_Y_N_C(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "�m�F";	//�f�t�H���g
	return Application->MessageBox(msg.c_str(), tit.c_str(), MB_YESNOCANCEL|MB_ICONQUESTION);
}

//---------------------------------------------------------------------------
//IME���J���Ă��邩?
//---------------------------------------------------------------------------
bool is_IME_Open(HWND hWnd)
{
	bool ret  = false;
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		ret = ::ImmGetOpenStatus(hIMC);
		::ImmReleaseContext(hWnd, hIMC);
	}
	return ret;
}
//---------------------------------------------------------------------------
//IME���͒�?
//---------------------------------------------------------------------------
bool is_IME_Typing(HWND hWnd)
{
	bool ret = false;
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		ret = ::ImmGetOpenStatus(hIMC) && ::ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0)>0;
		::ImmReleaseContext(hWnd, hIMC);
	}
	return ret;
}
//---------------------------------------------------------------------------
//IME���͂Ȃ�
//---------------------------------------------------------------------------
bool is_IME_Empty(HWND hWnd)
{
	bool ret = false;
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		ret = ::ImmGetOpenStatus(hIMC) && ::ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0)==0;
		::ImmReleaseContext(hWnd, hIMC);
	}
	return ret;
}
//---------------------------------------------------------------------------
//IME�����
//---------------------------------------------------------------------------
void CloseIME(HWND hWnd)
{
	HIMC hIMC = ::ImmGetContext(hWnd);
	if (hIMC) {
		if (::ImmGetOpenStatus(hIMC)) ::ImmSetOpenStatus(hIMC, FALSE);
		::ImmReleaseContext(hWnd, hIMC);
	}
}

//---------------------------------------------------------------------------
// �G�f�B�^�Ńt�@�C�����J��(�s�ԍ�������΃^�O�W�����v)
//---------------------------------------------------------------------------
bool open_by_editor(
	UnicodeString fnam,		//�t�@�C����
							//�t�@�C���� (�s�ԍ�)
							//�t�@�C���� �s�ԍ�:
							//	�t�@�C������ " �ň͂܂�Ă��Ă��A�s�ԍ���ɕ����񂪂����Ă���
	UnicodeString editor,
	UnicodeString frmt)		//�p�����[�^�̏��� (default=EmptyStr)
							//	$F: �t�@�C����  $L: �s�ԍ�
{
	if (editor.IsEmpty() || fnam.IsEmpty()) return false;

	//�t�@�C�����ƍs�ԍ������𕪂���
	UnicodeString lstr = EmptyStr;
	if (fnam[1]=='\"') {
		fnam.Delete(1, 1);
		lstr = get_tkn_r(fnam, "\"").Trim();
		fnam = get_tkn(fnam, "\"");
	}
	else {
		int p;
		int p0 = fnam.Pos(" ");
		int p1 = fnam.Pos("(");
		if (p0==0) p = p1; else if (p1==0) p = p0; else p = std::min(p0, p1);
		if (p>0) {
			lstr = fnam.SubString(p + 1, fnam.Length() - p);
			fnam = fnam.SubString(1, p - 1);
		}
	}

	//�s�ԍ����擾
	int p;
	int p0 = lstr.Pos(":");
	int p1 = lstr.Pos(")");
	if (p0==0) p = p1; else if (p1==0) p = p0; else p = std::min(p0, p1);
	if (p>0) {
		lstr = lstr.SubString(1, p - 1);
		if (ContainsText(lstr, "(")) lstr = get_tkn_r(lstr, "(");
		lstr = Trim(lstr);
	}
	int lno = !lstr.IsEmpty()? lstr.ToIntDef(1) : 1;

	//�t�@�C�����`�F�b�N
	if (!FileExists(fnam)) return false;
	fnam = add_quot_if_spc(fnam);

	//�N���p�����[�^�̍\��
	UnicodeString prmstr;
	if (!frmt.IsEmpty()) {
		prmstr = frmt;
		prmstr = ReplaceStr(prmstr, "$F", fnam);
		prmstr = ReplaceStr(prmstr, "$L", IntToStr(lno));
	}
	else {
		prmstr = fnam;
	}

	return (
		::ShellExecute(NULL, _T("open"), editor.c_str(), prmstr.c_str(), NULL,SW_SHOWNORMAL) > (HINSTANCE)32);
}

//---------------------------------------------------------------------------
//TStringList �Ƀt�@�C����ǂݍ���
//---------------------------------------------------------------------------
bool load_StrList(
	UnicodeString fnam,	//�t�@�C����
	TStringList *list)	//���X�g
{
	try {
		list->LoadFromFile(fnam);
		return true;
	}
	catch(...) {
		return false;
	}
}
//---------------------------------------------------------------------------
//TStringList ����t�@�C���ɕۑ�
//---------------------------------------------------------------------------
bool save_StrList(
	UnicodeString fnam,	//�t�@�C����
	TStringList *list)	//���X�g
{
	try {
		list->SaveToFile(fnam);
		return true;
	}
	catch(...) {
		return false;
	}
}

//---------------------------------------------------------------------------
//�摜�t�@�C�����r�b�g�}�b�v�ɓǂݍ���
//---------------------------------------------------------------------------
bool load_Image(UnicodeString fnam, Graphics::TBitmap *o_bmp)
{
	try {
		std::unique_ptr<TWICImage> img(new TWICImage());
		img->LoadFromFile(fnam);
		o_bmp->Assign(img.get());
		return !o_bmp->Empty;
	}
	catch(...) {
		return false;
	}
}

//---------------------------------------------------------------------------
// �w��t�@�C�����J��(ShellExecute)
// cmd ���V���[�g�J�b�g�̏ꍇ�̓����N����擾���ċN���Aprm��fld�͖���
// �f�t�H���g(�ȗ���) prm="", fld="",  nShowCmd=SW_SHOWNORMAL, wait=0(T.O. ms);
//---------------------------------------------------------------------------
bool execute_ex(UnicodeString cmd, UnicodeString prm, UnicodeString fld,
	int nShowCmd, int wait)
{
	if (ExtractFileExt(cmd.UpperCase())==".LNK") {
		_TCHAR l_cmd[MAX_PATH + 1];

		// �V���[�g�J�b�g�̃����N����擾(MSI�ɂ����̑Ή�)
		typedef UINT(WINAPI *FP_MsiGetShortcutTarget)(LPCTSTR,LPTSTR,LPTSTR,LPTSTR);
		typedef UINT(WINAPI *FP_MsiGetComponentPath)(LPCTSTR,LPCTSTR,LPTSTR,DWORD*);
		_TCHAR prd_cod[40];
		_TCHAR cmp_id[40];

		HMODULE hMsiDLL;
		bool msi_flag = false;
		do {
			hMsiDLL = ::LoadLibrary(_T("MSI.DLL"));	if (!hMsiDLL) break;
			FP_MsiGetShortcutTarget MsiGetShortcutTarget
				= (FP_MsiGetShortcutTarget)::GetProcAddress(hMsiDLL, "MsiGetShortcutTargetW");
			if (!MsiGetShortcutTarget) break;
			FP_MsiGetComponentPath MsiGetComponentPath
				= (FP_MsiGetComponentPath)::GetProcAddress(hMsiDLL, "MsiGetComponentPathW");
			if (!MsiGetComponentPath) break;
			if (MsiGetShortcutTarget(
				cmd.c_str(), prd_cod, NULL, cmp_id) != ERROR_SUCCESS) break;
			DWORD bufsz = sizeof(l_cmd);
			MsiGetComponentPath(prd_cod, cmp_id, l_cmd, &bufsz);
			if (bufsz==0) break;
			if (!FileExists(l_cmd)) break;
			msi_flag = true;	//�����N��擾�ɐ���
		} while (0);
		if (hMsiDLL) ::FreeLibrary(hMsiDLL);

		// �V���[�g�J�b�g�̏������擾
		IShellLink   *psl;
		IPersistFile *ppf;
		::CoInitialize(NULL);
		if (::CoCreateInstance(CLSID_ShellLink, NULL, 
			CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&psl) == S_OK)
		{
			WCHAR wcLinkFile[MAX_PATH + 1];
			_TCHAR l_prm[MAX_PATH + 1];
			_TCHAR l_fld[MAX_PATH + 1];
			if (psl->QueryInterface(IID_IPersistFile, (void **)&ppf) == S_OK) {
				::MultiByteToWideChar(CP_ACP, 0, AnsiString(cmd).c_str(), -1, wcLinkFile, MAX_PATH);
				if (ppf->Load(wcLinkFile, STGM_READ) == S_OK) {
					if (psl->Resolve(NULL, SLR_UPDATE) == NOERROR) {
						if (!msi_flag) psl->GetPath(l_cmd, 256, NULL, 0);
						psl->GetArguments(l_prm, 256);
						psl->GetWorkingDirectory(l_fld, 256);
						psl->GetShowCmd(&nShowCmd);
						prm = l_prm;
						fld = l_fld;
					}
				}
				ppf->Release();
			}
			psl->Release();
		}
		::CoUninitialize();
		cmd = l_cmd;
	}

	if (wait>0) {
		//�N�������A�v���̓��͂��L���ɂȂ�܂ő҂�
		STARTUPINFO sinf;
		::ZeroMemory(&sinf, sizeof(sinf) );
		sinf.cb = sizeof(sinf);
		sinf.wShowWindow = (WORD)nShowCmd;
		PROCESS_INFORMATION pinf;
		if (!prm.IsEmpty()) cmd += (" " + prm);
		if (CreateProcess(
			NULL, cmd.c_str(), NULL,NULL, FALSE, 0, NULL,
			(fld.IsEmpty()? NULL : fld.c_str()),
			&sinf,&pinf) != 0)
		{
			::WaitForInputIdle(pinf.hProcess, wait);
		    ::CloseHandle(pinf.hProcess);
			::CloseHandle(pinf.hThread );
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return (
			::ShellExecute(NULL, _T("open"), cmd.c_str(), prm.c_str(), fld.c_str(), nShowCmd) > (HINSTANCE)32);
	}
}

//---------------------------------------------------------------------------
// �����񂩂琔�l�͈͂����X�g�֎擾
// �G���[���ɂ� s �Ƀ��b�Z�[�W
//---------------------------------------------------------------------------
int get_no_list(UnicodeString &s, TStringList *lst)
{
	lst->Clear();
	UnicodeString tmp;

	try {
		for (;;) {
			if (s.IsEmpty()) break;
			int p = s.Pos(",");
			if (p>0) {
				tmp = s.SubString(1, p - 1);
				s.Delete(1, p);
			}
			else {
				tmp = s; s = EmptyStr;
			}

			if (!tmp.IsEmpty()) {
				p = tmp.Pos("-");
				if (p>0) {
					int out0 = tmp.SubString(1, p - 1).ToIntDef(-1);
					if (out0==-1) Abort();
					tmp.Delete(1, p);
					int out1 = tmp.ToIntDef(-1);
					if (out1==-1) Abort();
					if (out1<out0) Abort();
					for (int i=out0; i<=out1; i++) lst->Add(IntToStr(i));
				}
				else {
					int outn = tmp.ToIntDef(-1);
					if (outn==-1) Abort();
					lst->Add(tmp.Trim());
				}
			}
		}
	}
	catch (...) {
		s = "�G���[: �s���ȏ����ł�";
		lst->Clear();
	}

	return lst->Count;
}

//---------------------------------------------------------------------------
//=�ȍ~�̐����l���擾
//---------------------------------------------------------------------------
int get_eq_int(UnicodeString src, int def)
{
	UnicodeString vstr = get_tkn_r(src, "=").Trim();
	return vstr.IsEmpty()? def : vstr.ToIntDef(def);
}

//---------------------------------------------------------------------------
//fnam �Ƀh���C�u�����Ȃ����
//���s�t�@�C���̃f�B���N�g������̑��΃t�@�C�����ɕς���
//�t�@�C�������݂��Ȃ���� false ��Ԃ�
//---------------------------------------------------------------------------
bool get_file_name_r(UnicodeString &fnam)
{
	if (fnam.IsEmpty()) return false;
	if (ExtractFileDrive(fnam).IsEmpty())
		fnam = ExtractFilePath(Application->ExeName) + fnam;
	return FileExists(fnam);
}

//---------------------------------------------------------------------------
//���s�t�@�C���̃f�B���N�g������̑��΃t�@�C�����ɕϊ�
//---------------------------------------------------------------------------
UnicodeString to_filename_r(UnicodeString fnam)
{
	UnicodeString exedir = ExtractFilePath(Application->ExeName);
	if (StartsText(exedir, fnam)) fnam.Delete(1, exedir.Length());
	return fnam;
}

//---------------------------------------------------------------------------
//�b�J�E���g�l������������ɕϊ�
//---------------------------------------------------------------------------
UnicodeString Sec2TimeStr(int cnt)
{
	int s = (unsigned short)(cnt % 60);	cnt /= 60;
	int m = (unsigned short)(cnt % 60);
	int h = (unsigned short)(cnt/60);
	return UnicodeString().sprintf(_T("%02d:%02d:%02d"), h,m,s);
}

//---------------------------------------------------------------------------
//�����񂩂�DMX�`�����l��No.��(0�x�[�X)
// [A�`H]nnn
//---------------------------------------------------------------------------
int str_to_dmxch(
	UnicodeString s,
	int max_ch)			//�ő�`�����l��	(default = 4096/H512)
{
	int cn = -1;
	if (!s.IsEmpty() && !SameText(s, "All")) {
		s = s.UpperCase();
		switch (s[1]) {
		case 'A': case 'B': case 'C': case 'D':
		case 'E': case 'F': case 'G': case 'H':
			cn = StrToIntDef(s.SubString(2, s.Length() - 1), -1);
			if (cn>512) cn = -1; else cn--;
			if (cn!=-1) cn += ((s[1] - 'A') * 512);
			break;
		default:
			cn = StrToIntDef(s, -1);
			if (cn<1 || cn>=max_ch) cn = -1; else cn--;
		}
	}
	return cn;
}
//---------------------------------------------------------------------------
//DMX�`�����l��No.���當�����
//---------------------------------------------------------------------------
UnicodeString dmxch_to_str(
	int  cn,	//��΃`�����l��
	bool un_ch)	//default = true (���j�o�[�X+�`�����l��)
{
	if (cn<0) return EmptyStr;

	UnicodeString ret_str;
	if (!un_ch)
		ret_str.sprintf(_T("%u"), cn + 1);
	else
		ret_str.sprintf(_T("%1c%03u"), 'A' + cn/512, cn%512 + 1);

	return ret_str;
}

//---------------------------------------------------------------------------
// �����񂩂琔�l�͈͂����X�g�֎擾(Ch.No.��1�`)
// �G���[���ɂ� s �Ƀ��b�Z�[�W(�s���ȏ����ł�)
//---------------------------------------------------------------------------
int get_dmxch_list(UnicodeString &s, TStringList *lst)
{
	lst->Clear();
	UnicodeString tmp;

	try {
		for (;;) {
			if (s.IsEmpty()) break;
			int p = s.Pos(",");
			if (p>0) {
				tmp = s.SubString(1, p - 1);
				s.Delete(1, p);
			}
			else {
				tmp = s; s = EmptyStr;
			}

			if (!tmp.IsEmpty()) {
				p = tmp.Pos("-");
				if (p>0) {
					int out0 = str_to_dmxch(tmp.SubString(1, p - 1));
					if (out0==-1)  Abort();
					tmp.Delete(1, p);
					int out1 = str_to_dmxch(tmp);
					if (out1==-1)  Abort();
					if (out1<out0) Abort();
					for (int i=out0; i<=out1; i++) lst->Add(IntToStr(i + 1));
				}
				else {
					int outn = str_to_dmxch(tmp);
					if (outn==-1)  Abort();
					lst->Add(IntToStr(outn + 1));
				}
			}
		}
	}
	catch(EAbort &e) {
		s = "�G���[: �s���ȏ����ł�";
		lst->Clear();
	}

	return lst->Count;
}

//---------------------------------------------------------------------------
// TStringList�̒l���疼�O���擾
//---------------------------------------------------------------------------
UnicodeString name_of_value(TStringList *lst, UnicodeString value)
{
	int idx = -1;
	for (int i=0; i<lst->Count; i++) {
		if (get_tkn_r(lst->Strings[i],"=") == value) {
			idx = i; break;
		}
	}
	if (idx!=-1)
		return get_tkn(lst->Strings[idx],"=");
	else
		return EmptyStr;
}

//---------------------------------------------------------------------------
//�p�����[�^�̃o�C�g�������擾
//---------------------------------------------------------------------------
UnicodeString get_ByteInfo(UnicodeString strbuf, int lmt)
{
	UnicodeString infstr = EmptyStr;
	UnicodeString tmpbuf;
	int cnt = 0;
	try {
		while (1) {
			strbuf = strbuf.Trim();
			if (strbuf.IsEmpty()) break;
			if (strbuf.IsDelimiter("\"", 1)) {	//�擪�� "
				strbuf.Delete(1, 1); tmpbuf = EmptyStr;
				while (1) {
					int qp = strbuf.Pos("\"");
					if (qp) {
						//" ����
						if (qp<strbuf.Length()) {
							//"�`" ���� "
							if (strbuf.IsDelimiter("\"", qp + 1)) {
								tmpbuf += strbuf.SubString(1, qp);
								strbuf	= strbuf.Delete(1, qp + 1);
							}
							//�Ή����� "
							else {
								tmpbuf += strbuf.SubString(1, qp - 1);
								strbuf	= strbuf.Delete(1, qp).Trim();
								if (strbuf.IsDelimiter(",", 1))
									strbuf = strbuf.Delete(1, 1);
								else
									throw EAbort("�J���}���K�v");
								break;
							}
						}
						//������ " (�Ō�̍���)
						else {
							tmpbuf += strbuf.Delete(qp, 1);
							strbuf = EmptyStr; break;
						}
					}
					else {
						//�Ή����� " ���Ȃ�
						tmpbuf = strbuf;
						strbuf = EmptyStr;
						break;
					}
				}
				cnt += tmpbuf.Length();
			}
			else {
				int cp = strbuf.Pos(",");
				if (cp) {
					tmpbuf = strbuf.SubString(1, cp - 1);
					strbuf = strbuf.Delete(1, cp);
				}
				//�Ō�̍���
				else {
					tmpbuf = strbuf;
					strbuf = EmptyStr;
				}

				int d = tmpbuf.ToIntDef(-1);
				if (d>=0 && d<256)
					cnt ++;
				else if (tmpbuf!="0x")
					throw EAbort("�s���Ȓl");
			}
		}

		if (cnt<=lmt)
			infstr.sprintf(_T("%u/%u �o�C�g"), cnt, lmt);
		else
			infstr.sprintf(_T("%u/%u �o�C�g ����!"), cnt, lmt);

	}
	catch(EAbort &e) {
		infstr.sprintf(_T("\?\?/%u �o�C�g %s"), lmt, e.Message.c_str());
	}

	return infstr;
}
//---------------------------------------------------------------------------
