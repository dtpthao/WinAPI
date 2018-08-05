//#include <iostream>
//#include <Windows.h>
//#include <wincrypt.h>
//#include <string.h>
//#include <stdio.h>
//
//using namespace std;
//
//
//void EnumContainers() 
//{
//	HCRYPTPROV hProv;
//	BYTE       pbData[1000];
//	DWORD cbData = 1000, flag = CRYPT_FIRST;
//	int i = 0;
//	
//	if (CryptAcquireContext(&hProv, NULL, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
//	{
//		while (CryptGetProvParam(hProv, PP_ENUMCONTAINERS, pbData, &cbData, flag))
//		{
//			printf("  %d: %s\n", i, pbData);
//			flag = CRYPT_NEXT;
//			i++;
//		}
//	}
//	if (!CryptReleaseContext(hProv, 0)) printf("ERROR releasing variable.\n");
//}
//
//void EnumAlgorithms()
//{
//	HCRYPTPROV hProv;
//	DWORD cbData = 1000;
//	PROV_ENUMALGS_EX *pbData2 = new PROV_ENUMALGS_EX[20];
//	DWORD *pincr = new DWORD[20];
//	printf("No.\tID\tDefLen  MinLen  Incr.  MaxLen  Prot.  "
//		"NameLen\t    Name   LongNameLen\tLongName\n");
//	printf("_______________________________________________"
//		"__________________________________________________\n");
//	int index = 0;
//	if (!CryptAcquireContext(&hProv, NULL, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) exit(1);
//	if (CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)pbData2, &cbData, CRYPT_FIRST))
//	{
//		do index++;
//		while (CryptGetProvParam(hProv, PP_ENUMALGS_EX, (BYTE*)&pbData2[index], &cbData, CRYPT_NEXT));
//
//		PROV_ENUMALGS_EX tmp;
//		for (int i = 0; i < index - 1; i++) {
//			for (int j = i + 1; j < index; j++) {
//				if (pbData2[j].aiAlgid < pbData2[i].aiAlgid) {
//					tmp = pbData2[i];
//					pbData2[i] = pbData2[j];
//					pbData2[j] = tmp;
//				}
//			}
//		}
//		DWORD x;
//		for (int i = 0; i < index; i++) {
//			if (!CryptGetProvParam(hProv, PP_SIG_KEYSIZE_INC, (BYTE*)&pincr[i], &cbData, 0))
//				printf("Error! - PP_SIG_KEYSIZE_INC!\n");   //this is insane! you're stupid!
//			
//			printf("%2d%10d", i, pbData2[i].aiAlgid);
//			printf("%9d", pbData2[i].dwDefaultLen);
//			printf("%9d", pbData2[i].dwMinLen);
//			printf("%5d", pincr[i]);
//			printf("%9d", pbData2[i].dwMaxLen);
//			printf("%7d", pbData2[i].dwProtocols);
//			printf("%7d", pbData2[i].dwNameLen);
//			printf("%15s", pbData2[i].szName);
//			printf("%9d\t", pbData2[i].dwLongNameLen);
//			printf("%s\n", pbData2[i].szLongName);
//		}
//	}
//	else printf("Error reading PP_ENUMALGS_EX.\n\n");
//}
//
//void GetProvParam(HCRYPTPROV hProv, LPCTSTR pszContainer)
//{
//	BYTE       pbData[1000];
//	DWORD cbData = 1000;
//	
//	if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_FULL, 0))
//	{
//		if (CryptGetProvParam(hProv, PP_PROVTYPE, pbData, &cbData, 0)) {
//			printf("  PP_PROVTYPE:\t%d\n", *pbData);
//		}
//		else {
//			printf("Error reading Provider Type.\n");
//		}
//		cbData = 1000;
//		if (CryptGetProvParam(hProv, PP_NAME, pbData, &cbData, 0)) {
//			printf("  PP_NAME:\t%s\n", pbData);
//		}
//		else {
//			printf("Error reading Provider Name.\n");
//		}
//		cbData = 1000;
//		if (CryptGetProvParam(hProv, PP_CONTAINER, pbData, &cbData, 0)) {  //not use with the default key container
//																			 //printf("CryptGetProvParam succeeded. \n");
//			printf("  PP_CONTAINER:\t%s\n", pbData);
//		}
//		else {
//			printf("Error reading key container name. \n");
//		}
//		cbData = 1000;
//		if (CryptGetProvParam(hProv, PP_VERSION, pbData, &cbData, 0)) {
//			printf("  PP_VERSION:\t%d\n", *pbData);
//		}
//		else {
//			printf("Error reading CryptoAPI version.\n");
//		}
//	}
//}
//
//
//bool CreatNewKeyContainer()
//{
//	HCRYPTPROV hProv;
//	LPCTSTR pszContainer = "NewContainer";
//	if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_FULL, 0)) {
//		printf("A cryptographic context with the %s key container has been acquired.\n\n",
//			pszContainer);
//	}
//	else {
//		if (GetLastError() == NTE_BAD_KEYSET) {
//			if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_FULL, CRYPT_NEWKEYSET))
//			{
//				printf("A new key container \"%s\" has been created.\n\n", pszContainer);
//			}
//			else {
//				printf("ERROR creating new key container.\n");
//				return 1;
//			}
//		}
//		else {
//			printf("ERROR acquiring a cryptographic context.\n");
//			return 1;
//		}
//	}
//
//	printf("Get some parameters: \n");
//	GetProvParam(hProv, pszContainer);
//	cout << endl;
//	printf("EnumContainers:\n");
//	EnumContainers();
//	cout << endl;
//
//	if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_AES, CRYPT_DELETE_KEYSET)) {
//		printf("The key container \"%s\" has been deleted.\n\n", pszContainer);
//	}
//	else printf("Can not delete a key container %s.\n\n", pszContainer);
//	/*else printf("Can not delete a key container %s.\n\n", pszContainer);
//	if (!CryptReleaseContext(hProv, 0)) printf("ERROR releasing variable.\n");*/
//	return 0;
//}
//
//
//int main()
//{
//	printf("CreatNewKeyContainer:\n  ");
//	CreatNewKeyContainer();
//	printf("EnumAlgorithms + PP_SIG_KEYSIZE_INC:\n\n");
//	EnumAlgorithms();
//
//	system("pause");
//	return 0;
//}
