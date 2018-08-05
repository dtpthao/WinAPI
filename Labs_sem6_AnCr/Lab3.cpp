#include <iostream>
#include <Windows.h>
#include <wincrypt.h>
#include <iomanip>
//#include <string.h>
#include <stdio.h>
//#include <tchar.h>
//#include <conio.h>
using namespace std;
//#pragma comment (lib, "advapi32")

HCRYPTPROV hProv = NULL;
HCRYPTKEY hSessKey = NULL;
HCRYPTKEY hXchgKey = NULL;
HCRYPTKEY hSignKey = NULL;

PROV_ENUMALGS_EX bDataXchg;	
PROV_ENUMALGS_EX bDataSign;
PROV_ENUMALGS_EX bDataSess;

BOOL Get_hProv();
BOOL GetProvParam();
DWORD GetSessKeyParam(DWORD Param, PBYTE pbData);
BOOL GenKey(ALG_ID Algid, DWORD dwSize, HCRYPTKEY &hKey, char *s);
BOOL ExportKey(LPTSTR);
BOOL ImportKey(HCRYPTKEY &hKey, LPTSTR szImportKey);

void GenAllKey()
{
	//BYTE bData;
	DWORD cbData = 1000;
	PBYTE DataBlob = new BYTE[1000];

	////_________GenExchangeKey_______________________
	printf("Gen Exchange Key: \n");
	GenKey(bDataXchg.aiAlgid, bDataXchg.dwMaxLen >> 4, hXchgKey, "Exchange");
	cout << endl;

	/////_________GenSessionKey__________________
	printf("Gen Session Key: \n");
	if (GenKey(bDataSess.aiAlgid, 0, hSessKey, "Session")) {
		cout << endl;
		DWORD LenBlock;
		printf("  LenBlock: ");
		if (GetSessKeyParam(KP_BLOCKLEN, (PBYTE)&LenBlock))
			printf("%d bits\n", LenBlock);

		////_________GenRamdomData__________________
		BYTE pbDataRandom[100];
		if (!CryptGenRandom(hProv, LenBlock >> 3, pbDataRandom))
			printf("Error! - CryptGenRandom.\n");
		printf("  %d bytes of random data have been generated.\n", LenBlock >> 3);

		////__________Set_IV__________________________
		if (!CryptSetKeyParam(hSessKey, KP_IV, pbDataRandom, 0))
			printf("  Error setting initialization vector!\n");
		const DWORD dwMode = CRYPT_MODE_CFB;
		if (!CryptSetKeyParam(hSessKey, KP_MODE, (PBYTE)&dwMode, 0)) {
			printf("  Error setting cipher mode!\n\n");
		}
		printf("  The cipher mode of Session key is set to CFB.\n\n");
	}
}

//BOOL ReadData(char *Src, PBYTE pbData, DWORD &dwCount)
//{
//	FILE *fin = fopen(Src, "rb");
//	if (!fin) {
//		printf("Error opening source plaintext file!\n");
//		return 0;
//	}
//	fseek(fin, 0, SEEK_END);
//	dwCount = ftell(fin);
//	fseek(fin, 0, SEEK_SET);
//	//pbBuf = new BYTE[dwCount];
//	
//	if (fread(pbData, sizeof(byte), dwCount, fin) < dwCount)
//		printf("Error reading plaintext!\n");
//	fclose(fin);
//	//strcpy((char*)pbData, (char*)pbBuf);
//	return 1;
//}

int Encrypt(HCRYPTKEY hKey, char *Src, char*Dst)
{
	DWORD dwBuflen;
	DWORD dwBlocklen;
	PBYTE pbData;
	DWORD dwCount;
	DWORD LenBlock = 0;
	DWORD cbData = 1000;
	FILE *fin = fopen(Src, "rb");
	FILE *fout = fopen(Dst, "wb");
	if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (PBYTE)&LenBlock, &cbData, 0)) {
		printf("Error geting len block.\n\n");
	}
	LenBlock >>= 3;
	pbData = new BYTE[LenBlock*5];
	dwBuflen = LenBlock * 6;
	dwBlocklen = dwBuflen - LenBlock;
	if (!fin) {
		printf("Error opening source plaintext file!\n");
		return 0;
	}
	if (!fout) {
		printf("Error opening destination file!\n");
		return 0;
	}
	//cout << "Plaintext: ";
	
	bool eof = FALSE;
	do {
		dwCount = fread(pbData, sizeof(byte), dwBlocklen, fin);
		//for (int i = 0; i < dwCount; i++) cout << pbData[i];cout << endl;
		if (feof(fin)) eof = TRUE;
		if (!CryptEncrypt(hKey, NULL, eof, 0, pbData, &dwCount, dwBuflen)) {
			printf("Error during CryptEncrypt.\n");
			return 0;
		}
		/*cout << "Ciphertext: ";
		for (int i = 0; i < dwCount; i++) cout << pbData[i];cout << endl;*/

		if (fwrite(pbData, sizeof(byte), dwCount, fout) < 16)
			printf("Error writing ciphertext to file.\n");
	} while (!eof);
	printf("Encrypt successfully.\n");
	fclose(fin);
	fclose(fout);
	return 1;
}

