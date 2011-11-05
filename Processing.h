#include "md5.h"

UnicodeString properSize(int size) {
	UnicodeString out = "";
	int cur;
	if (cur = size / (1024 * 1024 * 1024)) {
		out = out + cur + "," + (size / (1024 * 1024)) + " GB";
		return out;
	}
	if (cur = size / (1024 * 1024)) {
		out = out + cur + "," + (size / 1024) + " MB";
		return out;
	}
	if (cur = size / (1024)) {
		out = out + cur + "," + (size % 1024) + " Bytes";
		return out;
	}

}

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
		char* cipher;
		int hash, k = 0, marker = 0;
		char part[3];
		int readL = fread(buffer, 1, strlen(pwd) * 10, input);
		cipher = md5.digestMemory(buffer, readL);
		for (int i = 0; i < strlen(cipher); i += 2) {
			buffer[i / 2] =
				byte(strtol((strncpy(part, cipher + i, 2)), NULL, 16) % 256);
			marker++;
		}
		cipher = md5.digestString(pwd);
		k = strlen(strrchr(in, '\\') + 1);
		byte* namebuff = new byte[k];
		strcpy(namebuff, strrchr(in, '\\') + 1);
		for (int i = 0, j = 0; i < k;) {
			namebuff[i] =
				byte((strtol((strncpy(part, cipher + j, 2)), NULL,
				16) + namebuff[i]) % 256);
			marker++;
			j = j % 32;
			j += 2;
			i++;
		}
		marker += 4;
		fwrite(&marker, 4, 1, output);
		fwrite(buffer, strlen(cipher) / 2, 1, output);
		fwrite(namebuff, k, 1, output);
		fseek(input, 0, SEEK_SET);
		while (!feof(input)) {
			readL = fread(buffer, 1, buffsize, input);
			for (int i = 0, j = 0; i < readL; i++) {
				buffer[i] =
					byte((buffer[i] + strtol((strncpy(part, cipher + j, 2)),
					NULL, 16)) % 256);
				j = j % 32;
				j += 2;
				i++;
			}
			fwrite(buffer, 1, readL, output);
		}
		fclose(output);
		return 0;
	}

}
