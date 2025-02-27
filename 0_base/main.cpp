//#define UNICODE
#include <Windows.h>
#include <stdio.h>
void C_char() {
	const char* pszText = "hello char";
	printf("%s\n", pszText);//strlen
}
void W_char() {
	const wchar_t* pszText = L"hello wchar";
	int len = wcslen(pszText);
	wprintf(L"%s %d\n", pszText, len);
}
void T_char() {
	const TCHAR* pszText = __TEXT("hello txt");//char* pszText = "hello txt"; / wchar_t* pszText = L"hello txt";
#ifdef UNICODE
	wprintf(L"%s\n", pszText);
#else
	printf("��:%s\n", pszText);
#endif
}
void PrintUnicode() {
	const wchar_t* pszText = L"�����Կ���¼�Ż��������·羰�����˹�����ɵ������ſ�";
	//char* pszText = "�����Կ���¼�Ż��������·羰�����˹�����ɵ������ſ�";
//	wprintf(L"%s\n", pszText);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(hOut, pszText, wcslen(pszText), NULL, NULL);
}
int main() {
	//	PrintUnicode();
	T_char();
	//	W_char();
	//	C_char();
	getchar();
	return 0;
}