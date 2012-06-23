// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
// ---------------------------------------------------------------------------

#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>









USEFORM("Operation.cpp", OpWindow);
USEFORM("Interface.cpp", CryptWindow);
USEFORM("Credits.cpp", CreditsForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	try {
		Application->Initialize();
		Application->ShowMainForm = 0;
		// Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Carbon");
		Application->Title = "Encryption";
		Application->CreateForm(__classid(TCreditsForm), &CreditsForm);
		Application->CreateForm(__classid(TCryptWindow), &CryptWindow);
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
// ---------------------------------------------------------------------------
