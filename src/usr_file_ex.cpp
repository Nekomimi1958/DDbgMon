//----------------------------------------------------------------------//
// �t�@�C������ (260�����ȏ�̃p�X�ɑΉ�)								//
//																		//
//----------------------------------------------------------------------//
#ifndef USE_COMMON_PCH
#include <vcl.h>
#include <tchar.h>
#include <winioctl.h>
#include <memory>
#include <System.StrUtils.hpp>
#pragma hdrstop
#endif

#include "usr_str.h"
#include "usr_file_ex.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//260�����ȏ�̃p�X���ɑΉ����邽�߂̃t�@�C�����ϊ�
//  �������󔒂̏ꍇ�ɂ��Ή�
//---------------------------------------------------------------------------
UnicodeString cv_ex_filename(UnicodeString fnam)
{
	if (fnam.Length()>=MAX_PATH || EndsStr(' ', fnam)) {
		if (StartsStr("\\\\", fnam)) fnam.Insert("?\\UNC\\", 3); else fnam.Insert("\\\\?\\", 1);
	}
	return fnam;
}

//---------------------------------------------------------------------------
//���ϐ���ϊ�
//---------------------------------------------------------------------------
UnicodeString cv_env_var(UnicodeString s)
{
	for (;;) {
		if (!ContainsStr(s, "%")) break;
		UnicodeString estr = get_tkn_m(s, '%', '%');
		if (!ContainsText(s, "%" + estr + "%")) break;
		UnicodeString eval = GetEnvironmentVariable(estr);  if (eval.IsEmpty()) break;
		s = ReplaceText(s, "%" + estr + "%", eval);
	}

	return s;
}

//---------------------------------------------------------------------------
//�p�X���ʂ��Ă���ꍇ�A�t�@�C��������p�X�Ɗg���q����菜��
//---------------------------------------------------------------------------
UnicodeString exclude_env_path(UnicodeString fnam)
{
	if (fnam.IsEmpty() || ExtractFileDrive(fnam).IsEmpty()) return fnam;

	UnicodeString fext = get_extension(fnam);
	if (fext.IsEmpty()) return fnam;

	//�g���q���`�F�b�N
	TStringDynArray xlst = split_strings_semicolon(GetEnvironmentVariable("PATHEXT"));
	bool ok = false;
	for (int i=0; i<xlst.Length && !ok; i++) ok = SameText(fext, xlst[i]);

	//�p�X���`�F�b�N
	if (ok) {
		TStringDynArray plst = split_strings_semicolon(GetEnvironmentVariable("PATH"));
		UnicodeString pnam = ExtractFilePath(fnam);
		for (int i=0; i<plst.Length; i++) {
			if (SameText(IncludeTrailingPathDelimiter(plst[i]), pnam)) {
				fnam = ChangeFileExt(ExtractFileName(fnam), EmptyStr);
				break;
			}
		}
	}

	return fnam;
}

//---------------------------------------------------------------------------
//���s�t�@�C���̃f�B���N�g������̑��΃t�@�C�����ɕϊ�
//---------------------------------------------------------------------------
UnicodeString to_relative_name(UnicodeString fnam)
{
	remove_top_text(fnam, ExtractFilePath(Application->ExeName));
	return fnam;
}

//---------------------------------------------------------------------------
//���΃p�X�����΃p�X�ւ̕ϊ�
//  �h���C�u�����w�肳��Ă�����A�ϊ������ɂ��̂܂܃p�X��Ԃ�
//---------------------------------------------------------------------------
UnicodeString rel_to_absdir(
	UnicodeString fnam,		//�ϊ��Ώۃt�@�C����
	UnicodeString rnam)		//��f�B���N�g���� (default = EmptyStr:���s�p�X);
{
	if (fnam.IsEmpty() || !ExtractFileDrive(fnam).IsEmpty()) return fnam;

	if (rnam.IsEmpty()) rnam = ExtractFilePath(Application->ExeName);

	for (;;) {
		if (remove_top_text(fnam, _T(".\\"))) continue;
		if (!remove_top_text(fnam, _T("..\\"))) break;
		rnam = get_parent_path(rnam);
	}

	return contains_PathDlmtr(rnam)? rnam + fnam : EmptyStr;
}

//---------------------------------------------------------------------------
//���[�g��(�h���C�u���܂���UNC�̃R���s���[�^��)���擾
//---------------------------------------------------------------------------
UnicodeString get_root_name(UnicodeString pnam)
{
	UnicodeString rstr = pnam;
	if (remove_top_text(rstr, _T("\\\\")))
		rstr = "\\\\" + get_tkn(rstr, '\\');
	else
		rstr = ExtractFileDrive(rstr);
	return IncludeTrailingPathDelimiter(rstr);
}

