#include "thread.h"

HANDLE g_hEvent = 0;//接收事件句柄
DWORD CALLBACK PrintProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hEvent, INFINITE);//等待事件
//		ResetEvent( g_hEvent );//手动复位需要加这一行，自动不需要
		printf("****************\n");
	}
	return 0;
}
DWORD CALLBACK CtrlProc(LPVOID pParam) {
	while (1) {
		Sleep(1000);
		SetEvent(g_hEvent);//设置事件为有信号状态
	}
	return 0;
}
void event() {
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);//true手动复位,false自动复位
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(g_hEvent);
}