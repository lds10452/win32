//两种方式导出库，用于显示链接动态库时，填写加载函数名称时是否是原函数名
int CPPdll_add(int add1, int add2) {
	return add1 + add2;
}

int CPPdll_sub(int sub1, int sub2) {
	return sub1 - sub2;
}

_declspec(dllexport) int CPPdll_mul(int mul1, int mul2) {
	return mul1 * mul2;
}