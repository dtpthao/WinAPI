//#include <iostream>
//#include <windows.h>
//#include <wincrypt.h>
//
//using namespace std;
//
//bool CrEnumProvTypes(DWORD &dwIndex, DWORD *dwType, LPTSTR pszName[])
//{
//	DWORD cbName;
//	dwIndex = 0;
//	while (CryptEnumProviderTypes(dwIndex, NULL, 0, dwType, NULL, &cbName)) {
//		if (!(*pszName = new char[cbName])) {
//			printf("ERROR! - Local Failed.\n");
//			return 1;
//		}
//		if (CryptEnumProviderTypes(dwIndex++, NULL, 0, dwType, *pszName, &cbName)) {
//			printf("     %4.0d\t%s\n", *dwType, *pszName);
//			pszName++; dwType++;
//		}
//		else {
//			printf("ERROR! - CryptEnumProviderTypes.\n");
//			return 1;
//		}
//	}
//	return 0;
//}
//
//bool CrEnumProviders(DWORD &dwIndex, DWORD *dwType, LPTSTR pszName[])
//{
//	DWORD cbName;
//	dwIndex = 0;
//	while (CryptEnumProviders(dwIndex, NULL, 0, dwType, NULL, &cbName)) {
//		if (!(*pszName = new char[cbName])) {
//			printf("ERROR! - Local Failed.\n");
//			return 1;
//		}
//		if (CryptEnumProviders(dwIndex++, NULL, 0, dwType, *pszName, &cbName)) {
//			printf("     %4.0d\t%s\n", *dwType, *pszName);
//			pszName++; dwType++;
//		}
//		else {
//			printf("ERROR! - CryptEnumProviders.\n");
//			return 1;
//		}
//	}
//	return 0;
//}
//
//bool CrGetDefaultProvider(DWORD dwProvType)
//{
//	DWORD       cbProvName = 0;
//	LPTSTR      pbName = NULL;
//
//	if (!(CryptGetDefaultProvider(dwProvType, NULL, 0, NULL, &cbProvName)))
//	{
//		printf("Error getting the length of the default provider name.\n");
//		return 1;
//	}
//	if (!(pbName = new char[cbProvName]))
//	{
//		printf("Error during memory allocation for provider name.\n");
//		return 1;
//	}
//	if (CryptGetDefaultProvider(dwProvType, NULL,
//		CRYPT_MACHINE_DEFAULT, pbName, &cbProvName))
//	{
//		printf("     Machine   \t  %s\n", pbName);
//	}
//	else {
//		printf("Getting the name of the provider failed.\n");
//		return 1;
//	}
//	if (CryptGetDefaultProvider(dwProvType, NULL,
//		CRYPT_USER_DEFAULT, pbName, &cbProvName)) {
//		printf("     User      \t  %s\n", pbName);
//	}
//	else {
//		printf("Getting the name of the provider failed.\n");
//		return 1;
//	}
//	delete[]pbName;
//	return 0;
//}
//
//void GetProvParam(HCRYPTPROV hCrProv, LPCTSTR pszContainer)
//{
//	//HCRYPTPROV hCrProv;
//	BYTE       pbData[1000];
//	DWORD cbData = 1000;
//
//	if (CryptAcquireContext(&hCrProv, pszContainer, 0, PROV_RSA_FULL, 0))
//	{
//		if (CryptGetProvParam(hCrProv, PP_PROVTYPE, pbData, &cbData, 0)) {
//			printf("Provider Type: %d\n\n", *pbData);
//		}
//		else {
//			printf("Error reading Provider Type.\n");
//		}
//		cbData = 1000;
//		if (CryptGetProvParam(hCrProv, PP_NAME, pbData, &cbData, 0)) {
//			printf("Provider Name: %s\n\n", pbData);
//		}
//		else {
//			printf("Error reading Provider Name.\n");
//		}
//		cbData = 1000;
//		if (CryptGetProvParam(hCrProv, PP_CONTAINER, pbData, &cbData, 0)) {  //not use with the default key container
//																			 //printf("CryptGetProvParam succeeded. \n");
//			printf("Key Container name: %s\n\n", pbData);
//		}
//		else {
//			printf("Error reading key container name. \n");
//		}
//		cbData = 1000;
//		if (CryptGetProvParam(hCrProv, PP_VERSION, pbData, &cbData, 0)) {
//			printf("CryptoAPI version: %x\n\n", *pbData);
//		}
//		else {
//			printf("Error reading CryptoAPI version.\n");
//		}
//	}
//
//	cbData = 1000;
//	PROV_ENUMALGS_EX *pbData2 = new PROV_ENUMALGS_EX[20];
//	printf("No.\tID\tDefLen\t  MinLen   MaxLen  Protocols  "
//		"NameLen\t  Name\t  LongNameLen\tLongName\n");
//	printf("_______________________________________________"
//		"__________________________________________________\n");
//	if (CryptGetProvParam(hCrProv, PP_ENUMALGS_EX, (BYTE*)pbData2, &cbData, CRYPT_FIRST))
//	{
//		int index = 1;
//		while (CryptGetProvParam(hCrProv, PP_ENUMALGS_EX, (BYTE*)&pbData2[index], &cbData, CRYPT_NEXT)) index++;
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
//		for (int i = 0; i < index; i++) {
//			printf("%2d%10d", i, pbData2[i].aiAlgid);
//			printf("%9d", pbData2[i].dwDefaultLen);
//			printf("%9d", pbData2[i].dwMinLen);
//			printf("%9d", pbData2[i].dwMaxLen);
//			printf("%9d", pbData2[i].dwProtocols);
//			printf("%9d", pbData2[i].dwNameLen);
//			printf("%15s", pbData2[i].szName);
//			printf("%9d\t", pbData2[i].dwLongNameLen);
//			printf("%s\n", pbData2[i].szLongName);
//		}
//	}
//	else printf("Error reading PP_ENUMALGS_EX.\n");
//}
//
//
//void GetProvParamEnum(DWORD dwProvType, LPTSTR pszProvName)
//{
//	HCRYPTPROV hProv;
//	BYTE       pbData[1000];
//	DWORD cbData = 1000, flag = CRYPT_FIRST;
//
//	if (CryptAcquireContext(&hProv, NULL, pszProvName, dwProvType, CRYPT_VERIFYCONTEXT))
//	{
//		while (CryptGetProvParam(hProv, PP_ENUMCONTAINERS, pbData, &cbData, flag))
//		{
//			printf("Key Container name: %s\n\n", pbData);
//			flag = 0;
//		}
//	}
//}
//
//int main()
//{
//	DWORD dwIndexType, dwIndexProv;
//	DWORD *pdwProvType = new DWORD[20], *pdwProvType2 = new DWORD[20];
//	LPTSTR* pszTypeName = new LPTSTR[20];
//	LPTSTR* pszProvName = new LPTSTR[30];
//
//	printf("Listing Available Provider Types:\n");
//	printf("Provider type\tProvider Type Name\n");
//	printf("_____________\t_____________________________________\n");
//	CrEnumProvTypes(dwIndexType, pdwProvType, pszTypeName);
//	//for (int i = 0; i < dwIndexType; i++) {
//	//	//printf("     %4.0d\t%s\n", pdwProvType[i], pszTypeName[i]);
//	//	GetProvParamEnum(pdwProvType[i]);
//	//}
//	cout << endl << endl;
//
//	printf("Listing Available Providers:\n");
//	printf("Provider type\tProvider Name\n");
//	printf("_____________\t_____________________________________\n");
//	CrEnumProviders(dwIndexProv, pdwProvType2, pszProvName);
//	/*for (int i = 0; i < dwIndexProv; i++) {
//	printf("     %4.0d\t%s\n", pdwProvType2[i], pszProvName[i]);
//	}*/
//	cout << endl << endl;
//
//	printf("Listing Available Provider Type:\n");
//	printf("Provider type\tProvider Type Name\n");
//	printf("_____________\t_____________________________________\n");
//	for (int i = 0; i < dwIndexType; i++) {
//		printf("     %4.0d\t%s\n", pdwProvType[i], pszTypeName[i]);
//		for (int j = 0; j < dwIndexProv; j++) {
//			if (pdwProvType2[j] == pdwProvType[i]) {
//				printf("         \t    %s\n", pszProvName[j]);
//				//GetProvParamEnum(pdwProvType[i], pszProvName[i]);
//			}
//		}
//	}
//	cout << endl << endl;
//
//	printf("Listing default provider:\n");
//	printf("Provider type\tProvider Type Name\n");
//	printf("___(Flag)____\t_____________________________________\n");
//	for (int i = 0; i < dwIndexType; i++) {
//		printf("     %4.0d\t%s\n", pdwProvType[i], pszTypeName[i]);
//		CrGetDefaultProvider(pdwProvType[i]);
//		cout << endl;
//	}
//	cout << endl << endl;
//
//	//GetDescriptorCSP();
//
//
//	delete[]pdwProvType;
//	delete[]pdwProvType2;
//	delete[]pszTypeName;
//	delete[]pszProvName;
//
//	system("pause");
//	return 0;
//}
//
//////////////////////////////////////////////////////////////////////////////////////////
//
////bool GetDescriptorCSP()
////{
////	HCRYPTPROV hProv;
////	LPCTSTR pszContainer = "NewContainer";
////
////	if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_FULL, 0)) {
////		printf("A cryptographic context with the %s key container has been acquired.\n\n",
////			pszContainer);
////	}
////	else {
////		if (GetLastError() == NTE_BAD_KEYSET) {
////			if (CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_FULL, CRYPT_NEWKEYSET))
////			{
////				printf("A new key container \"%s\" has been created.\n\n", pszContainer);
////			}
////			else {
////				printf("ERROR creating new key container.\n");
////				return 1;
////			}
////		}
////		else {
////			printf("ERROR acquiring a cryptographic context.\n");
////			return 1;
////		}
////	}
////	
////	GetProvParam(hProv, pszContainer);
////	if (!CryptAcquireContext(&hProv, pszContainer, 0, PROV_RSA_FULL, CRYPT_DELETE_KEYSET)) 
////	{
////		printf("Can not delete a key container %s.\n\n", pszContainer);
////	}
////	/*else printf("Can not delete a key container %s.\n\n", pszContainer);
////	if (!CryptReleaseContext(hProv, 0)) printf("ERROR releasing variable.\n");*/
////	return 0;
////}
//
//////////////////////////////////////////////////////////////////////////////////////////