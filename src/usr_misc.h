//----------------------------------------------------------------------//
// ÇªÇÃëºÇÃîƒópä÷êî														//
//----------------------------------------------------------------------//
#ifndef EtcUsrMiscH
#define EtcUsrMiscH

//---------------------------------------------------------------------------
#include <mmsystem.h>

//---------------------------------------------------------------------------
int round_i(double v);

UnicodeString get_WindowText(HWND hWnd);
UnicodeString get_ClassName(HWND hWnd);
bool GetHwndList(UnicodeString wcls, UnicodeString wtit, TList *hlist);
HWND get_window_from_pos();

TRect get_window_rect(HWND hWnd);
void  set_window_pos_ex(HWND hWnd, TRect rc);
void  set_TopMost(TForm *fp, bool enabled = true);

bool play_sound(UnicodeString fnam, unsigned int flag = SND_ASYNC);

void msgbox_ERR( UnicodeString msg, UnicodeString tit = EmptyStr);
void msgbox_WARN(UnicodeString msg, UnicodeString tit = EmptyStr);
void msgbox_OK(  UnicodeString msg, UnicodeString tit = EmptyStr);
bool msgbox_Y_N( UnicodeString msg, UnicodeString tit = EmptyStr);
int  msgbox_Y_N_C(UnicodeString msg, UnicodeString tit = EmptyStr);

bool is_IME_Open(HWND hWnd);
bool is_IME_Typing(HWND hWnd);
bool is_IME_Empty(HWND hWnd);
void CloseIME(HWND hWnd);

bool open_by_editor(UnicodeString fnam, UnicodeString editor, UnicodeString frmt = EmptyStr);

bool load_StrList(UnicodeString fnam, TStringList *list);
bool save_StrList(UnicodeString fnam, TStringList *list);

bool load_Image(UnicodeString fnam, Graphics::TBitmap *o_bmp);

bool execute_ex(UnicodeString cmd, UnicodeString prm = EmptyStr, UnicodeString fld = EmptyStr,
	int nShowCmd = SW_SHOWNORMAL, int wait = 0);

int  get_no_list(UnicodeString &s, TStringList *lst);
int  get_eq_int(UnicodeString src, int def);

bool get_file_name_r(UnicodeString &fnam);
UnicodeString to_filename_r(UnicodeString fnam);

UnicodeString Sec2TimeStr(int cnt);

int str_to_dmxch(UnicodeString s, int max_ch = 4096);
UnicodeString dmxch_to_str(int cn, bool un_ch = true);
int get_dmxch_list(UnicodeString &s, TStringList *lst);

UnicodeString name_of_value(TStringList *lst, UnicodeString value);

UnicodeString get_ByteInfo(UnicodeString strbuf, int lmt);

//---------------------------------------------------------------------------
#endif
