//----------------------------------------------------------------------//
// その他の汎用関数														//
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
//四捨五入
//---------------------------------------------------------------------------
int round_i(double v)
{
	return (int)(v + 0.5);
}

//---------------------------------------------------------------------------
//指定ウィンドウのテキストを取得
//---------------------------------------------------------------------------
UnicodeString get_WindowText(HWND hWnd)
{
	_TCHAR tbuf[1024];
	return ((::GetWindowText(hWnd, tbuf, 1023)>0)? UnicodeString(tbuf) : EmptyStr);
}
//---------------------------------------------------------------------------
//指定ウィンドウのクラス名を取得
//---------------------------------------------------------------------------
UnicodeString get_ClassName(HWND hWnd)
{
	_TCHAR cbuf[256];
	return ((::GetClassName(hWnd, cbuf, 255)>0)? UnicodeString(cbuf) : EmptyStr);
}

//---------------------------------------------------------------------------
// 該当するウィンドウのリストアップ
// wcls : クラス   (完全一致)
// wtit : タイトル (部分一致/正規表現可)
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
//マウスカーソル位置のウィンドウを取得
//---------------------------------------------------------------------------
HWND get_window_from_pos()
{
	POINT p;
	::GetCursorPos(&p);
	return ::WindowFromPoint(p);
}

//---------------------------------------------------------------------------
//ウィンドウ長方形の取得 (Vista以降の拡張フレームに対応)
//---------------------------------------------------------------------------
TRect get_window_rect(HWND hWnd)
{
	TRect rc;
	if (::DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc, sizeof(rc))!=S_OK) ::GetWindowRect(hWnd, &rc);
	return rc;
}
//---------------------------------------------------------------------------
//ウィンドウサイズ設定 (Vista以降の拡張フレームに対応)
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
//常に手前に表示
//---------------------------------------------------------------------------
void set_TopMost(TForm *fp, bool enabled)
{
	::EndDeferWindowPos(::DeferWindowPos(::BeginDeferWindowPos(1),
		fp->Handle, enabled? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE));
}