int Decrypt(HCRYPTKEY hKey, char *Src, char*Dst)
{
	DWORD dwBlocklen;
	PBYTE pbData;
	DWORD dwCount;
	DWORD LenBlock = 0;
	DWORD cbData = 1000;
	DWORD dwFileLen;
	FILE *fin = fopen(Src, "rb");
	FILE *fout = fopen(Dst, "wb");
	if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (PBYTE)&LenBlock, &cbData, 0)) {
		printf("Error geting len block.\n\n");
	}
	LenBlock >>= 3;
	//dwBuflen = LenBlock * 6;
	dwBlocklen = LenBlock * 5;
	pbData = new BYTE[dwBlocklen];
	
	if (!fin) {
		printf("Error opening source plaintext file!\n");
		return 0;
	}
	if (!fout) {
		printf("Error opening destination file!\n");
		return 0;
	}
	fseek(fin, 0, SEEK_END); 	// ставим указатель в конец файла
	dwFileLen = ftell(fin);
	rewind(fin);
	bool eof = FALSE;
	do {
		dwCount = fread(pbData, sizeof(byte), dwBlocklen, fin);
		dwFileLen -= dwCount;
		//for (int i = 0; i < dwCount; i++) cout << pbData[i]; cout << endl;
		if (!dwFileLen) eof = TRUE;
		if (!CryptDecrypt(hKey, NULL, eof, 0, pbData, &dwCount)) {
			printf("Error during CryptDecrypt.\n");
			//cout << hex << GetLastError() << endl;
			if (GetLastError() == NTE_BAD_DATA) printf("Bad Data!\n");
			return 0;
		}
		//cout << "Ciphertext: ";
		//for (int i = 0; i < dwCount; i++) cout << pbData[i]; cout << endl;

		if (fwrite(pbData, sizeof(byte), dwCount, fout) < dwCount)
			printf("Error writing ciphertext to file.\n");
		//}
		//else eof = TRUE;
	} while (dwFileLen);
	printf("Decrypt successfully.\n");
	fclose(fin);
	fclose(fout);
	return 1;
}


BOOL ReleaseALL()
{
	if (hXchgKey) CryptDestroyKey(hXchgKey);
	if (hSignKey) CryptDestroyKey(hSignKey);
	if (hSessKey) CryptDestroyKey(hSessKey);
	if (GetLastError()) return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	//int test[7] = { 0,2,7,8,9,14,16 };
	////string test[7] = { "0byte.txt", "2byte.txt","7byte.txt","8byte.txt","9byte.txt","14byte.txt","16byte.txt" };
	//char **ftest = new char*[7];
	//char **ftest2 = new char*[7];
	//for (int i = 0; i < 7; i++) {
	//	ftest[i] = new char[20];
	//	ftest2[i] = new char[20];
	//}
	//strcpy(ftest[0], "0byte.txt");		
	//strcpy(ftest[1], "2byte.txt");
	//strcpy(ftest[2], "7byte.txt");
	//strcpy(ftest[3], "8byte.txt");
	//strcpy(ftest[4], "9byte.txt");
	//strcpy(ftest[5], "14byte.txt");
	//strcpy(ftest[6], "16byte.txt");
	//strcpy(ftest2[0], "0byte2.txt");
	//strcpy(ftest2[1], "2byte2.txt");
	//strcpy(ftest2[2], "7byte2.txt");
	//strcpy(ftest2[3], "8byte2.txt");
	//strcpy(ftest2[4], "9byte2.txt");
	//strcpy(ftest2[5], "14byte2.txt");
	//strcpy(ftest2[6], "16byte2.txt");
	////FILE *Ftest; `1
	//if (argc > 4)
	if (argc < 5) return 1;
	LPTSTR pszKey = argv[2]; //"Key.txt";// argv[2];
	LPTSTR pszPlaintext = argv[3]; //"otchot4.docx";//argv[3];
	LPTSTR pszCiphertext = argv[4]; //"Ciphertext.txt";//agrv[4];
	LPTSTR pszDecrypt = argv[5]; //"Decrypt.txt";// argv[5];

	if (!Get_hProv()) return 1;
	if (!GetProvParam()) return ReleaseALL();
	GenAllKey();
	printf("_________Export Session Key________________\n");
	ExportKey(pszKey);
	printf("_________Import Key_________________________\n");
	HCRYPTKEY hKey;
	ImportKey(hKey, pszKey);
	
	/*for (int i = 0; i < 7; i++) {
		printf("%d byte: \n", test[i]);
		printf("_______Encrypt_____________________\n");
		Encrypt(hKey, ftest[i], ftest2[i]);
		cout << endl;
		printf("_______Decrypt_____________________\n");
		Decrypt(hKey, ftest2[i], "Decrypt.txt");
		cout << endl;
	}*/

	
	printf("_______Encrypt_____________________\n");
	Encrypt(hKey, pszPlaintext, pszCiphertext);
	cout << endl;
	printf("_______Decrypt_____________________\n");
	Decrypt(hKey, pszCiphertext, pszDecrypt);
	cout << endl;
	

	CryptDestroyKey(hKey);
	ReleaseALL();
	system("pause");
	return 0;
}

