#include "thread.h"

long g_value = 0;
DWORD CALLBACK InterProc1(LPVOID pParam) {
	for (int i = 0; i < 1000000; i++) {
		//		g_value++;
		InterlockedIncrement(&g_value);//�������������ԭ�Ӳ��������ڴ����
	}
	return 0;
}
DWORD CALLBACK InterProc2(LPVOID pParam) {
	for (int i = 0; i < 1000000; i++) {
		//		g_value++;
		InterlockedIncrement(&g_value);
	}
	return 0;
}
void inter() {
	DWORD nID = 0;
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, InterProc1, NULL, 0, &nID);
	hThread[1] = CreateThread(NULL, 0, InterProc2, NULL, 0, &nID);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);//�ȴ�����߳�ִ����ɷ���
	printf("%d\n", g_value);
}