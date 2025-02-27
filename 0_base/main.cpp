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
	printf("单:%s\n", pszText);
#endif
}
void PrintUnicode() {
	const wchar_t* pszText = L"警方对抗赛录放机看大理寺风景点可罗斯福即可的松连脚裤";
	//char* pszText = "警方对抗赛录放机看大理寺风景点可罗斯福即可的松连脚裤";
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