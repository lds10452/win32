#include "thread.h"

HANDLE g_hSema = 0;//�ź������
DWORD CALLBACK TestProc(LPVOID pParam) {
	while (1) {
		WaitForSingleObject(g_hSema, INFINITE);//ûͨ��һ�Σ�����ֵ��һ
		printf("*********\n");
	}
}
void sema() {
	g_hSema = CreateSemaphore(NULL, 3, 10, NULL);//��ʼ����ֵΪ3�����10
	DWORD nID = 0;
	HANDLE hThread = CreateThread(NULL, 0, TestProc, NULL, 0, &nID);
	getchar();
	ReleaseSemaphore(g_hSema, 10, NULL);//��λ����ֵΪ10,���ó������ֵ��ֵ��������
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(g_hSema);
}