//---------------------------------------------------------------------------
//���ۂ̑召�����Ńt�@�C�������擾
//---------------------------------------------------------------------------
UnicodeString get_case_name(UnicodeString fnam)
{
	UnicodeString drv_nam = IncludeTrailingPathDelimiter(ExtractFileDrive(fnam));
	UnicodeString ret_str = drv_nam;
	UnicodeString pnam;
	TStringDynArray plst = split_path(fnam);
	for (int i=0; i<plst.Length-1; i++) {
		pnam += plst[i] + "\\";
		if (USAME_TS(pnam, "\\") || USAME_TS(pnam, "\\\\")) continue;
		UnicodeString sea_str = pnam + plst[i + 1];
		if (SameText(IncludeTrailingPathDelimiter(sea_str), drv_nam)) continue;
		if (sea_str.Length()>=MAX_PATH) sea_str.Insert("\\\\?\\", 1);
		TSearchRec sr;
		if (FindFirst(sea_str, faAnyFile, sr)==0) {
			ret_str += sr.Name;
			if (sr.Attr & faDirectory) ret_str = IncludeTrailingPathDelimiter(ret_str);
			FindClose(sr);
		}
		else {
			//������Ȃ������炻�̂܂ܕԂ�
			ret_str = fnam;
			break;
		}
	}
	return ret_str;
}

//---------------------------------------------------------------------------
//���[�g�f�B���N�g����?
//---------------------------------------------------------------------------
bool is_root_dir(UnicodeString dnam)
{
	if (remove_top_s(dnam, _T("\\\\")))
		return !contains_PathDlmtr(ExcludeTrailingPathDelimiter(get_tkn_r(dnam, '\\')));
	else
		return !contains_PathDlmtr(ExcludeTrailingPathDelimiter(dnam));
}
//---------------------------------------------------------------------------
bool is_root_unc(UnicodeString dnam)
{
	if (remove_top_s(dnam, _T("\\\\")))
		return !contains_PathDlmtr(ExcludeTrailingPathDelimiter(get_tkn_r(dnam, '\\')));
	else
		return false;
}

//---------------------------------------------------------------------------
//�f�B���N�g�������[�g�̏ꍇ�A������ \ ����菜��
//---------------------------------------------------------------------------
UnicodeString exclede_delimiter_if_root(UnicodeString dnam)
{
	if (!dnam.IsEmpty()) {
		dnam = is_root_dir(dnam) ? ExcludeTrailingPathDelimiter(dnam)
								 : IncludeTrailingPathDelimiter(dnam);
	}
	return dnam;
}

//---------------------------------------------------------------------------
//�h���C�u��(�啶���A\�t��)���擾
//---------------------------------------------------------------------------
UnicodeString get_drive_str(UnicodeString dnam)
{
	return IncludeTrailingPathDelimiter(ExtractFileDrive(dnam)).UpperCase();
}

//---------------------------------------------------------------------------
//�h���C�u���L����?
//---------------------------------------------------------------------------
bool drive_exists(UnicodeString drv)
{
	drv = get_tkn(drv, ':');	if (drv.IsEmpty())	 return false;
	int d_n = drv[1] - _T('A');	if (d_n<0 || d_n>25) return false;
	DWORD d_flag = 0x00000001 << d_n;
	DWORD d_bit = ::GetLogicalDrives();	//���p�\�ȃh���C�u���r�b�g�}�X�N�`���Ŏ擾
	return (d_bit & d_flag);
}

//---------------------------------------------------------------------------
//�h���C�u�̎�ނ��擾
//---------------------------------------------------------------------------
UINT get_drive_type(UnicodeString dnam)
{
	return ::GetDriveType(get_drive_str(dnam).c_str());
}

//---------------------------------------------------------------------------
//�{�����[�������擾
//�߂�l �{�����[����
//---------------------------------------------------------------------------
UnicodeString get_volume_info(UnicodeString dnam,
	UnicodeString *fsys)	//[o] �t�@�C���V�X�e��
{
	UnicodeString ret_str;
	_TCHAR vol_nam[MAX_PATH];
	_TCHAR fil_sys[MAX_PATH];
	DWORD VolSerialNo, MaxCompLen, Flags;
	if (::GetVolumeInformation(get_drive_str(dnam).c_str(),
		vol_nam, sizeof(vol_nam), &VolSerialNo, &MaxCompLen, &Flags, fil_sys, sizeof(fil_sys)))
	{
		ret_str = vol_nam;
		if (fsys) *fsys = fil_sys;
	}
	return ret_str;
}

//---------------------------------------------------------------------------
//�N���X�^�T�C�Y���擾
//---------------------------------------------------------------------------
int get_ClusterSize(UnicodeString dnam)
{
	DWORD SecPerCl, BytePerSec, FreeCl, TotalCl;
	if (::GetDiskFreeSpace(get_drive_str(dnam).c_str(), &SecPerCl, &BytePerSec, &FreeCl, &TotalCl))
		return (BytePerSec * SecPerCl);
	else
		return 0;
}

