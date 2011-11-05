//---------------------------------------------------------------------------

#ifndef InterfaceH
#define InterfaceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TCryptWindow : public TForm
{
__published:	// IDE-managed Components
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
	TComboBox *Alg;
	TLabel *Finfo;
	TButton *Button1;
	TButton *Button2;
	TRadioButton *Encrypt;
	TRadioButton *Decrypt;
	TLabel *ActionLabel;
	TButton *Go;
	TLabel *Elapsed;
	TOpenDialog *OD;
	void __fastcall SearchClick(TObject *Sender);
	void __fastcall Pwd1Change(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall PathExit(TObject *Sender);
	void __fastcall PathKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall AlgDropDown(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall GoClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCryptWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCryptWindow *CryptWindow;
//---------------------------------------------------------------------------
#endif