BOOL Get_hProv()
{
	LPCTSTR pszContainer = "ContainerLab_ENHANCED";
	if (CryptAcquireContext(&hProv, pszContainer, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0)) {
		printf("The key container %s has been acquired.\n\n", pszContainer);
	}
	else {
		if (GetLastError() != NTE_BAD_KEYSET) {
			printf("ERROR creating new key container.\n");
			return 0;
		}
		if (!CryptAcquireContext(&hProv, pszContainer, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_NEWKEYSET)) {
			printf("ERROR acquiring a cryptographic context.\n");
			return 0;
		}
		printf("A new key container \"%s\" has been created.\n\n", pszContainer);
	}
	return 1;
}

BOOL GetProvParam()
{
	PROV_ENUMALGS_EX EnumData;
	DWORD cbData = 1000;
	DWORD dwFlag = CRYPT_FIRST;
	while (CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&EnumData, &cbData, dwFlag))
	{
		switch (EnumData.aiAlgid)
		{
		case CALG_RSA_KEYX:
			bDataXchg = EnumData;
			break;

		case CALG_AES_128:
			bDataSess = EnumData;
			break;
		}
		dwFlag = CRYPT_NEXT;
	}
	if (dwFlag == CRYPT_FIRST) {
		printf("Error reading PP_ENUMALGS_EX.\n\n");
		return 0;
	}
	return 1;
}

BOOL GenKey(ALG_ID Algid, DWORD dwSize, HCRYPTKEY &hKey, char *s)
{
	DWORD dwFlags;
	//cout << "  Len Key: " << dwSize << endl;
	dwFlags = (dwSize << 16) | CRYPT_EXPORTABLE;
	if (!CryptGenKey(hProv, Algid, dwFlags, &hKey))
	{
		printf("  GenKey Failed!\n\n");
		return 0;
	}
	else printf("  A %s Key of %d bits length is created.\n", s, dwSize);
	return 1;
}

DWORD GetSessKeyParam(DWORD Param, PBYTE pbData)
{
	DWORD cbData = 1000;
	if (!CryptGetKeyParam(hSessKey, Param, pbData, &cbData, 0)) {
		printf("Error geting parameter.\n\n");
		return 0;
	}
	return cbData;
}

void subwrite(void* buf, int size, int count, FILE *F)
{
	cout << ((size*count) << 2);
	if (fwrite(buf, size, count, F)) {
		cout << " bits was written to file." << endl;
	}
	else
		cout << " bits can not be written to file." << endl;
}

void WriteBlobToFile(BYTE *pbData, DWORD cbData, char *FileName)
{
	//char szFileName[] = "Key.txt";
	DWORD dwMode, lenIV;
	BYTE DataIV[100];
	FILE *F;// = fopen(szFileName, "wb");
	if ((F = fopen(FileName, "wb"))) {
		printf("The file '%s' was opened for writing.\n", FileName);
	}
	else printf("Can not open the file.\n");

	////___Len Key Blob____
	cout << left << setw(19) << "  Len Key Blob: ";
	subwrite(&cbData, sizeof(DWORD), 1, F);

	////___Key Blob_____
	cout << left << setw(19) << "  Key Blob: ";
	subwrite(pbData, sizeof(BYTE), cbData, F);

	////___mode____
	GetSessKeyParam(KP_MODE, (PBYTE)&dwMode); //cout << "\tmode: " << mode << endl;
	cout << left << setw(16) << "  Cipher mode = " << dwMode << ": ";
	subwrite(&dwMode, sizeof(DWORD), 1, F);

	////___Vector IV____
	lenIV = GetSessKeyParam(KP_IV, DataIV);
	cout << left << setw(17) << "  Len IV = " << lenIV << ": ";
	subwrite(&lenIV, sizeof(DWORD), 1, F);  //cout << "\tlenIV: " << lenIV << endl;
	cout << left << setw(17) << "  Vector IV: ";
	subwrite(DataIV, sizeof(BYTE), lenIV, F);

	if (!fclose(F)) printf("File \"%s\" is closed.\n", FileName);
}

