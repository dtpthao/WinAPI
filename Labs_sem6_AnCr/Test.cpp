////--------------------------------------------------------------------
//// Copyright (C) Microsoft.  All rights reserved.
//// Example of signing a hash and 
//// verifying the hash signature.
//#pragma comment(lib, "crypt32.lib")
//
//#include <stdio.h>
//#include <windows.h>
//#include <Wincrypt.h>
//#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
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
//void GenAllKey(HCRYPTPROV hProv, HCRYPTKEY &hSignKey, HCRYPTKEY &hSessKey) 
//{
//	PROV_ENUMALGS_EX EnumData, DataSign, DataSess;
//	DWORD cbData = 1000;
//	DWORD dwFlag = CRYPT_FIRST;
//	CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&EnumData, &cbData, CRYPT_FIRST);
//	do {
//		if (EnumData.aiAlgid == CALG_RSA_SIGN)
//			DataSign = EnumData;
//		if (EnumData.aiAlgid == CALG_AES_128)
//			DataSess = EnumData;
//	} while (CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&EnumData, &cbData, CRYPT_NEXT));
//
//	dwFlag = (DataSign.dwMinLen << 16) | CRYPT_EXPORTABLE;
//	if (!CryptGenKey(hProv, DataSign.aiAlgid, dwFlag, &hSignKey))
//	{
//		printf("  GenKey Failed!\n\n");
//	}
//	else printf("  A Sign Key of %d bits length is created.\n", DataSign.dwMinLen);
//
//	if (!CryptGenKey(hProv, DataSess.aiAlgid, CRYPT_EXPORTABLE, &hSessKey)){
//		printf("  GenKey Failed!\n\n");
//	}
//	else printf("  A Sess Key of defalt bits length is created.\n");
//}
//
//int WriteToFile(char *filename, PBYTE pbData, DWORD cbData) 
//{
//	FILE *fout;
//	if (!(fout = fopen(filename, "wb"))) {
//		printf("Error writing Signature to file.\n");
//		return 0;
//	}
//	if (!fwrite(&cbData, sizeof(DWORD), 1, fout)) {
//		printf("Error writing to file!\n");
//		return 0;
//	}
//	if (!fwrite(pbData, sizeof(BYTE), cbData, fout)) {
//		printf("Error writing to file!\n");
//	}
//	fclose(fout);
//}
//
//void ExportKey(HCRYPTKEY hKey, char *filename)
//{
//	PBYTE pbKeyBlob;
//	DWORD dwBlobLen;
//	if (CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, NULL, &dwBlobLen)) {
//		printf("Size of the BLOB for the public key determined. \n");
//	}
//	else {
//		printf("Error computing BLOB length.\n");
//	}
//
//	if (pbKeyBlob = (BYTE*)malloc(dwBlobLen)) {
//		printf("Memory has been allocated for the BLOB. \n");
//	}
//	else {
//		printf("Out of memory. \n");
//	}
//
//	if (CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, pbKeyBlob, &dwBlobLen)) {
//		printf("Contents have been written to the BLOB. \n");
//	}
//	else {
//		printf("Error during CryptExportKey.");
//	}
//	WriteToFile(filename, pbKeyBlob, dwBlobLen);
//}
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
//		MyHandleError("Error during CryptCreateHash.");
//	}
//
//	FILE *fin = fopen("otchot.docx", "wb");
//	if (!fin) {
//		printf("Error reading Data.txt!\n");
//		return 0;
//	}
//	
//	while (feof(fin)) {
//		dwBufferLen = fread(pbBuffer, sizeof(BYTE), 1024, fin);
//		if (dwBufferLen < 1024 && (!feof(fin)))
//			printf("Error reading file Data.txt\n");
//		
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
//void SignHash(HCRYPTHASH &hHash, char *FileName)//, BYTE *&pbSignature, DWORD &dwSigLen)
//{
//	BYTE *pbSignature;
//	DWORD dwSigLen;
//	dwSigLen = 0;
//	if (CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen)) {
//		printf("Signature length %d found.\n", dwSigLen);
//	}
//	else {
//		printf("Error during CryptSignHash.\n");
//	}
//
//	if (pbSignature = (BYTE *)malloc(dwSigLen)) {
//		printf("Memory allocated for the signature.\n");
//	}
//	else {
//		printf("Out of memory.\n");
//	}
//	if (CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)) {
//		printf("pbSignature is the hash signature.\n");
//	}
//	else{
//		printf("Error during CryptSignHash.\n");
//	}
//	
//	WriteToFile(FileName, pbSignature, dwSigLen);
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
//int ImportKey(HCRYPTPROV hProv, HCRYPTKEY &hPubKey)
//{
//	PBYTE pbKeyBlob;// = new BYTE[200];
//	DWORD dwBlobLen;
//	if (!ReadFile("SignKey.txt", pbKeyBlob, dwBlobLen)) return 0;
//	if (CryptImportKey(hProv, pbKeyBlob, dwBlobLen, 0, 0, &hPubKey)) {
//		printf("The key has been imported.\n");
//	}
//	else {
//		printf("Public key import failed.\n");
//	}
//	return 1;
//}
//
//int VerifyHash(HCRYPTHASH hHash, HCRYPTKEY hPubKey)
//{
//	BYTE *pbSignature = new BYTE[300];
//	DWORD dwSigLen = 0;
//	if (!ReadFile("Signature.txt", pbSignature, dwSigLen)) 
//		return 0;
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
//	if (argc < 4) return 0;
//	HCRYPTPROV hProv;
//	HCRYPTHASH hHash;
//	HCRYPTKEY hKey;
//	HCRYPTKEY hSessKey;
//	HCRYPTKEY hPubKey;
//	LPTSTR pszPubKey = argv[2];
//	LPTSTR pszHData = argv[3];
//	LPTSTR pszSignature = argv[4];
//
//	GethProv(hProv);
//	GenAllKey(hProv, hKey, hSessKey);
//
//	ExportKey(hKey, pszPubKey);
//	GetHash(hProv, hHash, hSessKey, pszHData);
//	
//	SignHash(hHash, pszSignature);// , pbSignature, dwSigLen);
//
//	
//	//-------------------------------------------------------------------
//	// Destroy the hash object.
//
//	if (hHash) CryptDestroyHash(hHash);
//
//	printf("The hash object has been destroyed.\n");
//	printf("The signing phase of this program is completed.\n\n");
//
//	//ImportKey(hProv, hPubKey);
//	//GetHash(hProv, hHash, hSessKey, pbBuffer, dwBufferLen);
//	//-------------------------------------------------------------------
//	// Validate the digital signature.
//	//VerifyHash(hHash, hPubKey);//, pbSignature, dwSigLen);
//	
//	
//
//	//if (pbSignature) free(pbSignature);
//	if (hHash) CryptDestroyHash(hHash);
//	if (hProv)
//		CryptReleaseContext(hProv, 0);
//
//	system("pause");
//	return 0;
//} //  End of main
//
//  //-------------------------------------------------------------------
//  //  This example uses the function MyHandleError, a simple error
//  //  handling function, to print an error message to the  
//  //  standard error (stderr) file and exit the program. 
//  //  For most applications, replace this function with one 
//  //  that does more extensive error reporting.
//
//void MyHandleError(char *s)
//{
//	fprintf(stderr, "An error occurred in running the program. \n");
//	fprintf(stderr, "%s\n", s);
//	fprintf(stderr, "Error number %x.\n", GetLastError());
//	fprintf(stderr, "Program terminating. \n");
//	exit(1);
//} // End of MyHandleError
