//---------------------------------------------------------------------------

#ifndef OperationsH
#define OperationsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TOpWindow : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *PB;
	TProgressBar *ProgressBar1;
	TLabel *CurrentOP;
private:	// User declarations
public:		// User declarations
	__fastcall TOpWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOpWindow *OpWindow;
//---------------------------------------------------------------------------
#endif
