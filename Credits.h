// ---------------------------------------------------------------------------

#ifndef CreditsH
#define CreditsH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TCreditsForm : public TForm {
__published: // IDE-managed Components
	TLabel *header;
	TLabel *dev1;
	TLabel *dev2;
	TLabel *mail1;
	TLabel *Label1;
	TLabel *whenwhere;

	void __fastcall LinkLabel1Click(TObject *Sender);
	void __fastcall mail1Click(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);

private: // User declarations
		public : // User declarations
	__fastcall TCreditsForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TCreditsForm *CreditsForm;
// ---------------------------------------------------------------------------
#endif
