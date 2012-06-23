#include "md5.h"
#include "time.h"
#define BUFF (16*8*1024)
#define UPD_OP (WM_APP+1)

struct feedback {
	void* destination;
	long int progress;
};

UnicodeString properSize(long int size) {
	double size2 = size;
	int k = 0;
	for (; size2 > 1024; size2 = size2 / 1024, k++);
	size2 = double(int(size2 * 100)) / 100;
	switch (k) {
	case 0:
		return (UnicodeString(size2) + " Bytes");
	case 1:
		return (UnicodeString(size2) + " KiB");
	case 2:
		return (UnicodeString(size2) + " MiB");
	case 3:
		return (UnicodeString(size2) + " GiB");
	case 4:
		return (UnicodeString(size2) + " TiB");
	default:
		return (UnicodeString(size2) + " >TiB");
	}

}

struct encParam {
	int length; // длина
	byte* data;
	byte* keyword;
};

byte* KeySum(byte* data, byte* keyword, int len1, int len2) {
	for (int i = 0; i < len1; i++) {
		data[i] = (data[i] + keyword[i % len2]) % 256;
	}
	return data;
}

byte* KeyMinus(byte* data, byte* keyword, int len1, int len2) {
	for (int i = 0; i < len1; i++) {
		data[i] = (256 + data[i] - keyword[i % len2]) % 256;
	}
	return data;
}

DWORD CALLBACK encThr(void* input) {
	encParam* data = (encParam*)input;
	KeySum(data->data, data->keyword, data->length, 16);
	delete data;
	return 0;
}

DWORD CALLBACK decThr(void* input) {
	encParam* data = (encParam*)input;
	KeyMinus(data->data, data->keyword, data->length, 16);
	delete data;
	return 0;
}

byte* hashPass(char* pwd) {
	// algoritm 1:md5
	char* cipher;
	MD5 md5;
	byte* keyword = new byte[16];
	char part[3];
	// keyword =
	cipher = md5.digestString(pwd);
	// 31 - max index md5hash
	for (int i = 0; i < 31; i += 2) {
		keyword[i / 2] = (byte)(strtol((strncpy(part, cipher + i, 2)), NULL,
			16) % 256);
	}
	return keyword;

}

char *GetFileName(char *path) {
	char *filename = strrchr(path, '\\');
	if (filename == NULL)
		filename = path;
	else
		filename++;
	return filename;
}

char *GetFilePath(char *path) {
	char *filename = strrchr(path, '\\');
	if (filename == NULL)
		filename = path;
	else
		filename++;
	filename[0] = 0;
	return path;
}

int encrypt(char* fin, char* fout, char* pwd, feedback* link) {
	FILE* in = fopen(fin, "rb");
	FILE* out = fopen(fout, "wb");
	if (!in) {
		return 1;
	}
	if (!out) {
		return 2;
	}

	byte* passHash = hashPass(pwd);
	byte* buffer = new byte[BUFF];
	char* newfname = GetFileName(fin);
	int lennewfname = strlen(newfname) + 1;
	newfname = KeySum(newfname, passHash, lennewfname, 16);
	fwrite(&lennewfname, 4, 1, out);
	fwrite(newfname, 1, lennewfname, out);
	// HANDLE thr1, thr2, thr3, thr4, thr5, thr6, thr7, thr8;
	HANDLE main[8]; // = {thr1, thr2, thr3, thr4, thr5, thr6, thr7, thr8};
	fseek(in, 0, SEEK_END);
	int size = ftell(in);
	fseek(in, 0, SEEK_SET);
	int cycles = size / (BUFF) + !(!(size % (BUFF)));
	int done = 0;
	int spare = size % BUFF;
	encParam* encData;
	clock_t begin = clock();
	for (int i = 0; i < cycles; i++) {
		done = i;
		int l = 0, L = 0;
		for (int k = 0; k < 8; k++) {
			l = fread(buffer + (BUFF / 8) * k, 1, BUFF / 8, in);
			encData = new encParam;
			encData->length = l;
			encData->data = buffer + (BUFF / 8) * k;
			encData->keyword = passHash;
			main[k] = CreateThread(0, 0, encThr, encData, 0, 0);
			L += l;
		}
		WaitForMultipleObjects(8, main, TRUE, INFINITE);
		fwrite(buffer, 1, L, out);
		if ((((double)clock() - begin) / CLOCKS_PER_SEC > 0.3) ||
			(done == cycles-1)) {
			begin = clock();
			link->progress = ftell(in);
			PostMessage(((HWND)(link->destination)), UPD_OP,
				(unsigned int)link, 0);
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}

int decrypt(char* fin, char* path, char* pwd, feedback* link) {
	FILE* in = fopen(fin, "rb");

	if (!in) {
		return 1;
	}

	byte* passHash = hashPass(pwd);
	byte* buffer = new byte[BUFF];
	int lennewfname;
	fread(&lennewfname, 1, 4, in);
	char* newfname = new char[lennewfname];
	fread(newfname, 1, lennewfname, in);
	newfname = KeyMinus(newfname, passHash, lennewfname, 16);
	char* fout = new char[lennewfname + strlen(path)];
	fout = strcat(path, newfname);
	FILE* out = fopen(fout, "wb");
	if (!out) {
		return 2;
	}
	// HANDLE thr1, thr2, thr3, thr4, thr5, thr6, thr7, thr8;
	HANDLE main[8]; // = {thr1, thr2, thr3, thr4, thr5, thr6, thr7, thr8};
	int pos = ftell(in);
	fseek(in, 0, SEEK_END);
	int size = ftell(in) - pos;
	fseek(in, pos, SEEK_SET);
	int cycles = size / (BUFF) + !(!(size % (BUFF)));
	int done = 0;
	int spare = size % BUFF;
	encParam* encData;
	clock_t begin = clock();
	for (int i = 0; i < cycles; i++) {
		done = i;
		int l = 0, L = 0;
		for (int k = 0; k < 8; k++) {
			l = fread(buffer + (BUFF / 8) * k, 1, BUFF / 8, in);
			encData = new encParam;
			encData->length = l;
			encData->data = buffer + (BUFF / 8) * k;
			encData->keyword = passHash;
			main[k] = CreateThread(0, 0, decThr, encData, 0, 0);
			L += l;
		}
		WaitForMultipleObjects(8, main, TRUE, INFINITE);
		fwrite(buffer, 1, L, out);
		if ((((double)clock() - begin) / CLOCKS_PER_SEC > 0.3) ||
			(done == cycles-1)) {
			begin = clock();
			link->progress = ftell(in);
			PostMessage(((HWND)(link->destination)), UPD_OP,
				(unsigned int)link, 0);
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}

// ---------------------------------------------------------------------------
