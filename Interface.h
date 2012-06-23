// ---------------------------------------------------------------------------

#ifndef InterfaceH
#define InterfaceH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#define OP_TERM (WM_APP+2)

// ---------------------------------------------------------------------------
class TCryptWindow : public TForm {
__published: // IDE-managed Components

	TEdit *Path;
	TSaveDialog *SD;
	TButton *Search;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TEdit *Pwd1;
	TEdit *Pwd2;
	TLabel *EnterP;
	TLabel *ConfirmP;
	TLabel *Ident;
	TLabel *Finfo;
	TRadioButton *Encrypt;
	TRadioButton *Decrypt;
	TButton *Go;
	TOpenDialog *OD;
	TComboBox *activeOps;
	TLabel *Label1;

	void __fastcall SearchClick(TObject *Sender);
	void __fastcall Pwd1Change(TObject *Sender);
	void __fastcall PathExit(TObject *Sender);
	void __fastcall PathKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall GoClick(TObject *Sender);
	void __fastcall PathClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall activeOpsDropDown(TObject *Sender);
	void __fastcall activeOpsCloseUp(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);

private:
	void forkOperation(char* inputFile, char* outputFile, char* pwd, bool mode);
	UnicodeString TCryptWindow::shortGoto(UnicodeString in, UnicodeString out,
		int prg);

	// User declarations
public:
	void __fastcall delEntry(TMessage& msg);
	// User declarations
	__fastcall TCryptWindow(TComponent* Owner);
	BEGIN_MESSAGE_MAP VCL_MESSAGE_HANDLER(OP_TERM, TMessage, delEntry);
	END_MESSAGE_MAP(TForm)
};

// ---------------------------------------------------------------------------
extern PACKAGE TCryptWindow *CryptWindow;
// ---------------------------------------------------------------------------
#endif
