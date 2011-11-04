#include "md5.h"

char* fileN(char& in) {
	char* buff = new char[strlen(&in)];
	if (!strstr(&in, ".enc"))
		return &in;
	int pos = (int)(strstr(&in, ".enc") - &in);
	strncpy(buff, &in, pos);
	strcpy(&in, buff);
	*(&in + pos) = '\0';
	delete[]buff;
	return &in;
}

int md5alg(int buffsize, char* in, char* pwd, char* out, int mode) {
	MD5 md5;
	if (mode) {
		out = fileN(*out);
		FILE *input, *output;
		if (!(input = fopen(AnsiString(in).c_str(), "r+b")))
			return 1;
		if (!(output = fopen((AnsiString(out) + ".enc").c_str(), "w+b")))
			return 2;
		byte* buffer = new byte[buffsize];
		byte* littlebuff = new byte;
		char* cipher;
		int hash, k = 0, len = 0;
		char part[3];
		int headL = fread(buffer, 1, strlen(pwd) * 10, input);
		delete cipher;
		cipher = md5.digestMemory(buffer, headL);
		for (int i = 0; i < strlen(cipher); i += 2) {
			buffer[i / 2] =
				byte(strtol((strncpy(part, cipher + i, 2)), NULL, 16) % 256);
		}
		fwrite(buffer, strlen(cipher) / 2, 1, output);
		cipher = md5.digestString(pwd);
		delete buffer, littlebuff, cipher;
		fclose(output);
		fclose(input);
		return 0;
	}

	/*
	 out = fileN(*out);
	 FILE *input, *output;
	 if (!(input = fopen(AnsiString(in).c_str(), "r+b")))
	 return 1;
	 if (!(output = fopen((AnsiString(out)+".enc").c_str(), "w+b")))
	 return 2;

	 byte* buffer = new byte[MAX_B];
	 byte* littlebuff = new byte;
	 char* cipher;
	 int hash, k = 0, len = 0;
	 char part[3];
	 int headL = fread(buffer, 1, strlen(pwd) * 10, input);
	 cipher = md5.digestMemory(buffer, headL);
	 // int a = MAX_B  ;
	 for (int i = 0; i < strlen(cipher); i += 2) {
	/*	stringstream convert(strncpy(part, cipher + i, 2));
	 convert >> std::hex >> hash;
	 buffer[i / 2] = byte(hash % 256);
	 //	= *littlebuff;
	 buffer[i/2]=byte(strtol((strncpy(part, cipher + i, 2)),NULL, 16)%256);
	 }
	 fwrite(buffer,strlen(cipher)/2,1,output);
	 cipher = md5.digestString(pwd);

	/*	while (!feof(input)) {
	 if (k >= StrLen(cipher))
	 k = 0;
	 fread(buff, 1, 1, input);
	 stringstream convert(strncpy(part, cipher + k, 2));
	 convert >> std::hex >> hash;
	 *buff = byte((*buff + hash) % 256);
	 fwrite(buff, 1, 1, output);

	 k += 2;

	 return 0;
	 }
	 fclose(output);
	 fclose(input);
	 */

}
