#include "thread.h"

HANDLE g_hMutex = 0;//接收互斥句柄
DWORD CALLBACK MutexProc(LPVOID pParam) {
	char* pszText = (char*)pParam;
	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pszText); i++) {
			printf("%c", pszText[i]);
			Sleep(125);
		}
		printf("\n");
		ReleaseMutex(g_hMutex);
	}
	return 0;
}
DWORD CALLBACK MutexProc2(LPVOID pParam) {
	char* pszText = (char*)pParam;
	while (1) {
		WaitForSingleObject(g_hMutex, INFINITE);
		for (int i = 0; i < strlen(pszText); i++) {
			printf("%c", pszText[i]);
			Sleep(125);
		}
		printf("\n");
		ReleaseMutex(g_hMutex);
	}
	return 0;
}
void mutex() {
	g_hMutex = CreateMutex(NULL, FALSE, NULL);//false:主线程不拥有互斥量
	DWORD nID = 0;
	const char* pszText = "*******";
	HANDLE hThread = CreateThread(NULL, 0, MutexProc, (void*)pszText, 0, &nID);
	const char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread(NULL, 0, MutexProc2, (void*)pszText2, 0, &nID);
	getchar();
	CloseHandle(g_hMutex);
}