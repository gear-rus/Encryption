// ---------------------------------------------------------------------------

#ifndef OperationH
#define OperationH
// ---------------------------------------------------------------------------
#include <time.h>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#define UPD_OP (WM_APP+1)
#define OP_TERM (WM_APP+2)

// ---------------------------------------------------------------------------
class TOpWindow : public TForm {
__published: // IDE-managed Components

	TProgressBar *mainBar;
	TLabel *i;
	TCheckBox *autoClose;
	TButton *cancelOp;
	TLabel *o;
	TLabel *ipath;
	TLabel *opath;
	TLabel *percentage;
	TLabel *isize;
	TLabel *osize;
	TLabel *Elapsed;
	TButton *pauseThread;

	void __fastcall cancelOpClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall autoCloseClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall pauseThreadClick(TObject *Sender);

private: // User declarations
		public :

	HWND mainForm;
	TOpWindow *OpWindow;
	HANDLE opThread;
	char *inputFile, *outputFile, *pwd;
	int size, sofar;
	double progress;
	bool opcode, autoclose;
	clock_t start;

	// User declarations
	double getProgress();
	void __fastcall barUPD(TMessage& msg);
	__fastcall TOpWindow(TComponent* Owner);
	BEGIN_MESSAGE_MAP VCL_MESSAGE_HANDLER(UPD_OP, TMessage, barUPD);
	END_MESSAGE_MAP(TForm)
};

// ---------------------------------------------------------------------------
extern PACKAGE TOpWindow *OpWindow;
// ---------------------------------------------------------------------------
#endif
