// ---------------------------------------------------------------------------

#include <vcl.h>
//#include <stdio.h>
#pragma hdrstop

#include "Interface.h"
#include "Processing.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define MAX_B 5120
TCryptWindow *CryptWindow;
FILE *input = NULL, *output = NULL;
MD5 md5;
int size = 0, nArgs;
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
		Enc->Enabled = 1;
		Dec->Enabled = 1;
	}
	else {
		Ident->Caption = "Passwords do not match";
		Dec->Enabled = 0;
		Enc->Enabled = 0;
	}
	if ((Pwd1->Text == "") || (Pwd2->Text == "")) {
		Ident->Caption = "";
	}

}

// ---------------------------------------------------------------------------
void __fastcall TCryptWindow::Button1Click(TObject *Sender) {
	/* char* sdf = "dsf hk.enc";
	 ShowMessage(UnicodeString(fileN(*sdf))); */
	// for (int i = 0; i < 10; i++) {
	// byte*	x = new byte[1024 * 1000];
	// memset(x, 1, 1024*1000);
	// }
	// this->OpWindow->ShowModal();
}

// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::PathExit(TObject *Sender) {

	input = fopen(AnsiString(Path->Text).c_str(), "rb");
	if (!input) {
		Finfo->Caption = "No file";
		size = 0;
		return;
	}
	fseek(input, 0, SEEK_END);
	size = ftell(input);
	fseek(input, 0, SEEK_SET);
	fclose(input);
	Finfo->Caption = UnicodeString(size) + " bytes (OK)";
}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::PathKeyPress(TObject *Sender, wchar_t &Key) {
	// ShowMessage(UnicodeString(Key));
	if (Key == 0xD)
		PathExit(NULL);
}
// ---------------------------------------------------------------------------
