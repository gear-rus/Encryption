//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Operations.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpWindow *OpWindow;
//---------------------------------------------------------------------------
__fastcall TOpWindow::TOpWindow(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
