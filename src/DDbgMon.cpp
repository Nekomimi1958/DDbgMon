//----------------------------------------------------------------------//
// Dual Debug Monitor													//
//																		//
//----------------------------------------------------------------------//
USEFORM("Unit1.cpp", DDbgMonFrm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try {
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TDDbgMonFrm), &DDbgMonFrm);
		Application->Run();
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
