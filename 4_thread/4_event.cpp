#include "thread.h"

HANDLE g_hEvent = 0;//�����¼����
DWORD CALLBACK PrintProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hEvent, INFINITE);//�ȴ��¼�
//		ResetEvent( g_hEvent );//�ֶ���λ��Ҫ����һ�У��Զ�����Ҫ
		printf("****************\n");
	}
	return 0;
}
DWORD CALLBACK CtrlProc(LPVOID pParam) {
	while (1) {
		Sleep(1000);
		SetEvent(g_hEvent);//�����¼�Ϊ���ź�״̬
	}
	return 0;
}
void event() {
	g_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);//true�ֶ���λ,false�Զ���λ
	DWORD nID = 0;
	HANDLE hThread[2] = { 0 };
	hThread[0] = CreateThread(NULL, 0, PrintProc, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, CtrlProc, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(g_hEvent);
}