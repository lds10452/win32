#include"thread.h"
static int i = 0;
DWORD CALLBACK BaseProc(LPVOID pParam) {
	char* pszText = (char*)pParam;
	while (1) {
		printf("%s\n", pszText);
		Sleep(1000);

		if (i > 5)
		{
			break;
		}
	}
	return 0;
}
DWORD CALLBACK BaseProc2(LPVOID pParam) {
	char* pszText = (char*)pParam;
	while (1) {
		printf("%s\n", pszText);
		Sleep(1000);

		i++;
		if (i > 5)
		{
			//ExitThread(0);
			break;
		}
	}
	return 0;
}
void base() {
	DWORD nID = 0;
	const char* pszText = "*******";
	HANDLE hThread = CreateThread(NULL, 0, BaseProc, (void*)pszText, 0, &nID);//0���߳�ջ�ռ�1M�ֽڶ��롣0������ִ��

	const char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread(NULL, 0, BaseProc2, (void*)pszText2, 0, &nID);//�����̲߳�����
	getchar();//��ֹ��Ϊ���߳̽����������߳���Դ�����ն�δִ��,����WaitForSingleObject���

	//SuspendThread(hThread);//���������߳�
	//ResumeThread(hThread2);//�ָ��߳�ִ��

//	TerminateThread(hThread,0);
	WaitForSingleObject(hThread, INFINITE);//�ȴ��߳�ִ�����
	WaitForSingleObject(hThread2, INFINITE);//�ȴ��߳�ִ�����

	CloseHandle(hThread);
	CloseHandle(hThread2);
}