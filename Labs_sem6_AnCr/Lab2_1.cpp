//#include <iostream>
//#include <Windows.h>
//#include <wincrypt.h>
//#include <iomanip>
//
//using namespace std;
//
//HCRYPTPROV hProv = NULL;
//HCRYPTKEY hSessKey = NULL;
//HCRYPTKEY hXchgKey = NULL;
//HCRYPTKEY hSignKey = NULL;
//LPCTSTR pszContainer = "ContainerLab_2_1";
//PROV_ENUMALGS_EX bDataXchg;		//bDataXchg.aiAlgid = 0;
//PROV_ENUMALGS_EX bDataSign;		//bDataSign.aiAlgid = 0;
//PROV_ENUMALGS_EX bDataSess;		//bDataSess.aiAlgid = 0;
//
//void printEnumAlgEx(PROV_ENUMALGS_EX bData);
//BOOL Get_hProv();
//BOOL GetProvParam();
//BOOL GenKey(ALG_ID Algid, DWORD dwSize, HCRYPTKEY &hKey, char *s);
//
////typedef struct _PLAINTEXTKEYBLOB {
////	BLOBHEADER hdr;
////	DWORD      dwKeySize;
////	BYTE       rgbKeyData[];
////};// PLAINTEXTKEYBLOB, *PPLAINTEXTKEYBLOB;
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
////void subwrite(void* buf, int size, int count, FILE *F)
////{
////	cout << ((size*count) << 2);
////	if (fwrite(buf, size, count, F)) {
////		cout << " bits was written to file." << endl;
////	}
////	else
////		cout << " bits can not be written to file." << endl;
////}
////
////void WriteBlobToFile(BYTE *pbData, DWORD cbData)
////{
////	char szFileName[] = "Export.txt";
////	DWORD dwMode, lenIV;
////	BYTE DataIV[100];
////	FILE *F;// = fopen(szFileName, "wb");
////	if ((F = fopen(szFileName, "wb"))) {
////		printf("The file '%s' was opened for writing.\n", szFileName);
////	}
////	else printf("Can not open the file.\n");
////
////	////___Len Key Blob____
////	cout << left << setw(19) << "  Len Key Blob: ";
////	subwrite(&cbData, sizeof(DWORD), 1, F);
////
////	////___Key Blob_____
////	cout << left << setw(19) << "  Key Blob: ";
////	subwrite(pbData, sizeof(BYTE), cbData, F);
////
////	////___mode____
////	GetSessKeyParam(KP_MODE, (PBYTE)&dwMode); //cout << "\tmode: " << mode << endl;
////	cout << left << setw(16) << "  Cipher mode = " << dwMode << ": ";
////	subwrite(&dwMode, sizeof(DWORD), 1, F);
////
////	////___Vector IV____
////	lenIV = GetSessKeyParam(KP_IV, DataIV);
////	cout << left << setw(17) << "  Len IV = " << lenIV << ": ";
////	subwrite(&lenIV, sizeof(DWORD), 1, F);  //cout << "\tlenIV: " << lenIV << endl;
////	cout << left << setw(17) << "  Vector IV: ";
////	subwrite(DataIV, sizeof(BYTE), lenIV, F);
////
////	if (!fclose(F)) printf("File \"%s\" is closed.\n", szFileName);
////}
////
////BOOL ExportKey()
////{
////	DWORD cbData = 1000;
////	PBYTE DataBlob = new BYTE[1000];
////	//DWORD LenData = 1000;
////	if (!CryptExportKey(hSessKey, hXchgKey, SIMPLEBLOB, CRYPT_OAEP, 0, &cbData))
////	{
////		cout << "Error getting key Blob length!\n\n" << endl;
////		return 0;
////	}
////	//DataBlob = new BYTE[LenData];
////	if (!CryptExportKey(hSessKey, hXchgKey, SIMPLEBLOB, CRYPT_OAEP, DataBlob, &cbData))
////	{
////		cout << "Error exporting Key Blob!\n\n" << endl;
////		return 0;
////	}
////	printf("Exporting Key Blob successfully.\n");
////	WriteBlobToFile(DataBlob, cbData);
////	cout << endl;
////	return 1;
////}
//
//void subRead(void* buf, int size, int count, FILE *F)
//{
//	if (fread(buf, size, count, F)) {
//		printf("  %d bits\n", (size*count) << 2);
//	}
//	else
//		printf("  Error reading file.\n");
//}
//
//BOOL ReadBlobFile(BYTE *pbData, DWORD &cbData, PBYTE DataIV, DWORD &dwMode)
//{
//	char szFileName[] = "Export.txt";
//	DWORD lenIV;
//	FILE *F = fopen(szFileName, "rb");
//	if (!F) {
//		printf("Can not open the file\n");
//		return 0;
//	}
//	printf("The file '%s' was opened for reading.\n", szFileName);
//
//	if (fread(&cbData, sizeof(DWORD), 1, F)) {
//		printf("  Len Key: %d bits\n", cbData << 2);
//	}
//	else {
//		printf("  Error reading len Key Blob.\n");
//		return 0;
//	}
//	if (fread(pbData, sizeof(BYTE), cbData, F)) {
//		printf("  %d bits were written to the key.\n", cbData << 2);
//	}
//	else printf("  Error reading key Blob.\n");
//
//	if (fread(&dwMode, sizeof(DWORD), 1, F)) {
//		printf("  Mode: %d bits = %x.\n", sizeof(DWORD), dwMode);
//	}
//	else printf("  Error reading cipher mode.\n");
//
//	if (fread(&lenIV, sizeof(DWORD), 1, F)) {
//		printf("  Len IV: %d bits\tlenIV = %d.\n", sizeof(DWORD), lenIV);
//	}
//	else printf("  Error reading lenIV.\n");
//		
//	if (fread(DataIV, sizeof(BYTE), lenIV, F)) {
//		printf("  %d bits were written to the vector IV.\n", lenIV << 2);
//	}
//	else {
//		printf("  Error reading vector IV.\n");
//		return 0;
//	}
//	
//	if (!fclose(F)) printf("The file \"%s\" is closed.\n", szFileName);
//	return 1;
//}
//
//BOOL ImportKey()//PBYTE DataBlob, DWORD LenData)
//{
//	BYTE *pbData = new BYTE[1000];
//	DWORD cbData = 1000;
//	DWORD dwMode;
//	BYTE DataIV[1000];
//	HCRYPTKEY hKey;
//
//	if (!ReadBlobFile(pbData, cbData, DataIV, dwMode)) return 0;
//	if (!CryptImportKey(hProv, pbData, cbData, hXchgKey, CRYPT_OAEP, &hKey))
//	{
//		printf("Error importing key Blob!\n\n");
//		return 0;
//	}
//	else printf("Importing Key Blob successfully.\n");
//
//	////__________Set_IV__________________________
//	if (!CryptSetKeyParam(hSessKey, KP_IV, DataIV, 0))
//		printf("Error setting initialization vector!\n");
//	else printf("Setting IV successfully\n");
//	//const DWORD mode = dwMode; cout << dwMode << endl;
//	if (!CryptSetKeyParam(hSessKey, KP_MODE, (PBYTE)&dwMode, 0)) {
//		printf("Error setting cipher mode!\n\n");
//	}
//	else printf("The cipher mode of the key is set to %d.\n\n", dwMode);
//	CryptDestroyKey(hKey);
//	return 1;
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
//	if (!CryptGetProvParam(hProv, PP_SIG_KEYSIZE_INC, (BYTE*)&IncrSign, &cbData, 0))
//		printf("Error! - PP_SIG_KEYSIZE_INC!\n");
//
//	lenSignKey = lenSignKey*IncrSign + bDataSign.dwMinLen;
//	while (lenSignKey > bDataSign.dwMaxLen) lenSignKey -= IncrSign;
//
//	printf("Gen Signature Key: \n");
//	GenKey(bDataSign.aiAlgid, lenSignKey, hSignKey, "Signature");
//	cout << endl;
//
//	////_________GenExchangeKey_______________________
//	printf("Gen Exchange Key: \n");
//	GenKey(bDataXchg.aiAlgid, bDataXchg.dwMaxLen >> 4, hXchgKey, "Exchange");
//	cout << endl;
//
//	/////_________GenSessionKey__________________
//	printf("Gen Session Key: \n");
//	if (GenKey(bDataSess.aiAlgid, 0, hSessKey, "Session"))
//	{
//		DWORD LenBlock;
//		printf("  LenBlock: ");
//		if (GetSessKeyParam(KP_BLOCKLEN, (PBYTE)&LenBlock))
//			printf("%d bits\n", LenBlock); 
//
//		////_________GenRamdomData__________________
//		BYTE pbDataRandom[100];
//		if (!CryptGenRandom(hProv, LenBlock >> 3, pbDataRandom))
//			printf("Error! - CryptGenRandom.\n");
//		printf("  %d bytes of random data have been generated.\n", LenBlock >> 3);
//
//		////__________Set_IV__________________________
//		if (!CryptSetKeyParam(hSessKey, KP_IV, pbDataRandom, 0))
//			printf("  Error setting initialization vector!\n");
//		const DWORD dwMode = CRYPT_MODE_CFB;
//		if (!CryptSetKeyParam(hSessKey, KP_MODE, (PBYTE)&dwMode, 0)) {
//			printf("  Error setting cipher mode!\n\n");
//		}
//		printf("  The cipher mode of Session key is set to CFB.\n\n");
//	}
//}
//
//BOOL ReleaseALL()
//{
//	if (hXchgKey) CryptDestroyKey(hXchgKey);
//	if (hSignKey) CryptDestroyKey(hSignKey);
//	if (hSessKey) CryptDestroyKey(hSessKey);
//	if (GetLastError()) return 1;
//	return 0;
//}
//
//int main()
//{
//	if (!Get_hProv()) return 1;
//	if (!GetProvParam()) return ReleaseALL();
//	GenAllKey();
//
//	
//	if (hSessKey && hXchgKey) {
//		if (ExportKey())
//			ImportKey();
//	}
//	ReleaseALL();
//	system("pause");
//	return 0;
//}
//
//void printEnumAlgEx(PROV_ENUMALGS_EX bData)
//{
//	printf("%10d", bData.aiAlgid);
//	printf("%9d", bData.dwDefaultLen);
//	printf("%9d", bData.dwMinLen);
//	printf("%9x", bData.dwMaxLen);
//	printf("%7d", bData.dwProtocols);
//	printf("%7d", bData.dwNameLen);
//	printf("%15s", bData.szName);
//	printf("%9d\t", bData.dwLongNameLen);
//	printf("%s\n", bData.szLongName);
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
//BOOL GetProvParam()//HCRYPTPROV hProv, PROV_ENUMALGS_EX bDataXchg,
//	//PROV_ENUMALGS_EX bDataSign, PROV_ENUMALGS_EX bDataSess)
//{
//	PROV_ENUMALGS_EX EnumData;
//	DWORD cbData = 1000;
//	DWORD dwFlag = CRYPT_FIRST;
//	while (CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&EnumData, &cbData, dwFlag))
//	{
//		switch (EnumData.aiAlgid)
//		{
//		case CALG_RSA_SIGN:
//			bDataSign = EnumData;
//			//printEnumAlgEx(bDataSign);
//			break;
//
//		case CALG_RSA_KEYX:
//			bDataXchg = EnumData;
//			//printEnumAlgEx(bDataXchg);
//			break;
//
//		case CALG_AES_128:
//			bDataSess = EnumData;
//			//printEnumAlgEx(bDataSess);
//			break;
//		}
//		dwFlag = CRYPT_NEXT;
//	}
//	if (dwFlag == CRYPT_FIRST) {
//		printf("Error reading PP_ENUMALGS_EX.\n\n");
//		return 0;
//	}
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
