// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Interface.h"
#include "Processing.h"
#include <time.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define MAX_B 5120
TCryptWindow *CryptWindow;
FILE *input = NULL, *output = NULL;
MD5 md5;
int size = 0, nArgs, mode = 1;
wchar_t** args = CommandLineToArgvW(GetCommandLineW(), &nArgs);
int buffersize = MAX_B;

// ---------------------------------------------------------------------------
__fastcall TCryptWindow::TCryptWindow(TComponent* Owner) : TForm(Owner) {

}

// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::SearchClick(TObject *Sender) {
	if (OD->Execute()) {
		Path->Text = OD->FileName;
		PathExit(NULL);
	}
	else
		Path->Text = "No file selected...";
}

// ---------------------------------------------------------------------------
void __fastcall TCryptWindow::Pwd1Change(TObject *Sender) {
	if (Pwd1->Text == Pwd2->Text) {
		Ident->Caption = "Passwords are identical";
		Go->Enabled = 1;

	}
	else {
		Ident->Caption = "Passwords do not match";
		Go->Enabled = 0;

	}
	if ((Pwd1->Text == "") || (Pwd2->Text == "")) {
		Ident->Caption = "";
	}

}

// ---------------------------------------------------------------------------
void __fastcall TCryptWindow::Button1Click(TObject *Sender) {
	char* filename = "D:\\Program Files\\LOLZ\\pizdec.tmp";
	ShowMessage(UnicodeString(strrchr(filename, '\\') + 1));

}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::PathExit(TObject *Sender) {
	input = fopen(AnsiString(Path->Text).c_str(), "rb");
	if (!input) {
		Finfo->Caption = " No file ";
		size = 0;
		return;
	}
	fseek(input, 0, SEEK_END);
	size = ftell(input);
	fseek(input, 0, SEEK_SET);
	fclose(input);
	Finfo->Caption = UnicodeString(size) + " bytes(OK)";
	Finfo->Caption = properSize(size);

}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::PathKeyPress(TObject *Sender, wchar_t &Key) {
	if (Key == 0xD)
		PathExit(NULL);
}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::AlgDropDown(TObject *Sender) {
	Alg->Perform(CB_SETDROPPEDWIDTH, 110, 0);
}

// ---------------------------------------------------------------------------
void __fastcall TCryptWindow::Button2Click(TObject *Sender) {
	clock_t start = clock();
	md5alg(1024, "D:\MaxNoobMagom.7z", "lolwut", "D:\\1.enc", 1);
}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::GoClick(TObject *Sender) {
	if (!Encrypt->Checked)
		mode = 0;
	else
		mode = 1;
	clock_t start = clock();
	switch (Alg->ItemIndex) {
	case 0:
		md5alg(5*1024*1024, AnsiString(Path->Text).c_str(),
			AnsiString(Pwd2->Text).c_str(),
			AnsiString(Path->Text).c_str(), mode);
		Elapsed->Caption =
			("Time elapsed: " + UnicodeString(((double)clock() - start)
			/ CLOCKS_PER_SEC) + " s");
	default:
		return; ;
	}
}
// ---------------------------------------------------------------------------
