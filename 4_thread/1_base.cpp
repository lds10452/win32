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
	HANDLE hThread = CreateThread(NULL, 0, BaseProc, (void*)pszText, 0, &nID);//0：线程栈空间1M字节对齐。0：立即执行

	const char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread(NULL, 0, BaseProc2, (void*)pszText2, 0, &nID);//创建线程并启动
	getchar();//防止因为主线程结束导致子线程资源被回收而未执行,可用WaitForSingleObject替代

	//SuspendThread(hThread);//挂起休眠线程
	//ResumeThread(hThread2);//恢复线程执行

//	TerminateThread(hThread,0);
	WaitForSingleObject(hThread, INFINITE);//等待线程执行完成
	WaitForSingleObject(hThread2, INFINITE);//等待线程执行完成

	CloseHandle(hThread);
	CloseHandle(hThread2);
}