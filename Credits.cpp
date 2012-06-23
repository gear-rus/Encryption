// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Interface.h"
#include "Credits.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCreditsForm *CreditsForm;

// ---------------------------------------------------------------------------
__fastcall TCreditsForm::TCreditsForm(TComponent* Owner) : TForm(Owner) {

}
// ---------------------------------------------------------------------------

void __fastcall TCreditsForm::LinkLabel1Click(TObject *Sender) {

	UnicodeString Operation = "open"; // команда
	UnicodeString Command = "iexplore.exe"; // программа
	UnicodeString FileName = "http://anour.ru"; // параметр
	ShellExecute(Handle, Operation.c_str(), Command.c_str(), FileName.c_str(),
		NULL, SW_SHOW);

}
// ---------------------------------------------------------------------------

void __fastcall TCreditsForm::mail1Click(TObject *Sender)
{
ShellExecute(Handle, L"open", L"mailto:gear_rus@cn.ru", 0, 0, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TCreditsForm::Label1Click(TObject *Sender)
{
ShellExecute(Handle, L"open", L"mailto:crazymax101@gmail.com", 0, 0, SW_SHOW);
}
//---------------------------------------------------------------------------

