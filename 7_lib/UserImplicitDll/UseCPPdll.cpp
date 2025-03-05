#include <iostream>
using namespace std;
//_declspec(dllimport) int CPPdll_add( int add1, int add2 );
//_declspec(dllimport) int CPPdll_sub( int sub1, int sub2 );
_declspec(dllimport) int CPPdll_mul( int mul1, int mul2 );
#pragma comment( lib, "../Debug/CPPdll.lib" )
//通知链接器到哪抓 编号 和  dll文件名（"CPPdll.dll"）
int main(){
//	int sum = CPPdll_add(5,4); // 0 "CPPdll.dll"
//	int sub = CPPdll_sub(5,4);  // 1 "CPPdll.dll"
	int mul = CPPdll_mul(5,4); // 2 "CPPdll.dll"
	cout /*<< "sum=" << sum << ",sub=" << sub << ",mul=" */<< mul << endl;
 	return 0;
}















