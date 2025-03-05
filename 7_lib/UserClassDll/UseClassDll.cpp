#include <iostream>
using namespace std;
#include "../ClassDll/ClassDll.h"
#pragma comment( lib, "../Debug/ClassDll.lib" )
int main(){
	CMath math;
	int sum = math.Add(5,6);
	int sub = math.Sub(5,6);
	cout << "sum=" << sum << ",sub=" << sub << endl;
	return 0;
}