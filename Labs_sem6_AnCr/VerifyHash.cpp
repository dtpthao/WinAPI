////--------------------------------------------------------------------
//// Copyright (C) Microsoft.  All rights reserved.
//// Example of signing a hash and 
//// verifying the hash signature.
////#pragma comment(lib, "crypt32.lib")
//
//#include <stdio.h>
//#include <windows.h>
//#include <Wincrypt.h>
////#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
//void MyHandleError(char *s);
//
//void GethProv(HCRYPTPROV &hProv)
//{
//	LPTSTR pszContainer = "ContainerLab_2_1";
//	if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_AES, 0)) {
//		printf("The key container %s has been acquired.\n\n", pszContainer);
//	}
//	else {
//		if (GetLastError() != NTE_BAD_KEYSET) {
//			printf("ERROR creating new key container.\n");
//		}
//		if (!CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_AES, CRYPT_NEWKEYSET)) {
//			printf("ERROR acquiring a cryptographic context.\n");
//		}
//		printf("A new key container \"%s\" has been created.\n\n", pszContainer);
//	}
//}
//
//void GenPrivateKey(HCRYPTPROV hProv, HCRYPTKEY &hSessKey)//, HCRYPTKEY &hXchgKey)
//{
//	PROV_ENUMALGS_EX DataSess;
//	DWORD cbData = 1000;
//	
//	CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&DataSess, &cbData, CRYPT_FIRST);
//	while (DataSess.aiAlgid == CALG_AES_128) 
//	{
//		CryptGetProvParam(hProv, PP_ENUMALGS_EX,
//			(BYTE*)&DataSess, &cbData, CRYPT_NEXT);
//	}
//
//	if (!CryptGenKey(hProv, DataSess.aiAlgid, CRYPT_EXPORTABLE, &hSessKey)) {
//		printf("  GenKey Failed!\n\n");
//	}
//	else printf("  A Sess Key of defalt bits length is created.\n");
//}
//
//
//int GetHash(HCRYPTPROV hProv, HCRYPTHASH &hHash, HCRYPTKEY hSessKey, char *FileName)
//	//BYTE *pbBuffer, DWORD &dwBufferLen)
//{
//	BYTE *pbBuffer = new BYTE[1024]; 
//	DWORD dwBufferLen;
//	if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
//		printf("Hash object created. \n");
//	}
//	else {
//		printf("Error during CryptCreateHash.");
//	}
//
//	FILE *fin = fopen(FileName, "wb");
//	if (!fin) {
//		printf("Error reading %s!\n", FileName);
//		return 0;
//	}
//	
//	while (feof(fin)) {
//		dwBufferLen = fread(pbBuffer, sizeof(BYTE), 1024, fin);
//		if (dwBufferLen < 1024 && (!feof(fin)))
//			printf("Error reading file Data.txt\n");
//		if (!CryptHashData(hHash, pbBuffer, dwBufferLen, 0))
//			printf("Error during CryptHashData.\n");
//		else printf("The data has been added to the hash.\n\n");
//
//		if (CryptHashSessionKey(hHash, hSessKey, 0)) {
//			printf("The session key has been hashed. \n");
//		}
//	}
//	fclose(fin);
//}
//
//int ReadFile(char *filename, PBYTE &pbData, DWORD &cbData)
//{
//	FILE *fin;
//	if (!(fin = fopen(filename, "rb"))) {
//		printf("Error writing Signature to file.\n");
//		return 0;
//	}
//	if (!fread(&cbData, sizeof(DWORD), 1, fin)) {
//		printf("Error reading file!\n");
//		return 0;
//	}
//	pbData = new BYTE[cbData];
//	if (!fread(pbData, sizeof(BYTE), cbData, fin)) {
//		printf("Error reading file!\n");
//		return 0;
//	}
//	fclose(fin);
//	return 1;
//}
//
//int ImportKey(HCRYPTPROV hProv, char * FileName, HCRYPTKEY &hPubKey)
//{
//	PBYTE pbKeyBlob;// = new BYTE[200];
//	DWORD dwBlobLen;
//	if (!ReadFile(FileName, pbKeyBlob, dwBlobLen)) return 0;
//	if (CryptImportKey(hProv, pbKeyBlob, dwBlobLen, 0, 0, &hPubKey)) {
//		printf("The key has been imported.\n");
//	}
//	else {
//		printf("Public key import failed.");
//	}
//	return 1;
//}
//
//int VerifyHash(HCRYPTHASH hHash, HCRYPTKEY hPubKey, char *FileName)
//{
//	BYTE *pbSignature;
//	DWORD dwSigLen = 0;
//	if (!ReadFile(FileName, pbSignature, dwSigLen)) return 0;
//	if (CryptVerifySignature(hHash, pbSignature, dwSigLen, hPubKey, NULL, 0)) {
//		printf("The signature has been verified.\n");
//	}
//	else {
//		printf("Signature not validated!\n");
//	}
//	return 1;
//}
//
//int main(int argc, char *argv[])
//{
//	if (argc < 4) return 1;
//	HCRYPTPROV hProv;
//	HCRYPTHASH hHash;
//	HCRYPTKEY hSessKey;
//	HCRYPTKEY hPubKey;
//	LPTSTR pszPubKey = argv[2];
//	LPTSTR pszHData = argv[3];
//	LPTSTR pszSignature = argv[4];
//
//	GethProv(hProv);
//	GenPrivateKey(hProv, hSessKey);
//
//	ImportKey(hProv, pszPubKey, hPubKey);
//	GetHash(hProv, hHash, hSessKey, pszHData);
//	VerifyHash(hHash, hPubKey, pszSignature);
//
//	if (hHash) CryptDestroyHash(hHash);
//	if (hSessKey) CryptDestroyKey(hSessKey);
//	if (hPubKey) CryptDestroyKey(hPubKey);
//	if (hProv) CryptReleaseContext(hProv, 0);
//
//	system("pause");
//	return 0;
//} //  End of main
//
//
//void MyHandleError(char *s)
//{
//	fprintf(stderr, "An error occurred in running the program. \n");
//	fprintf(stderr, "%s\n", s);
//	fprintf(stderr, "Error number %x.\n", GetLastError());
//	fprintf(stderr, "Program terminating. \n");
//	exit(1);
//} 