//---------------------------------------------------------------------------
//�t�@�C���̃x�[�X�����擾
//---------------------------------------------------------------------------
UnicodeString get_base_name(UnicodeString fnam)
{
	fnam = ExtractFileName(fnam);
	if (fnam.IsEmpty()) return EmptyStr;
	return StartsStr('.', fnam)? "." + ChangeFileExt(exclude_top(fnam), EmptyStr) : ChangeFileExt(fnam, EmptyStr);
}
//---------------------------------------------------------------------------
//�g���q���擾 (�h�b�g�t�@�C�����l��)
//---------------------------------------------------------------------------
UnicodeString get_extension(UnicodeString fnam)
{
	fnam = ExtractFileName(fnam);
	if (fnam.IsEmpty()) return EmptyStr;
	return ExtractFileExt(StartsStr('.', fnam)? exclude_top(fnam) : fnam);
}
//---------------------------------------------------------------------------
//�t�@�C���Ȃ�g���q���擾
//---------------------------------------------------------------------------
UnicodeString get_extension_if_file(UnicodeString fnam)
{
	return dir_exists(fnam)? EmptyStr : get_extension(fnam);
}

//---------------------------------------------------------------------------
//�g���q�̃`�F�b�N
//---------------------------------------------------------------------------
bool test_FileExt(UnicodeString fext, UnicodeString list)
{
	if (list.IsEmpty() || fext.IsEmpty() || USAME_TS(fext, ".")) return false;
	if (USAME_TS(list, "*") || USAME_TS(list, ".*")) return true;
	if (!StartsStr('.', fext)) fext.Insert(".", 1);
	if (!EndsStr('.', fext))   fext += ".";
	if (!StartsStr('.', list)) list.Insert(".", 1);
	if (!EndsStr('.', list))   list += ".";
	return ContainsText(list, fext);
}
//---------------------------------------------------------------------------
bool test_FileExt(UnicodeString fext, const _TCHAR *list)
{
	return test_FileExt(fext, UnicodeString(list));
}
//---------------------------------------------------------------------------
//�g���q�̃`�F�b�N(�T�C�Y�����Ή�)
//---------------------------------------------------------------------------
bool test_FileExtSize(UnicodeString fext, UnicodeString list, __int64 size)
{
	bool ret = false;
	TStringDynArray xlst = SplitString(list, ".");
	UnicodeString xstr;
	for (int i=0; i<xlst.Length; i++) {
		if (test_FileExt(fext, get_tkn(xlst[i], ":"))) xstr =xlst[i];
	}
	if (!xstr.IsEmpty()) {
		__int64 sz = get_tkn_r(xstr, ":").ToIntDef(0) * 1048576ul;	//MB
		ret = (size>=sz);
	}

	return ret;
}

//---------------------------------------------------------------------------
//�f�B���N�g�����̖����� \\ �� (EmptyStr �̏ꍇ�� EmptyStr ��Ԃ�)
//---------------------------------------------------------------------------
UnicodeString to_path_name(UnicodeString dnam)
{
	return (!dnam.IsEmpty()? IncludeTrailingPathDelimiter(dnam) : EmptyStr);
}

//---------------------------------------------------------------------------
//�f�B���N�g����(������ \\ ����)���擾
//---------------------------------------------------------------------------
UnicodeString get_dir_name(UnicodeString dnam)
{
	return ExtractFileName(ExcludeTrailingPathDelimiter(dnam));
}

//---------------------------------------------------------------------------
//�e�f�B���N�g�����擾
//---------------------------------------------------------------------------
UnicodeString get_parent_path(UnicodeString dnam)
{
	return ExtractFilePath(ExcludeTrailingPathDelimiter(dnam));
}

//---------------------------------------------------------------------------
//�p�X�𕪊�
//---------------------------------------------------------------------------
TStringDynArray split_path(
	UnicodeString pnam,
	UnicodeString dlmt)		//��؂�	(default = "\\")
{
	pnam = ExcludeTrailingPathDelimiter(pnam);
	UnicodeString top_s = remove_top_s(pnam, dlmt + dlmt)? dlmt + dlmt : EmptyStr;

	TStringDynArray ret_array = SplitString(pnam, dlmt);
	if (!top_s.IsEmpty() && ret_array.Length>0) ret_array[0] = top_s + ret_array[0];

	return ret_array;
}

//---------------------------------------------------------------------------
//�R���s���[�^����?
//---------------------------------------------------------------------------
bool is_computer_name(UnicodeString pnam)
{
	if (!remove_top_s(pnam, _T("\\\\"))) return false;
	return (ExcludeTrailingPathDelimiter(pnam).Pos('\\')==0);
}

//---------------------------------------------------------------------------
//�f�B���N�g�����A�N�Z�X�\���H
//---------------------------------------------------------------------------
bool is_dir_accessible(UnicodeString dnam)
{
	if (!is_drive_accessible(dnam)) return false;
	if (is_root_dir(dnam)) return true;

	if (!contains_PathDlmtr(ExcludeTrailingPathDelimiter(dnam))) dnam = to_path_name(dnam);
	if (dnam.IsEmpty()) return false;

	if (dnam.Length()>=248) {
		if (StartsStr("\\\\", dnam)) dnam.Insert("?\\UNC\\", 3); else dnam.Insert("\\\\?\\", 1);
	}
	TSearchRec sr;
	if (FindFirst(dnam + "*.*", faAnyFile, sr)==0) {
		FindClose(sr);
		return true;
	}

	return false;
}

