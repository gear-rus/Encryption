#include <vcl.h>

#pragma hdrstop
#include "Credits.h"
#include "Interface.h"
#include "Processing.h"
#include "Operation.h"
#include <time.h>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCryptWindow *CryptWindow;
FILE *input = NULL, *output = NULL;
int size = 0, mode = 0;

void __fastcall TCryptWindow::delEntry(TMessage& msg) {
	for (int i = 1; i < activeOps->Items->Count; i++)
		if (activeOps->Items->Objects[i] == (TOpWindow*)msg.WParam)
			activeOps->Items->Delete(i);
	activeOps->Items->Strings[0] = "Active Operations - " +
		UnicodeString(activeOps->Items->Count - 1);
	activeOps->ItemIndex = 0;
}

UnicodeString TCryptWindow::shortGoto(UnicodeString in, UnicodeString out,
	int prg) {
	char* str1 = AnsiString(in).c_str();
	char* str2 = AnsiString(out).c_str();
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	if ((len1 == 0) || (len2 == 0)) {
		return 0;
	}
	if ((prg > 100) || (prg < 0)) {
		return 0;
	}
	int LEN = 70;
	if ((len1 + len2 + 11) <= LEN) {
		return UnicodeString(str1) + " to " + str2 + " - " + prg + "%";
	}
	int pos1 = 0;
	int l = 0;
	int pos2 = 0;
	for (pos1 = len1; (str1[pos1] != '\\') && (pos1 >= 0); pos1--);
	for (pos2 = len2; (str2[pos2] != '\\') && (pos2 >= 0); pos2--);
	// str11 - before \\ str 12 after \\
	char* str11 = new char[pos1 + 1 + 1];
	char* str12 = new char[len1 - pos1];
	char* str21 = new char[pos2 + 1 + 1];
	char* str22 = new char[len2 - pos2];
	strncpy(str11, str1, pos1 + 1);
	strncpy(str12, str1 + pos1 + 1, len1 - pos1);
	strncpy(str21, str2, pos2 + 1);
	strncpy(str22, str2 + pos2 + 1, len2 - pos2);
	int len11 = strlen(str11);
	int len12 = strlen(str12);
	int len21 = strlen(str21);
	int len22 = strlen(str22);
	// path1 to path2 - int%
	// " to "  +  " - int%"  =11
	// how many free slots we have ?
	int freelen = LEN - (len12 + len22 + 11);
	if (freelen < 0) {
		return UnicodeString("~") + (str12 - freelen / 2 + 1) + " to " + "~" +
			(str22 - freelen / 2 + 1) + " - " + prg + "%";
	}
	if (freelen == 0) {
		return UnicodeString(str12) + " to " + str22 + " - " + prg + "%";
	}
	if (freelen > 0) {

		str11[freelen / 2] = 0;
		str21[freelen / 2] = 0;
		return UnicodeString(str11) + "~" + str12 + " to " + str21 + "~" +
			str22 + " - " + prg + "%";
		return 0;
	}
}

void TCryptWindow::forkOperation(char* inputFile, char* outputFile, char* pwd,
	bool mode) {
	FILE* in = NULL, *out = NULL;
	char* outputstring = new char[strlen(outputFile) + 10];
	if (!mode) {
		in = fopen(inputFile, "rb");
		strcpy(outputstring, AnsiString(AnsiString(outputFile) + ".crypt")
			.c_str());
		out = fopen(outputstring, "wb");
	}
	else {
		in = fopen(inputFile, "rb");
		strcpy(outputstring, AnsiString(AnsiString(GetFilePath(outputFile)) +
			"test").c_str());
		out = fopen(outputstring, "wb");
		// strcpy(outputstring,GetFilePath(outputstring));

	}
	if ((!in) || (!out)) {
		fclose(in);
		fclose(out);
		remove(outputstring);
		throw 1;
		return;
	}
	fseek(in, 0, SEEK_END);
	int size = ftell(in);
	fclose(in);
	fclose(out);
	remove(outputstring);
	TOpWindow* newOp = new TOpWindow(this);
	newOp->size = size;
	newOp->opcode = mode;
	newOp->inputFile = inputFile;
	newOp->outputFile = outputstring;
	newOp->pwd = pwd;
	newOp->mainForm = this->Handle;
	newOp->ipath->Caption = UnicodeString(inputFile);
	if (mode) {
		outputstring = GetFilePath(outputstring);
	}
	newOp->opath->Caption = UnicodeString(outputstring);
	newOp->isize->Caption = UnicodeString(size) + " Bytes";
	newOp->osize->Caption = UnicodeString(0) + " Bytes";
	if (activeOps->Items->Count > 1) {
		newOp->Top += 30*(activeOps->Items->Count - 1);
		newOp->Left += 20*(activeOps->Items->Count - 1);
	}
	activeOps->AddItem(shortGoto(inputFile, outputFile, 0), newOp);
	activeOps->Items->Strings[0] = "Active Operations - " +
		UnicodeString(activeOps->Items->Count - 1);
	activeOps->ItemIndex = 0;
	newOp->Show();
}

