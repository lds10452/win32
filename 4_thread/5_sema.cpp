#include "thread.h"

HANDLE g_hSema = 0;//信号量句柄
DWORD CALLBACK TestProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hSema, INFINITE);//没通过一次，计数值减一
		printf("*********\n");
	}
}
void sema() {
	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);//初始计数值为3，最大10
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL, 0, TestProc, NULL, 0, &nID);
	getchar();
	ReleaseSemaphore(g_hSema, 10, NULL);//复位计数值为10,设置超过最大值的值不起作用
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(g_hSema);
}
