// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Processing.h"
#include "Operation.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpWindow *OpWindow;

double TOpWindow::getProgress() {
	return progress;
}

struct encParameters {
	char *fin, *fout, *pwd;
	feedback* link;
	bool opcode;
};

DWORD CALLBACK startOperation(void* input) {
	encParameters* data = (encParameters*)input;
	if (!(data->opcode))
		encrypt(data->fin, data->fout, data->pwd, data->link);
	else
		decrypt(data->fin, GetFilePath(data->fout), data->pwd, data->link);

}

// ---------------------------------------------------------------------------
__fastcall TOpWindow::TOpWindow(TComponent* Owner) : TForm(Owner) {

}

// ---------------------------------------------------------------------------
void __fastcall TOpWindow::cancelOpClick(TObject *Sender) {
	Close();
}
// ---------------------------------------------------------------------------

void __fastcall TOpWindow::FormShow(TObject *Sender) {
	autoclose = 0;
	if (opcode)
		Caption = "Decryption in progress...";
	else
		Caption = "Encryption in progress...";

	encParameters* encData = new encParameters;
	encData->fin = inputFile;
	encData->fout = outputFile;
	encData->pwd = pwd;
	encData->link = new feedback;
	encData->link->destination = this->Handle;
	encData->link->progress = 0;
	encData->opcode = opcode;
	start = clock();
	opThread = CreateThread(0, 0, startOperation, encData, 0, 0);

	//
}

// ---------------------------------------------------------------------------
void __fastcall TOpWindow::FormCreate(TObject *Sender) {
	opThread = 0;
	inputFile = 0;
	outputFile = 0;
	size = 0;
	sofar = 0;
	progress = 0;
	opcode = 0;
	autoclose = 1;
	// mainBar->Max = size;
}

// ---------------------------------------------------------------------------
void __fastcall TOpWindow::barUPD(TMessage& msg) {

	sofar = ((feedback*)msg.WParam)->progress;
	progress = (ceil((((double)sofar) / size) * 1000)) / 10;
	mainBar->Position = progress;
	percentage->Caption = UnicodeString(progress) + "%";
	osize->Caption = UnicodeString(sofar) + " Bytes";
	Elapsed->Caption =
		("Time elapsed: " + UnicodeString(((double)clock() - start)
		/ CLOCKS_PER_SEC) + " s");
	if (sofar == size) {
		cancelOp->Caption = "Close";
		pauseThread->Enabled=0;
		if (autoclose)
			this->Close();
	}

}

// void __fastcall TOpWindow::mainUPD(TMessage& msg) {
//
// PostMessage(((HWND)(msg.WParam)), UPD_ANS, progress, (long)this);
// }

void __fastcall TOpWindow::autoCloseClick(TObject *Sender) {
	autoclose = !autoclose;
}

// ---------------------------------------------------------------------------
void __fastcall TOpWindow::FormClose(TObject *Sender, TCloseAction &Action) {
	TerminateThread(opThread, 0);
	PostMessage(mainForm, OP_TERM, (unsigned int)this, 0);
}

// ---------------------------------------------------------------------------
void __fastcall TOpWindow::pauseThreadClick(TObject *Sender) {
	if (pauseThread->Caption == "Pause") {
		SuspendThread(opThread);
		pauseThread->Caption = "PAUSED";
	}
	else {
		ResumeThread(opThread);
		pauseThread->Caption = "Pause";
	}

}
// ---------------------------------------------------------------------------
