#include <Windows.h>
#include <stdio.h>
DWORD CALLBACK TestProc(LPVOID pParam) {
	char* pszText = (char*)pParam;
	while (1) {
		printf("%s\n", pszText);
		Sleep(1000);
	}
	return 0;
}
DWORD CALLBACK TestProc2(LPVOID pParam) {
	char* pszText = (char*)pParam;
	while (1) {
		printf("%s\n", pszText);
		Sleep(1000);
	}
	return 0;
}
int main() {
	DWORD nID = 0;
	const char* pszText = "*******";
	HANDLE hThread = CreateThread(NULL, 0, TestProc, (void*)pszText, 0, &nID);//0���߳�ջ�ռ�1M�ֽڶ��롣0������ִ��

//	WaitForSingleObject(hThread, INFINITE);//�ȴ��߳�ִ�����

	const char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, (void*)pszText2, 0, &nID);
	getchar();//��ֹ��Ϊ���߳̽����������߳���Դ�����ն�δִ��,����WaitForSingleObject���
	SuspendThread(hThread);//���������߳�
	ResumeThread(hThread2);//�ָ��߳�ִ��
	getchar();
	return 0;
}