BOOL ExportKey(char *FileName)
{
	DWORD cbData = 1000;
	PBYTE DataBlob;// = new BYTE[1000];
	//DWORD LenData = 1000;
	if (!CryptExportKey(hSessKey, hXchgKey, SIMPLEBLOB, CRYPT_OAEP, 0, &cbData))
	{
		cout << "Error getting key Blob length!\n\n" << endl;
		return 0;
	}
	DataBlob = new BYTE[cbData];
	if (!CryptExportKey(hSessKey, hXchgKey, SIMPLEBLOB, CRYPT_OAEP, DataBlob, &cbData))
	{
		cout << "Error exporting Key Blob!\n\n" << endl;
		return 0;
	}
	printf("Exporting Key Blob successfully.\n");
	WriteBlobToFile(DataBlob, cbData, FileName);
	cout << endl;
	return 1;
}

//void SubReadKey(FILE *F, PBYTE pbBuf, DWORD size, DWORD count)
//{
//	if (fread(pbBuf, size, 1, F)) {
//		printf("  Len Key: %d bytes\n", cbData);
//	}
//	else {
//		printf("  Error reading len Key Blob.\n");
//		return 0;
//	}
//}

BOOL ReadBlobFile(LPTSTR szFileName, BYTE *pbData, DWORD &cbData, PBYTE DataIV, DWORD &dwMode)
{
	//char szFileName[] = "Key.txt";
	DWORD lenIV;
	FILE *F = fopen(szFileName, "rb");
	if (!F) {
		printf("Can not open the file\n");
		return 0;
	}
	printf("The file '%s' is open for reading.\n", szFileName);

	if (fread(&cbData, sizeof(DWORD), 1, F)) {
		printf("  Len Key: %d bytes\n", cbData);
	}
	else {
		printf("  Error reading len Key Blob.\n");
		return 0;
	}
	if (fread(pbData, sizeof(BYTE), cbData, F)) {
		printf("  %d bytes were written to the key.\n", cbData);
	}
	else printf("  Error reading key Blob.\n");

	if (fread(&dwMode, sizeof(DWORD), 1, F)) {
		printf("  Mode: %d.\n", dwMode);
	}
	else printf("  Error reading cipher mode.\n");

	if (fread(&lenIV, sizeof(DWORD), 1, F)) {
		printf("  Len IV: %d.\n", lenIV);
	}
	else printf("  Error reading lenIV.\n");

	if (fread(DataIV, sizeof(BYTE), lenIV, F)) {
		printf("  %d bits were written to the vector IV.\n", lenIV << 2);
	}
	else {
		printf("  Error reading vector IV.\n");
		return 0;
	}

	if (!fclose(F)) printf("The file \"%s\" is closed.\n", szFileName);
	return 1;
}

BOOL ImportKey(HCRYPTKEY &hKey, LPTSTR szImportKey)//PBYTE DataBlob, DWORD LenData)
{
	BYTE *pbData = new BYTE[1000];
	DWORD cbData = 1000;
	DWORD dwMode;
	BYTE DataIV[1000];
	//HCRYPTKEY hKey;

	if (!ReadBlobFile(szImportKey, pbData, cbData, DataIV, dwMode)) return 0;
	if (!CryptImportKey(hProv, pbData, cbData, hXchgKey, CRYPT_OAEP, &hKey))
	{
		printf("Error importing key Blob!\n\n");
		return 0;
	}
	else printf("Importing Key Blob successfully.\n");

	////__________Set_IV__________________________
	if (!CryptSetKeyParam(hKey, KP_IV, DataIV, 0))
		printf("Error setting initialization vector!\n");
	else printf("Setting IV successfully\n");
	//const DWORD mode = dwMode; cout << dwMode << endl;
	if (!CryptSetKeyParam(hKey, KP_MODE, (PBYTE)&dwMode, 0)) {
		printf("Error setting cipher mode!\n\n");
	}
	else printf("The cipher mode of the key is set to %d.\n\n", dwMode);
	return 1;
}