//---------------------------------------------------------------------------
//サウンド再生
//---------------------------------------------------------------------------
bool play_sound(
	UnicodeString fnam,		//ファイル名(実行パスからの相対指定可)/ サウンド識別子
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

	//サウンド識別子
	if (is_snd_id) {
		PlaySound(fnam.c_str(), NULL, SND_ALIAS|SND_NODEFAULT|flag);
		return true;
	}
	//WAVファイル名
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
//エラーメッセージ
//---------------------------------------------------------------------------
void msgbox_ERR(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "エラー";	//デフォルト
	Application->MessageBox(msg.c_str(), tit.c_str(), MB_OK|MB_ICONERROR);
}
//---------------------------------------------------------------------------
//警告メッセージ
//---------------------------------------------------------------------------
void msgbox_WARN(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "警告";	//デフォルト
	Application->MessageBox(msg.c_str(), tit.c_str(), MB_OK|MB_ICONWARNING);
}

//---------------------------------------------------------------------------
//メッセージ
//---------------------------------------------------------------------------
void msgbox_OK(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "確認";	//デフォルト
	Application->MessageBox(msg.c_str(), tit.c_str(), MB_OK);
}
//---------------------------------------------------------------------------
//確認メッセージ
//---------------------------------------------------------------------------
bool msgbox_Y_N(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "確認";	//デフォルト
	int res = Application->MessageBox(msg.c_str(), tit.c_str(), MB_YESNO|MB_ICONQUESTION);
	return (res==IDYES);
}
//---------------------------------------------------------------------------
int msgbox_Y_N_C(UnicodeString msg, UnicodeString tit)
{
	if (tit.IsEmpty()) tit = "確認";	//デフォルト
	return Application->MessageBox(msg.c_str(), tit.c_str(), MB_YESNOCANCEL|MB_ICONQUESTION);
}

//---------------------------------------------------------------------------
//IMEを開いているか?
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
//IME入力中?
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
//IME入力なし
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
//IMEを閉じる
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
// エディタでファイルを開く(行番号があればタグジャンプ)
//---------------------------------------------------------------------------
bool open_by_editor(
	UnicodeString fnam,		//ファイル名
							//ファイル名 (行番号)
							//ファイル名 行番号:
							//	ファイル名は " で囲まれていても可、行番号後に文字列があっても可
	UnicodeString editor,
	UnicodeString frmt)		//パラメータの書式 (default=EmptyStr)
							//	$F: ファイル名  $L: 行番号
{
	if (editor.IsEmpty() || fnam.IsEmpty()) return false;

	//ファイル名と行番号部分を分ける
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

	//行番号を取得
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

	//ファイル名チェック
	if (!FileExists(fnam)) return false;
	fnam = add_quot_if_spc(fnam);

	//起動パラメータの構成
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
//TStringList にファイルを読み込む
//---------------------------------------------------------------------------
bool load_StrList(
	UnicodeString fnam,	//ファイル名
	TStringList *list)	//リスト
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
//TStringList からファイルに保存
//---------------------------------------------------------------------------
bool save_StrList(
	UnicodeString fnam,	//ファイル名
	TStringList *list)	//リスト
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
//画像ファイルをビットマップに読み込む
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
// 指定ファイルを開く(ShellExecute)
// cmd がショートカットの場合はリンク先を取得して起動、prmとfldは無視
// デフォルト(省略可) prm="", fld="",  nShowCmd=SW_SHOWNORMAL, wait=0(T.O. ms);
//---------------------------------------------------------------------------
bool execute_ex(UnicodeString cmd, UnicodeString prm, UnicodeString fld,
	int nShowCmd, int wait)
{
	if (ExtractFileExt(cmd.UpperCase())==".LNK") {
		_TCHAR l_cmd[MAX_PATH + 1];

		// ショートカットのリンク先を取得(MSIによるもの対応)
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
			msi_flag = true;	//リンク先取得に成功
		} while (0);
		if (hMsiDLL) ::FreeLibrary(hMsiDLL);

		// ショートカットの諸情報を取得
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
		//起動したアプリの入力が有効になるまで待つ
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
// 文字列から数値範囲をリストへ取得
// エラー時には s にメッセージ
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
		s = "エラー: 不正な書式です";
		lst->Clear();
	}

	return lst->Count;
}

//---------------------------------------------------------------------------
//=以降の整数値を取得
//---------------------------------------------------------------------------
int get_eq_int(UnicodeString src, int def)
{
	UnicodeString vstr = get_tkn_r(src, "=").Trim();
	return vstr.IsEmpty()? def : vstr.ToIntDef(def);
}

//---------------------------------------------------------------------------
//fnam にドライブ名がなければ
//実行ファイルのディレクトリからの相対ファイル名に変える
//ファイルが存在しなければ false を返す
//---------------------------------------------------------------------------
bool get_file_name_r(UnicodeString &fnam)
{
	if (fnam.IsEmpty()) return false;
	if (ExtractFileDrive(fnam).IsEmpty())
		fnam = ExtractFilePath(Application->ExeName) + fnam;
	return FileExists(fnam);
}

//---------------------------------------------------------------------------
//実行ファイルのディレクトリからの相対ファイル名に変換
//---------------------------------------------------------------------------
UnicodeString to_filename_r(UnicodeString fnam)
{
	UnicodeString exedir = ExtractFilePath(Application->ExeName);
	if (StartsText(exedir, fnam)) fnam.Delete(1, exedir.Length());
	return fnam;
}

//---------------------------------------------------------------------------
//秒カウント値を時刻文字列に変換
//---------------------------------------------------------------------------
UnicodeString Sec2TimeStr(int cnt)
{
	int s = (unsigned short)(cnt % 60);	cnt /= 60;
	int m = (unsigned short)(cnt % 60);
	int h = (unsigned short)(cnt/60);
	return UnicodeString().sprintf(_T("%02d:%02d:%02d"), h,m,s);
}

//---------------------------------------------------------------------------
//文字列からDMXチャンネルNo.へ(0ベース)
// [A～H]nnn
//---------------------------------------------------------------------------
int str_to_dmxch(
	UnicodeString s,
	int max_ch)			//最大チャンネル	(default = 4096/H512)
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
//DMXチャンネルNo.から文字列へ
//---------------------------------------------------------------------------
UnicodeString dmxch_to_str(
	int  cn,	//絶対チャンネル
	bool un_ch)	//default = true (ユニバース+チャンネル)
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
// 文字列から数値範囲をリストへ取得(Ch.No.は1～)
// エラー時には s にメッセージ(不正な書式です)
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
		s = "エラー: 不正な書式です";
		lst->Clear();
	}

	return lst->Count;
}

//---------------------------------------------------------------------------
// TStringListの値から名前を取得
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
//パラメータのバイト数情報を取得
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
			if (strbuf.IsDelimiter("\"", 1)) {	//先頭が "
				strbuf.Delete(1, 1); tmpbuf = EmptyStr;
				while (1) {
					int qp = strbuf.Pos("\"");
					if (qp) {
						//" 発見
						if (qp<strbuf.Length()) {
							//"～" 内の "
							if (strbuf.IsDelimiter("\"", qp + 1)) {
								tmpbuf += strbuf.SubString(1, qp);
								strbuf	= strbuf.Delete(1, qp + 1);
							}
							//対応する "
							else {
								tmpbuf += strbuf.SubString(1, qp - 1);
								strbuf	= strbuf.Delete(1, qp).Trim();
								if (strbuf.IsDelimiter(",", 1))
									strbuf = strbuf.Delete(1, 1);
								else
									throw EAbort("カンマが必要");
								break;
							}
						}
						//末尾が " (最後の項目)
						else {
							tmpbuf += strbuf.Delete(qp, 1);
							strbuf = EmptyStr; break;
						}
					}
					else {
						//対応する " がない
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
				//最後の項目
				else {
					tmpbuf = strbuf;
					strbuf = EmptyStr;
				}

				int d = tmpbuf.ToIntDef(-1);
				if (d>=0 && d<256)
					cnt ++;
				else if (tmpbuf!="0x")
					throw EAbort("不正な値");
			}
		}

		if (cnt<=lmt)
			infstr.sprintf(_T("%u/%u バイト"), cnt, lmt);
		else
			infstr.sprintf(_T("%u/%u バイト 超過!"), cnt, lmt);

	}
	catch(EAbort &e) {
		infstr.sprintf(_T("\?\?/%u バイト %s"), lmt, e.Message.c_str());
	}

	return infstr;
}
//---------------------------------------------------------------------------