//---------------------------------------------------------------------------
//�h���C�u���A�N�Z�X�\���H
//---------------------------------------------------------------------------
bool is_drive_accessible(UnicodeString dnam)
{
	if (dnam.IsEmpty()) return false;
	UnicodeString dstr = get_drive_str(dnam);
	if (dstr.IsEmpty()) return false;

	UINT old_mode = ::SetErrorMode(SEM_FAILCRITICALERRORS);
	DWORD MaxCompLen, Flags;
	bool res = (::GetVolumeInformation(dstr.c_str(), NULL, 0, NULL, &MaxCompLen, &Flags, NULL, 0)!=0);
	::SetErrorMode(old_mode);

	return res;
}
//---------------------------------------------------------------------------
//�h���C�u�����C�g�v���e�N�g����Ă��邩�H
//---------------------------------------------------------------------------
bool is_drive_protected(UnicodeString dnam)
{
	bool ret = false;
	dnam = "\\\\.\\" + ExtractFileDrive(dnam);
	HANDLE hDevice = ::CreateFile(dnam.c_str(),
		GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (hDevice!=INVALID_HANDLE_VALUE) {
		DWORD dwWritten;
		if (::DeviceIoControl(hDevice, IOCTL_DISK_IS_WRITABLE, NULL, 0, NULL, 0, &dwWritten, NULL)==FALSE &&
			GetLastError()==ERROR_WRITE_PROTECT)
				ret = true;
		::CloseHandle(hDevice);
	}
	return ret;
}

//---------------------------------------------------------------------------
//�t�@�C���̑������擾
//---------------------------------------------------------------------------
int file_GetAttr(UnicodeString fnam)
{
	try {
		return FileGetAttr(cv_ex_filename(fnam));
	}
	catch (...) {
		return faInvalid;
	}
}

//---------------------------------------------------------------------------
//�t�@�C���̑�����ݒ�
//---------------------------------------------------------------------------
bool file_SetAttr(UnicodeString fnam, int attr)
{
	try {
		return (FileSetAttr(cv_ex_filename(fnam).c_str(), attr)==0);
	}
	catch (...) {
		return false;
	}
}
//---------------------------------------------------------------------------
//�f�B���N�g���̑������R�s�[
//�߂�l: false = ���s
//dst_nam �͖������Ƃ݂Ȃ�(�쐬����̏��)
//---------------------------------------------------------------------------
bool dir_CopyAttr(UnicodeString src_nam, UnicodeString dst_nam,
	bool remove_ro)	//�Ǎ���p����������
{
	int attr = file_GetAttr(src_nam);	if (attr==faInvalid) return false;
	if (remove_ro) attr &= ~faReadOnly;
	if ((attr & (faReadOnly|faHidden|faSysFile)) == 0) return true;
	return file_SetAttr(dst_nam, attr);
}

//---------------------------------------------------------------------------
//�t�@�C���̓ǂݏo����p����������
//---------------------------------------------------------------------------
bool set_FileWritable(UnicodeString fnam)
{
	bool ret = true;
	if (file_exists(fnam)) {
		int atr = file_GetAttr(fnam);
		if (atr!=faInvalid && (atr & faReadOnly)) {
			atr &= ~faReadOnly;
			ret = file_SetAttr(fnam, atr);
		}
	}
	return ret;
}

//---------------------------------------------------------------------------
//���p�[�X�|�C���g?
//---------------------------------------------------------------------------
bool is_SymLink(UnicodeString fnam)
{
	fnam = cv_ex_filename(ExcludeTrailingPathDelimiter(fnam));
	DWORD attr = ::GetFileAttributes(fnam.c_str());
	return (attr!=0xffffffff && (attr & FILE_ATTRIBUTE_REPARSE_POINT));
}

//---------------------------------------------------------------------------
//�����N�J�E���g���擾(2�ȏ�Ȃ�n�[�h�����N)
//---------------------------------------------------------------------------
int get_HardLinkCount(UnicodeString fnam)
{
	int cnt = 0;

	HANDLE hFile = ::CreateFile(cv_ex_filename(fnam).c_str(),
		0, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile!=INVALID_HANDLE_VALUE) {
		BY_HANDLE_FILE_INFORMATION fi;
		if (::GetFileInformationByHandle(hFile, &fi)) cnt = fi.nNumberOfLinks;
		::CloseHandle(hFile);
	}

    return cnt;
}


//---------------------------------------------------------------------------
//�t�@�C���̑��݃`�F�b�N
//---------------------------------------------------------------------------
bool file_exists(UnicodeString fnam)
{
	if (fnam.IsEmpty()) return false;
	return (file_GetAttr(fnam) != faInvalid);
}
//---------------------------------------------------------------------------
bool file_exists_x(UnicodeString fnam)
{
	if (fnam.IsEmpty()) return false;
	int attr = file_GetAttr(fnam);

	return (attr!=faInvalid && (attr & faDirectory)==0);
}

//---------------------------------------------------------------------------
//�f�B���N�g���̑��݃`�F�b�N
//---------------------------------------------------------------------------
bool dir_exists(UnicodeString dnam)
{
	if (dnam.IsEmpty()) return false;
	return ::PathIsDirectory(cv_ex_filename(dnam).c_str());
}

//---------------------------------------------------------------------------
//���E���莞�����烍�[�J���� TDateTime ��
//---------------------------------------------------------------------------
TDateTime utc_to_DateTime(FILETIME *utc)
{
	FILETIME f_tm;
	SYSTEMTIME st;
	::FileTimeToLocalFileTime(utc, &f_tm);
	::FileTimeToSystemTime(&f_tm, &st);
	return SystemTimeToDateTime(st);
}

//---------------------------------------------------------------------------
//�t�@�C���̃^�C���X�^���v�� TDateTime �^�Ŏ擾
//---------------------------------------------------------------------------
TDateTime get_file_age(UnicodeString fnam)
{
	TDateTime ft = 0;
	fnam = cv_ex_filename(fnam);
	HANDLE hFile = ::CreateFile(fnam.c_str(),
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (hFile!=INVALID_HANDLE_VALUE) {
		FILETIME c_tm, a_tm, w_tm, f_tm;
		if (::GetFileTime(hFile, &c_tm, &a_tm, &w_tm)) ft = utc_to_DateTime(&w_tm);
		::CloseHandle(hFile);
	}
	else {
		try {
			FileAge(fnam, ft);
		}
		catch (...) {
			ft = 0;
		}
	}

	return ft;
}

//---------------------------------------------------------------------------
//�^�C���X�^���v��ݒ�
//---------------------------------------------------------------------------
bool set_file_age(UnicodeString fnam, TDateTime dt,
	bool force)		//�Ǎ���p�ł������I�ɕύX (default = false)
{
	bool res = false;

	//�Ǎ���p�Ȃ�ꎞ�I�ɉ���
	int atr = file_GetAttr(fnam);
	bool chg_ro = force && atr!=faInvalid && (atr & faReadOnly);
	if (chg_ro && !set_FileWritable(fnam)) chg_ro = false;

	UnicodeString l_fnam = cv_ex_filename(fnam);
	HANDLE hFile = ::CreateFile(l_fnam.c_str(),
		GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (hFile!=INVALID_HANDLE_VALUE) {
		SYSTEMTIME s_tm;
		FILETIME l_tm, f_tm;
		DateTimeToSystemTime(dt, s_tm);
		//�V�X�e������ �� �t�@�C������ �� ���E���莞��
		if (::SystemTimeToFileTime(&s_tm, &l_tm) && ::LocalFileTimeToFileTime(&l_tm, &f_tm)) {
			res = ::SetFileTime(hFile, NULL, NULL, &f_tm);
		}
		::CloseHandle(hFile);
	}

	//���������ɖ߂�
	if (chg_ro) file_SetAttr(fnam, atr);

	return res;
}

//---------------------------------------------------------------------------
//�t�@�C���T�C�Y���擾
//---------------------------------------------------------------------------
__int64 get_file_size(UnicodeString fnam)
{
	__int64 size = 0;
	HANDLE hFile = ::CreateFile(cv_ex_filename(fnam).c_str(),
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile!=INVALID_HANDLE_VALUE) {
		DWORD size_hi;
		DWORD size_lo = ::GetFileSize(hFile, &size_hi);
		size = size_hi;
		size = (size << 32) + size_lo;
		::CloseHandle(hFile);
	}
	return size;
}

//---------------------------------------------------------------------------
//�w��f�B���N�g�������݂��Ȃ��ꍇ�͍쐬
//---------------------------------------------------------------------------
UnicodeString chk_cre_dir(UnicodeString dnam)
{
	if (!dir_exists(dnam)) dnam = create_Dir(dnam)? IncludeTrailingPathDelimiter(dnam) : EmptyStr;
	return dnam;
}

//---------------------------------------------------------------------------
//��f�B���N�g�����H
//---------------------------------------------------------------------------
bool is_EmptyDir(UnicodeString dnam, 
	bool no_file)	//true = �t�@�C�����܂܂�Ă��Ȃ�(�T�C�Y=0) (default = false);
{
	bool e_flag = true;
	dnam = IncludeTrailingPathDelimiter(dnam);
	TSearchRec sr;
	if (FindFirst(cv_ex_filename(dnam + "*"), faAnyFile, sr)==0) {
		do {
			if (ContainsStr("..", sr.Name)) continue;
			if (no_file && (sr.Attr & faDirectory))
				e_flag = is_EmptyDir(dnam + sr.Name, no_file);
			else
				e_flag = false;
		} while(FindNext(sr)==0 && e_flag);
		FindClose(sr);
	}
	return e_flag;
}

//---------------------------------------------------------------------------
//���p�\�ȃh���C�u�̃��X�g���擾
//---------------------------------------------------------------------------
int get_available_drive_list(TStringList *lst)
{
	lst->Clear();
	DWORD d_bit = ::GetLogicalDrives();	//���p�\�ȃh���C�u���r�b�g�}�X�N�`���Ŏ擾
	DWORD d_flag = 0x00000001;
	UINT old_mode = ::SetErrorMode(SEM_FAILCRITICALERRORS);
	for (int d_n=_T('A'); d_n <= _T('Z'); d_n++,d_flag<<=1) {
		if ((d_bit & d_flag)==0) continue;
		UnicodeString drvnam; drvnam.sprintf(_T("%c:\\"), d_n);
		if (is_drive_accessible(drvnam)) lst->Add(drvnam);
	}
	::SetErrorMode(old_mode);
	return lst->Count;
}

//---------------------------------------------------------------------------
//�t�@�C���̑�����������擾
//---------------------------------------------------------------------------
UnicodeString get_file_attr_str(int atr)
{
	UnicodeString atr_str = StringOfChar(_T('_'), 5);
	if (atr!=faInvalid) {
		if (atr & faReadOnly)	atr_str[1] = 'R';
		if (atr & faHidden)		atr_str[2] = 'H';
		if (atr & faSysFile)	atr_str[3] = 'S';
		if (atr & faArchive)	atr_str[4] = 'A';
		if (atr & faCompressed)	atr_str[5] = 'C';
	}
	return atr_str;
}

//---------------------------------------------------------------------------
//�f�B���N�g�����̃}�X�N�ɊY������ŏ��̃t�@�C�����擾
//---------------------------------------------------------------------------
UnicodeString find_FirstFile(
	UnicodeString pnam,	//�f�B���N�g����
	UnicodeString mask,	//�}�X�N
	bool subSW)			//�T�u�f�B���N�g����	 (default = false)
{
	if (!dir_exists(pnam)) return EmptyStr;

	UnicodeString fnam;
	pnam = IncludeTrailingPathDelimiter(pnam);
	UnicodeString mask_u = def_if_empty(mask, _T("*.*"));

	//�t�@�C��������
	TSearchRec sr;
	if (FindFirst(cv_ex_filename(pnam + mask_u), faAnyFile, sr)==0) {
		do {
			if (sr.Attr & faDirectory) continue;
			fnam = pnam + sr.Name;
		} while(fnam.IsEmpty() && FindNext(sr)==0);
		FindClose(sr);
	}
	if (!fnam.IsEmpty()) return fnam;

	//�T�u�f�B���N�g��������
	if (subSW) {
		if (FindFirst(cv_ex_filename(pnam + "*"), faAnyFile, sr)==0) {
			do {
				if ((sr.Attr & faDirectory)==0) continue;
				if (ContainsStr("..", sr.Name)) continue;
				fnam = find_FirstFile(pnam + sr.Name, mask_u, subSW);
			} while(fnam.IsEmpty() && FindNext(sr)==0);
			FindClose(sr);
		}
	}

	return fnam;
}

//---------------------------------------------------------------------------
//�f�B���N�g�����̃}�X�N�ɊY������S�t�@�C�����擾
//---------------------------------------------------------------------------
void get_files(
	UnicodeString pnam,	//�f�B���N�g����
	const _TCHAR *mask,	//�}�X�N
	TStrings *lst,		//���ʊi�[���X�g
	bool subSW)			//�T�u�f�B���N�g����	 (default = false)
{
	if (!dir_exists(pnam)) return;

	pnam = IncludeTrailingPathDelimiter(pnam);

	UnicodeString mask_u = def_if_empty(mask, _T("*.*"));

	//�T�u�f�B���N�g��������
	TSearchRec sr;
	if (subSW) {
		if (FindFirst(cv_ex_filename(pnam + "*"), faAnyFile, sr)==0) {
			do {
				if ((sr.Attr & faDirectory)==0) continue;
				if (ContainsStr("..", sr.Name)) continue;
				get_all_files_ex(pnam + sr.Name, mask_u, lst, subSW);
			} while(FindNext(sr)==0);
			FindClose(sr);
		}
	}

	//�t�@�C��������
	if (FindFirst(cv_ex_filename(pnam + mask_u), faAnyFile, sr)==0) {
		do {
			if (sr.Attr & faDirectory) continue;
			lst->Add(pnam + sr.Name);
		} while(FindNext(sr)==0);
		FindClose(sr);
	}
}

//---------------------------------------------------------------------------
//�f�B���N�g�����̃}�X�N�ɊY������S�t�@�C���̃��X�g��ǉ��擾
//  �߂�l: �t�@�C����(��f�B���N�g���͏���)
//---------------------------------------------------------------------------
int get_all_files_ex(
	UnicodeString pnam,		//�f�B���N�g����
	UnicodeString mask,		//�}�X�N
	TStrings *lst,			//���ʂ��i�[���� TStrings
	bool subSW,				//�T�u�f�B���N�g��������			(default = fals)
	int subn,				//�T�u�f�B���N�g���̊K�w�̐[��		(default = 99)
	UnicodeString skip_dir,	//���ODir�}�X�N(;�ŋ�؂蕡����)	(default = EmptyStr)
	bool inc_hide,			//�B��������						(default = true)
	bool inc_sys)			//�V�X�e��������					(default = true)
{
	int fcnt = 0;
	if (!dir_exists(pnam)) return fcnt;

	pnam = IncludeTrailingPathDelimiter(pnam);
	if (mask.IsEmpty()) mask = "*.*";

	//�T�u�f�B���N�g��������
	TSearchRec sr;
	if (subSW && subn>0) {
		TStringDynArray skip_dir_lst = split_strings_semicolon(skip_dir);
		if (FindFirst(cv_ex_filename(pnam + "*"), faAnyFile, sr)==0) {
			do {
				if ((sr.Attr & faDirectory)==0) continue;
				if (!inc_hide && (sr.Attr & faHidden))  continue;
				if (!inc_sys  && (sr.Attr & faSysFile)) continue;
		
				UnicodeString dnam = sr.Name;
				if (!ContainsStr("..", dnam)) {
					//���O�f�B���N�g���̃`�F�b�N
					bool skip = false;
					for (int i=0; i<skip_dir_lst.Length; i++) {
						UnicodeString snam = skip_dir_lst[i];
						if (str_match(skip_dir_lst[i], dnam)) { skip = true; break; }
					}

					if (!skip) {
						int scnt = get_all_files_ex(pnam + dnam, mask, lst, subSW, subn - 1, skip_dir,
													inc_hide, inc_sys);
						fcnt += scnt;
					}
				}
			} while(FindNext(sr)==0);
			FindClose(sr);
		}
	}

	//�t�@�C��������
	if (FindFirst(cv_ex_filename(pnam + mask), faAnyFile, sr)==0) {
		do {
			if (sr.Attr & faDirectory) continue;
			if (!inc_hide && (sr.Attr & faHidden))  continue;
			if (!inc_sys  && (sr.Attr & faSysFile)) continue;
			lst->Add(pnam + sr.Name);
			fcnt++;
		} while(FindNext(sr)==0);
		FindClose(sr);
	}

	return fcnt;
}

//---------------------------------------------------------------------------
//�f�B���N�g�����̑S�f�B���N�g�����擾
//---------------------------------------------------------------------------
void get_dirs(UnicodeString pnam, TStrings *lst, bool subSW)
{
	if (pnam.IsEmpty() || !dir_exists(pnam)) return;

	pnam = IncludeTrailingPathDelimiter(pnam);
	TSearchRec sr;
	if (FindFirst(cv_ex_filename(pnam + "*"), faAnyFile, sr)==0) {
		do {
			if ((sr.Attr & faDirectory)==0 || ContainsStr("..", sr.Name)) continue;
			lst->Add(pnam + sr.Name);
			if (subSW) get_dirs(pnam + sr.Name, lst, subSW);
		} while(FindNext(sr)==0);
		FindClose(sr);
	}
}

//---------------------------------------------------------------------------
//��̃t�@�C�����쐬
//---------------------------------------------------------------------------
bool create_EmptyFile(UnicodeString fnam)
{
	HANDLE hFile = ::CreateFile(cv_ex_filename(fnam).c_str(),
		GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile==INVALID_HANDLE_VALUE) return false;
	::CloseHandle(hFile);
	return true;
}

//---------------------------------------------------------------------------
//�f�B���N�g���̍쐬
//---------------------------------------------------------------------------
bool create_Dir(UnicodeString dnam)
{
	if (dnam.Length()>=248) {
		if (StartsStr("\\\\", dnam)) dnam.Insert("?\\UNC\\", 3); else dnam.Insert("\\\\?\\", 1);
	}
	return ::CreateDirectory(dnam.c_str(), NULL);
}
//---------------------------------------------------------------------------
//�f�B���N�g���̍쐬(�����K�w��)
//---------------------------------------------------------------------------
bool create_ForceDirs(UnicodeString dnam)
{
	TStringDynArray plst = split_path(dnam);
	UnicodeString rnam = get_root_name(dnam);
	UnicodeString pnam;
	for (int i=0; i<plst.Length; i++) {
		pnam += IncludeTrailingPathDelimiter(plst[i]);
		if (USAME_TS(pnam, "\\") || USAME_TS(pnam, "\\\\") || SameStr(pnam, rnam)) continue;
		if (dir_exists(pnam)) continue;
		if (!create_Dir(pnam)) return false;
	}
	return true;
}

//---------------------------------------------------------------------------
//�f�B���N�g���̍폜
//---------------------------------------------------------------------------
bool delete_Dir(UnicodeString dnam)
{
	return ::RemoveDirectory(cv_ex_filename(dnam).c_str());
}
//---------------------------------------------------------------------------
//�T�u�f�B���N�g�����܂߂��f�B���N�g���̍폜
//---------------------------------------------------------------------------
bool delete_Dirs(UnicodeString pnam)
{
	pnam = to_path_name(pnam);
	if (!dir_exists(pnam)) return false;

	//�T�u�f�B���N�g�����������č폜
	TSearchRec sr;
	if (FindFirst(cv_ex_filename(pnam + "*"), faAnyFile, sr)==0) {
		bool ok = true;
		do {
			if ((sr.Attr & faDirectory)==0 || ContainsStr("..", sr.Name)) continue;
			ok = delete_Dirs(pnam + sr.Name);
		} while(FindNext(sr)==0 && ok);
		FindClose(sr);
	}

	//�f�B���N�g�����폜
	if (!set_FileWritable(pnam)) return false;
	return delete_Dir(pnam);
}

//---------------------------------------------------------------------------
//�t�@�C���̈ړ�
//---------------------------------------------------------------------------
bool move_File(UnicodeString old_nam, UnicodeString new_nam)
{
	return ::MoveFileEx(cv_ex_filename(old_nam).c_str(), cv_ex_filename(new_nam).c_str(),
				MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH);
}
//---------------------------------------------------------------------------
//�t�@�C���̃R�s�[
//---------------------------------------------------------------------------
bool copy_File(UnicodeString src_nam, UnicodeString dst_nam)
{
	return ::CopyFile(cv_ex_filename(src_nam).c_str(), cv_ex_filename(dst_nam).c_str(), FALSE);
}

//---------------------------------------------------------------------------
//�t�@�C�����O�̕ύX
//---------------------------------------------------------------------------
bool rename_File(UnicodeString old_nam, UnicodeString new_nam)
{
	return ::MoveFile(cv_ex_filename(old_nam).c_str(), cv_ex_filename(new_nam).c_str());
}

//---------------------------------------------------------------------------
//�p�X���̕ύX
//---------------------------------------------------------------------------
bool rename_Path(UnicodeString old_nam, UnicodeString new_nam)
{
	if (!SameText(get_root_name(old_nam),  get_root_name(new_nam))) return false;

	TStringDynArray o_plst = split_path(old_nam);
	TStringDynArray n_plst = split_path(new_nam);
	if (o_plst.Length!=n_plst.Length) return false;

	UnicodeString cur_dir = GetCurrentDir();

	bool ok = true;
	UnicodeString o_pnam, n_pnam;
	for (int i=0; i<o_plst.Length && ok; i++) {
		o_pnam += IncludeTrailingPathDelimiter(o_plst[i]);
		n_pnam += IncludeTrailingPathDelimiter(n_plst[i]);
		if (USAME_TS(o_pnam, "\\") || USAME_TS(o_pnam, "\\\\") || USAME_TS(n_pnam, "\\") || USAME_TS(n_pnam, "\\\\")) continue;
		if (!SameText(o_plst[i], n_plst[i])) {
			SetCurrentDir(get_parent_path(o_pnam));
			ok = rename_File(o_pnam, n_pnam);
		}
		o_pnam = n_pnam;
	}

	SetCurrentDir(cur_dir);

	return ok;
}

//---------------------------------------------------------------------------
//�h���b�v�t�@�C���ꗗ���擾
//---------------------------------------------------------------------------
void get_drop_list(TWMDropFiles msg, TStringList *lst,
	UnicodeString x_mask)		//�g���q(;�ŋ�؂��ĕ����w��A���C���h�J�[�h�� default = ".*")
{
	UINT filecount = ::DragQueryFile((HDROP)msg.Drop, 0xFFFFFFFF, NULL, 0);

	if (filecount>0) {
		TStringDynArray x_lst = SplitString(x_mask, ";");
		if (x_lst.Length>0) {
			for (int i=0; i<x_lst.Length; ++i)
				if (!StartsStr(".", x_lst[i])) x_lst[i].Insert(".", 1);

			UnicodeString fnam;
			for(UINT i=0; i<filecount; i++) {
				fnam.SetLength(MAX_PATH);
				int len = ::DragQueryFile((HDROP)msg.Drop, i, fnam.c_str(),fnam.Length());
				fnam.SetLength(len);
				//�f�B���N�g��
				if ((faDirectory & FileGetAttr(fnam)) != 0)
					for (int i=0; i<x_lst.Length; ++i)
						get_files(fnam, ("*" + x_lst[i]).c_str(), lst, true);
				//�t�@�C��
				else if (lst->IndexOf(fnam)==-1)
					for (int i=0; i<x_lst.Length; ++i)
						if (str_match(x_lst[i], ExtractFileExt(fnam))) lst->Add(fnam);
			}
		}
	}
	::DragFinish((HDROP)msg.Drop);
}
//---------------------------------------------------------------------------
