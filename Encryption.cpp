// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//#include <stdio.h>
#include <tchar.h>
// ---------------------------------------------------------------------------
USEFORM("Interface.cpp", CryptWindow);
USEFORM("Operations.cpp", OpWindow);

//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	try {
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TCryptWindow), &CryptWindow);
		Application->CreateForm(__classid(TOpWindow), &OpWindow);
        void* Op = OpWindow;
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
