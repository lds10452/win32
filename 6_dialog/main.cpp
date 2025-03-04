#include <windows.h>
#include "resource.h"

HINSTANCE g_hInstance = 0;
INT CALLBACK ModelDlgProc(HWND hwndlg, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_INITDIALOG://对话框创建之后，显示之前的消息，不进入WM_CREATE消息
		MessageBox(hwndlg, "model WM_INITDIALOG", "Infor", MB_OK);
		break;
	case WM_CREATE:
		MessageBox(hwndlg, "WM_CREATE", "Infor", MB_OK);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			EndDialog(hwndlg, 100);//销毁模式对话框，函数DialogBox返回值为100
//			DestroyWindow( hwndlg );//销毁非模式对话框
		}
		break;
	}
	return FALSE;//将消息交给真正的对话框窗口处理函数的后续代码帮我们处理
}

INT CALLBACK NoModelDlgProc(HWND hwndlg, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_INITDIALOG://对话框创建之后，显示之前的消息，不进入WM_CREATE消息
		MessageBox(hwndlg, "WM_INITDIALOG", "Infor", MB_OK);
		break;
	case WM_CREATE:
		MessageBox(hwndlg, "WM_CREATE", "Infor", MB_OK);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
//			EndDialog(hwndlg, 100);//销毁模式对话框，函数DialogBox返回值为100
			DestroyWindow( hwndlg );//销毁非模式对话框
		}
		break;
	}
	return FALSE;//将消息交给真正的对话框窗口处理函数的后续代码帮我们处理
}

void OnCommand(HWND hWnd, WPARAM wParam) {
	switch (LOWORD(wParam)) {
	case ID_MODEL://菜单项id，模态对话框
	{
		int nRet = DialogBox(g_hInstance, (char*)IDD_DIALOG1, hWnd, (DLGPROC)ModelDlgProc);
		if (nRet == 100)//EndDialog函数第二个参数值
			MessageBox(hWnd, "successful", "Infor", MB_OK);
	}
	break;
	case ID_NOMODEL://菜单项id
	{
		HWND wnd= CreateDialog(g_hInstance, (char*)IDD_DIALOG1, hWnd, (DLGPROC)NoModelDlgProc);
		ShowWindow(wnd, SW_SHOW);
	}
	break;
	}
}
//窗口处理函数( 自定义，处理消息)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}
//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow) {
	g_hInstance = hIns;
	//注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = (char*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将以上所有赋值全部写入操作系统。
	//在内存创建窗口
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hIns, NULL);
	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//将消息交给窗口处理函数来处理。
	}
	return 0;
}