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
	HANDLE hThread = CreateThread(NULL, 0, TestProc, (void*)pszText, 0, &nID);//0：线程栈空间1M字节对齐。0：立即执行

//	WaitForSingleObject(hThread, INFINITE);//等待线程执行完成

	const char* pszText2 = "--------";
	HANDLE hThread2 = CreateThread(NULL, 0, TestProc2, (void*)pszText2, 0, &nID);
	getchar();//防止因为主线程结束导致子线程资源被回收而未执行,可用WaitForSingleObject替代
	SuspendThread(hThread);//挂起休眠线程
	ResumeThread(hThread2);//恢复线程执行
	getchar();
	return 0;
}