// ---------------------------------------------------------------------------
__fastcall TCryptWindow::TCryptWindow(TComponent * Owner) : TForm(Owner) {

}

// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::SearchClick(TObject * Sender) {
	if (OD->Execute()) {
		Path->Text = OD->FileName;
		PathExit(NULL);
	}
	else
		Path->Text = "File name (and path) here...";
}

// ---------------------------------------------------------------------------
void __fastcall TCryptWindow::Pwd1Change(TObject * Sender) {
	if (Pwd1->Text == Pwd2->Text) {
		Ident->Caption = "Passwords are identical";
		Go->Enabled = 1;

	}
	else {
		Ident->Caption = "Passwords do not match";
		Go->Enabled = 0;

	}
	if ((Pwd1->Text.Length() == 0) || (Pwd2->Text.Length() == 0)) {
		Ident->Caption = "";
		Go->Enabled = 0;
	}

}

// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::PathExit(TObject * Sender) {
	input = fopen(AnsiString(Path->Text).c_str(), "rb");
	Pwd1Change(0);
	if (!input) {
		Finfo->Caption = "No file";
		size = 0;
		Go->Enabled = 0;
		return;
	}
	fseek(input, 0, SEEK_END);
	size = ftell(input);
	fseek(input, 0, SEEK_SET);
	fclose(input);
	Finfo->Caption = UnicodeString(size) + " bytes(OK)";
	Finfo->Caption = properSize(size) + " (" + UnicodeString(size) + " Bytes)";

}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::PathKeyPress(TObject * Sender, wchar_t &Key) {
	if (Key == 0xD)
		PathExit(NULL);
}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::GoClick(TObject * Sender) {
	if (Encrypt->Checked)
		mode = 0;
	else
		mode = 1;
	UnicodeString temppath = OD->FileName;
	SD->FileName = "";
	if (mode) {
		SD->FileName = "SELECT FOLDER, Filename will be restored automatically";
	}
	if (SD->Execute()) {

		try {
			forkOperation(AnsiString(Path->Text).c_str(),
				AnsiString(SD->FileName).c_str(),
				AnsiString(Pwd1->Text).c_str(), mode);
		}
		catch (int exception) {
			if (exception == 1) {
				MessageBox(this->Handle,
					L"Error!\nCheck input parameters and try again!", L"Error",
					MB_ICONWARNING);
			}
		}

	}
	SD->FileName = temppath;

}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::PathClick(TObject * Sender) {
	if (Path->Text == "File name (and path) here...") {
		Path->SelectAll();
	}
}

// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::Button1Click(TObject * Sender)

{

	// TOpWindow* newOp = new TOpWindow(this);
	// // newOp->Parent = this;
	// // newOp->ParentWindow = Handle;
	// newOp->Show();
	// newOp->Top += 20;
	// // activeOps->Items->AddObject("aaaa", this);
	// // int aa = 2650, b = 10000;
	// // double lol = (ceil((((double)aa)/b)*1000))/10;
	// // double lolz = 100*((int)(0.5467657 * 1000) / 1000.0) ;
	// // SetForegroundWindow(CryptWindow->Handle);
	// // OpWindow->PopupMode=pmAuto;
	// // OpWindow->PopupParent=Application->MainForm;
	// // TOpWindow* newOp;
	// // Application->CreateForm(__classid(TOpWindow),&newOp) ;
	// // SetWindowPos(CryptWindow->Handle,newOp->Handle,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);
	// // newOp->Parent=newOp;
	// // newOp->Show();
	// // SetFocus();
	// // newOp->progress=10;
}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::FormClose(TObject *Sender, TCloseAction &Action) {
	CreditsForm->Close();
//    RemoveFontResourceEx(
}
// ---------------------------------------------------------------------------;

void __fastcall TCryptWindow::activeOpsDropDown(TObject *Sender)

{
	for (int i = 1; i < activeOps->Items->Count; i++) {
		activeOps->Items->Strings[i] =
			shortGoto(((TOpWindow*)(activeOps->Items->Objects[i]))
			->ipath->Caption, ((TOpWindow*)(activeOps->Items->Objects[i]))
			->opath->Caption, ((TOpWindow*)(activeOps->Items->Objects[i]))
			->getProgress());
	}

}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::activeOpsCloseUp(TObject *Sender)

{
	if (activeOps->ItemIndex) {
		((TOpWindow*)(activeOps->Items->Objects[activeOps->ItemIndex]))
			->BringToFront();
	}
	activeOps->ItemIndex = 0;
}
// ---------------------------------------------------------------------------

void __fastcall TCryptWindow::Label1Click(TObject *Sender)

{
//AddFontResourceEx(
	CreditsForm->ShowModal();
}
// ---------------------------------------------------------------------------9
 

