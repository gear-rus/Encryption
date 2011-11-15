#include "md5.h"
bool md5encrypt(char *in,char* out,int N,byte pwdhash[16],int buf);
int CheckFile(char* filename,char* pwd);

UnicodeString properSize(int size) {
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
		int hash, k = 0;
		short marker = 0, algindex = 1;
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
		fwrite(&algindex, 2, 1, output);
		fwrite(&marker, 2, 1, output);
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
	}//nahooj ety sistemy :D
	else
	CheckFile(in,pwd);

}
void BSum(byte* arr,int n1,byte* keyword,int n2,bool mode)//mode=1 - minus
{
	if (mode) mode=-1;
		else mode=1;
	for(int i=0,j=0;i<n1;i++,j++)
	arr[i]=(256+arr[i]+mode*keyword[j%n2])%256;
}
int CheckFile(char* filename,char* pwd)
{
	MD5 md5;
	char part[3];
	FILE*in=fopen(filename,"rb");
	short marker;
	fread(&marker,1,2,in);//alg
	switch (marker) {
	case 1:                               //md5 alg
	{
	byte filehash[16];
	char* charnfhash;
	byte nfilehash[16];
	byte* memory=new byte[strlen(pwd)*10];
	char* nfname;//new filename
	int len=strlen(pwd);
	pwd=md5.digestString(pwd);//md5hash pwd
	byte pwdhash[16];
	for (int i = 0, j = 0; i < 16; i++) { //pasha's code
				pwdhash[i] =                 //i hope it converts 32 char(pwd) to 16 byte(pwdhash)
					byte((pwdhash[i] + strtol((strncpy(part, pwd + j, 2)),
					NULL, 16)) % 256);
				j = j % 32;
				j += 2;
				i++;
	}            //end pasha's block
	fread(&marker,1,2,in);//length
	fread(filehash,16,1,in);//hash
	fread(nfname,marker-2-2-16,1,in);
	fread(memory,len*10,1,in);
	charnfhash=md5.digestMemory(memory, len*10);
	for (int i = 0, j = 0; i < 16; i++) { //pasha's code
				nfilehash[i] =                 //i hope it converts 32 char(pwd) to 16 byte(pwdhash)
					byte((nfilehash[i] + strtol((strncpy(part, charnfhash + j, 2)),
					NULL, 16)) % 256);
				j = j % 32;
				j += 2;
				i++;
	}            //end pasha's block
	int i;
	for(i=0;(i<16)&&(filehash[i]==nfilehash[i]);i++);
	if (i==16){
	fclose(in);
	for(int i=0,j=0;i<strlen(nfname);i++,j++)
		nfname[i]=(256+nfname[i]-pwdhash[j%16])%256;
	md5encrypt(filename,nfname,marker,pwdhash,1024*1024*5);//5MB
	return 0;
	}
	return 1;
	}
	default:return 0;
		;
	}  //idk why it returns alg :O


}
bool md5encrypt(char *in,char* out,int N,byte pwdhash[16],int buf)
{
	FILE*inf=fopen(in,"rb");
	FILE*outf=fopen(out,"wb");
	byte* buffer=new byte[buf];
	fseek(inf,N,SEEK_SET);//+N byte
	int L;
	while (!feof(inf))
		{
			L=fread(buffer,buf,1,inf);
			for(int i=0,j=0;i<L;i++,j=(j+1)%16)
				buffer[i]=(256+buffer[i]-pwdhash[j])%256;
			fwrite(buffer,L,1,outf);
		}
	fclose(inf);
	fclose(outf);
	return 0;
}
