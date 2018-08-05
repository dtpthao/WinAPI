//#include <iostream>
//#include <Windows.h>
//#include <wincrypt.h>
//#include <iomanip>
//
//using namespace std;
//
//HCRYPTPROV hProv = NULL;
//HCRYPTHASH hHash = NULL;
//HCRYPTKEY hSessKey = NULL;
//HCRYPTKEY hXchgKey = NULL;
//HCRYPTKEY hSignKey = NULL;
//LPCTSTR pszContainer = "ContainerLab_2_1";
//PROV_ENUMALGS_EX DataXchg;		
//PROV_ENUMALGS_EX DataSign;	
//PROV_ENUMALGS_EX DataSess;
//
////void printEnumAlgEx(PROV_ENUMALGS_EX bData);
//BOOL Get_hProv();
//BOOL GetProvParam();
//BOOL GenKey(ALG_ID Algid, DWORD dwSize, HCRYPTKEY &hKey, char *s);
//DWORD GetSessKeyParam(DWORD Param, PBYTE pbData);
//void GenAllKey();
//
//void subwrite(void* buf, int size, int count, FILE *F)
//{
//	cout << ((size*count) << 2);
//	if (fwrite(buf, size, count, F)) {
//		cout << " bits was written to file." << endl;
//	}
//	else
//		cout << " bits can not be written to file." << endl;
//}
//
//void WriteBlobToFile(BYTE *pbData, DWORD cbData)
//{
//	char szFileName[] = "PubKey.txt";
//	DWORD dwMode, lenIV;
//	BYTE DataIV[100];
//	FILE *F;// = fopen(szFileName, "wb");
//	if ((F = fopen(szFileName, "wb"))) {
//		printf("The file '%s' was opened for writing.\n", szFileName);
//	}
//	else printf("Can not open the file.\n");
//
//	////___Len Key Blob____
//	cout << left << setw(19) << "  Len Key Blob: ";
//	subwrite(&cbData, sizeof(DWORD), 1, F);
//
//	////___Key Blob_____
//	cout << left << setw(19) << "  Key Blob: ";
//	subwrite(pbData, sizeof(BYTE), cbData, F);
//
//	//////___mode____
//	//GetSessKeyParam(KP_MODE, (PBYTE)&dwMode); //cout << "\tmode: " << mode << endl;
//	//cout << left << setw(16) << "  Cipher mode = " << dwMode << ": ";
//	//subwrite(&dwMode, sizeof(DWORD), 1, F);
//
//	//////___Vector IV____
//	//lenIV = GetSessKeyParam(KP_IV, DataIV);
//	//cout << left << setw(17) << "  Len IV = " << lenIV << ": ";
//	//subwrite(&lenIV, sizeof(DWORD), 1, F);  //cout << "\tlenIV: " << lenIV << endl;
//	//cout << left << setw(17) << "  Vector IV: ";
//	//subwrite(DataIV, sizeof(BYTE), lenIV, F);
//
//	if (!fclose(F)) printf("File \"%s\" is closed.\n", szFileName);
//}
//
//BOOL ExportKey(HCRYPTKEY &hKey)
//{
//	DWORD cbData = 1000;
//	PBYTE DataBlob = new BYTE[1000];
//	//DWORD LenData = 1000;
//	if (!CryptExportKey(hSignKey, NULL, PUBLICKEYBLOB, 0, 0, &cbData))
//	{
//		cout << "Error getting key Blob length!\n\n" << endl;
//		return 0;
//	}
//	//DataBlob = new BYTE[LenData];
//	if (!CryptExportKey(hSignKey, 0, PUBLICKEYBLOB, 0, DataBlob, &cbData))
//	{
//		cout << "Error exporting Key Blob!\n\n" << endl;
//		return 0;
//	}
//	printf("Exporting Key Blob successfully.\n");
//	WriteBlobToFile(DataBlob, cbData);
//	cout << endl;
//	return 1;
//}
//
//BOOL ReadBlobFile(LPTSTR szFileName, BYTE *pbData, DWORD &cbData)//, PBYTE DataIV, DWORD &dwMode)
//{
//	//char szFileName[] = "Key.txt";
//	FILE *F = fopen(szFileName, "rb");
//	if (!F) {
//		printf("Can not open the file\n");
//		return 0;
//	}
//	printf("The file '%s' is open for reading.\n", szFileName);
//
//	if (fread(&cbData, sizeof(DWORD), 1, F)) {
//		printf("  Len Key: %d bytes\n", cbData);
//	}
//	else {
//		printf("  Error reading len Key Blob.\n");
//		return 0;
//	}
//	if (fread(pbData, sizeof(BYTE), cbData, F)) {
//		printf("  %d bytes were written to the key.\n", cbData);
//	}
//	else printf("  Error reading key Blob.\n");
//
//	if (!fclose(F)) printf("The file \"%s\" is closed.\n", szFileName);
//	return 1;
//}
//
//BOOL ImportKey(HCRYPTKEY &hKey, LPTSTR szImportKey)//PBYTE DataBlob, DWORD LenData)
//{
//	BYTE *pbData;// = new BYTE[1000];
//	DWORD cbData = 1000;
//	//HCRYPTKEY hKey;
//
//	//if (!ReadBlobFile(szImportKey, pbData, cbData)) return 0;
//	FILE *F = fopen(szImportKey, "rb");
//	if (!F) {
//		printf("Can not open the file\n");
//		return 0;
//	}
//	printf("The file '%s' is open for reading.\n", szImportKey);
//
//	if (fread(&cbData, sizeof(DWORD), 1, F)) {
//		printf("  Len Key: %d bytes\n", cbData);
//	}
//	else {
//		printf("  Error reading len Key Blob.\n");
//		return 0;
//	}
//	pbData = new BYTE[cbData];
//	if (fread(pbData, sizeof(BYTE), cbData, F)) {
//		printf("  %d bytes were written to the key.\n", cbData);
//	}
//	else printf("  Error reading key Blob.\n");
//
//	if (!fclose(F)) printf("The file \"%s\" is closed.\n", szImportKey);
//
//	if (!CryptImportKey(hProv, pbData, cbData, 0, 0, &hKey))
//	{
//		printf("Error importing key Blob!\n\n");
//		return 0;
//	}
//	else printf("Importing Key Blob successfully.\n");
//
//	return 1;
//}
//
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
//
//int GetHash()
//{
//	FILE *fin;
//	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
//		printf("Error getting hHash.\n");
//		return 0;
//	}
//	printf("A hash object has been created.\n");
//	/*if (CryptHashSessionKey(hHash, hSessKey, 0))
//	{
//		printf("The session key has been hashed. \n");
//	}*/
//	PBYTE pbData = new BYTE[1024];
//	DWORD lenData = 1024;
//	if (!(fin = fopen("Data.txt", "rb"))) {
//		printf("Can not open the file Data.txt!\n");
//		return 0;
//	}
//	/*if (!ReadData("Data.txt", pbData, lenData))
//		return 0;*/
//	while (!feof(fin)) {
//		lenData = fread(pbData, sizeof(BYTE), 1024, fin);
//		if (lenData < 1024 && (!feof(fin)))
//			printf("Error reading file Data.txt\n");
//		if (!CryptHashData(hHash, pbData, lenData, 0))
//			printf("Error during CryptHashData.\n");
//		else printf("The data has been added to the hash.\n\n");
//	}
//	return 1;
//}
//
//BOOL SignHash(DWORD &dwSigLen, PBYTE pbSignature)
//{
//	DWORD cbData = 100;
//	DWORD *pbData;
//	FILE *fout;
//	//DWORD dwSigLen = 0;
//	//PBYTE pbSignature;
//	//DWORD Aialg;// = GET_ALG_CLASS(DataSign.aiAlgid);
//	//if (!CryptGetKeyParam(hSignKey, KP_ALGID, (PBYTE)&Aialg, &cbData, 0)) {
//	//	printf("Error getting AL_GID!\n");
//	//	return 0;
//	//}
//
//	if (!CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSigLen)) {
//		printf("Error during CryptSignHash.\n");
//		return 0;
//	}
//	printf("Signature length %d found.\n", dwSigLen);
//	pbSignature = new BYTE[dwSigLen];
//	if (!CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)) {
//		printf("Error during CryptSignHash.\n");
//		return 0;
//	}
//	printf("pbSignature is the hash signature.\n");
//
//	if (!(fout = fopen("Signature.txt", "wb"))) {
//		printf("Error writing Signature to file.\n");
//		return 0;
//	}
//	if (!fwrite(&dwSigLen, sizeof(DWORD), 1, fout))
//		printf("Error writing SigLen!\n");
//	if (!fwrite(pbSignature, sizeof(BYTE), dwSigLen, fout))
//		printf("Error writing Signature!\n");
//	fclose(fout);
//	return 1;
//}
//
//BOOL VerifyHash(DWORD dwSigLen, PBYTE pbSignature, HCRYPTKEY hKey)
//{
//	DWORD cbData = 100;
//	DWORD *pbData;
//	//DWORD dwSigLen = 0;
//	//PBYTE pbSignature;
//	
//	if (!CryptVerifySignature(hHash, pbSignature, dwSigLen, hKey, 0, 0)) {
//		printf("Error during CryptVerifySignature.\n");
//		switch (GetLastError()) {
//		case NTE_BAD_HASH: printf("Bad Key!\n");
//		case NTE_BAD_SIGNATURE: printf("NTE_BAD_SIGNATURE!\n");
//		case NTE_BAD_KEY: printf("Bad Key!\n");
//		case ERROR_INVALID_PARAMETER: printf("ERROR_INVALID_PARAMETER!\n");
//		case NTE_BAD_FLAGS: printf("NTE_BAD_FLAGS\n");
//		case ERROR_INVALID_HANDLE: printf("ERROR_INVALID_HANDLE\n");
//		}
//		return 0;
//	}
//	/*printf("Signature length %d found.\n", dwSigLen);
//	pbSignature = new BYTE[dwSigLen];
//	if (!CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSigLen)) {
//		printf("Error during CryptSignHash.\n");
//		return 0;
//	}
//	printf("pbSignature is the hash signature.\n");*/
//	return 1;
//}
//
//BOOL ReleaseALL()
//{
//	if (hXchgKey) CryptDestroyKey(hXchgKey);
//	if (hSignKey) CryptDestroyKey(hSignKey);
//	if (hSessKey) CryptDestroyKey(hSessKey);
//	if (hHash) CryptDestroyHash(hHash);
//	if (GetLastError()) return 1;
//	return 0;
//}
//
//int main()
//{
//	HCRYPTKEY hKey;
//	DWORD dwSigLen = 0;
//	PBYTE pbSignature = new BYTE[100];
//	if (!Get_hProv()) return 1;
//	if (!GetProvParam()) return ReleaseALL();
//
//	/*if (CryptGetUserKey(hProv,AT_SIGNATURE,	&hKey))
//	{
//		printf("The signature key has been acquired. \n");
//	}
//	else
//	{
//		printf("Error during CryptGetUserKey for signkey.");
//	}*/
//
//	GenAllKey();
//	ExportKey(hKey);
//	ImportKey(hKey, "PubKey.txt");
//	GetHash();
//	SignHash(dwSigLen, pbSignature);
//	VerifyHash(dwSigLen, pbSignature, hKey);
//	ReleaseALL();
//
//	system("pause");
//	return 0;
//}
//
//BOOL Get_hProv()//HCRYPTPROV hProv, LPCTSTR pszContainer)
//{
//	if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_AES, 0)) {
//		printf("The key container %s has been acquired.\n\n", pszContainer);
//	}
//	else {
//		if (GetLastError() != NTE_BAD_KEYSET) {
//			printf("ERROR creating new key container.\n");
//			return 0;
//		}
//		if (!CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_AES, CRYPT_NEWKEYSET)) {
//			printf("ERROR acquiring a cryptographic context.\n");
//			return 0;
//		}
//		printf("A new key container \"%s\" has been created.\n\n", pszContainer);
//	}
//	return 1;
//}
//
//BOOL GetProvParam()
//{
//	PROV_ENUMALGS_EX EnumData;
//	DWORD cbData = 1000;
//	DWORD dwFlag = CRYPT_FIRST;
//	DataSign.aiAlgid = 0;
//	DataSess.aiAlgid = 0;
//	if (!CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&EnumData, &cbData, CRYPT_FIRST)) {
//		printf("Error reading PP_ENUMALGS_EX.\n\n");
//		return 0;
//	}
//	while (DataSign.aiAlgid == 0 || DataSess.aiAlgid == 0)
//	{
//		switch (EnumData.aiAlgid)
//		{
//		case CALG_RSA_SIGN:
//			DataSign = EnumData;
//			break;
//		case CALG_AES_128:
//			DataSess = EnumData;
//			break;
//		}
//		CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&EnumData, &cbData, CRYPT_NEXT);
//	}
//	
//	return 1;
//}
//
//BOOL GenKey(ALG_ID Algid, DWORD dwSize, HCRYPTKEY &hKey, char *s)
//{
//	DWORD dwFlags;
//	//cout << "  Len Key: " << dwSize << endl;
//	dwFlags = (dwSize << 16) | CRYPT_EXPORTABLE;
//	if (!CryptGenKey(hProv, Algid, dwFlags, &hKey))
//	{
//		printf("  GenKey Failed!\n\n");
//		return 0;
//	}
//	else printf("  A %s Key of %d bits length is created.\n", s, dwSize);
//	return 1;
//}
//
//DWORD GetSessKeyParam(DWORD Param, PBYTE pbData)
//{
//	DWORD cbData = 1000;
//	if (!CryptGetKeyParam(hSessKey, Param, pbData, &cbData, 0)) {
//		printf("Error geting parameter.\n\n");
//		return 0;
//	}
//	return cbData;
//}
//
//void GenAllKey()
//{
//	BYTE bData;
//	DWORD cbData = 1000;
//	PBYTE DataBlob = new BYTE[1000];
//	//_PLAINTEXTKEYBLOB DataBlob;
//	
//	////__________GenSignKey_______________________
//	DWORD IncrSign = 0, lenSignKey = 3;
//	printf("Gen Signature Key: \n");
//	GenKey(DataSign.aiAlgid, DataSign.dwMinLen, hSignKey, "Signature");
//	cout << endl;
//
//	/////_________GenSessionKey__________________
//	printf("Gen Session Key: \n");
//	if (!GenKey(DataSess.aiAlgid, 0, hSessKey, "Session"))
//	{
//		printf("Error during GenKey");
//	}
//}
