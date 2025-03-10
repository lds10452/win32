#include <windows.h>
#include "resource.h"
#include "resource1.h"

HINSTANCE g_hInstance = 0;

void OnCreate(HWND hWnd) {
	HMENU hMenu = LoadMenu(g_hInstance, (char*)IDR_MENU1);
	SetMenu(hWnd, hMenu);//添加菜单方式三
}
void OnCommand(HWND hWnd, WPARAM wParam) {
	switch (LOWORD(wParam)) {
	case ID_NEW:
	{
		if (HIWORD(wParam) == 0)
			MessageBox(hWnd, "新建菜单项被点击", "Infor", MB_OK);
		else if (HIWORD(wParam) == 1)
			MessageBox(hWnd, "CTRL+M被点击", "Infor", MB_OK);
	}
		break;
	case ID_EXIT:
		MessageBox(hWnd, "退出被点击", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, "关于被点击", "Infor", MB_OK);
		break;
	}
}
void OnContextMenu(HWND hWnd, LPARAM lParam) {
	HMENU hMain = LoadMenu(g_hInstance, (CHAR*)IDR_MENU1);
	HMENU hPopup = GetSubMenu(hMain, 0);
	TrackPopupMenu(hPopup, TPM_LEFTALIGN | TPM_TOPALIGN,//弹出上下文菜单
		LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_SETCURSOR:
	{
		HCURSOR hCursor = LoadCursor(g_hInstance, (char*)IDC_CURSOR2);
		if (LOWORD(lParam) == HTCAPTION)//标题栏使用这个光标
		{
			SetCursor(hCursor);//加载光标资源方式二
			return 0;//必须返回，否则会被默认处理函数覆盖导致使用默认光标
		}
	}
		break;
	case WM_CONTEXTMENU://在WM_RBUTTONUP消息之后产生。右键点击弹出
		OnContextMenu(hWnd, lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);//菜单项被点击后的处理
		break;
	case WM_CREATE:
		OnCreate(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow) {
	g_hInstance = hIns;
	
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(hIns,(char*)IDC_CURSOR1);//加载光标资源方式一，在默认处理函数中会自动设置，只作用于客户区
	wc.hIcon = LoadIcon(hIns, (char*)IDI_ICON1);//加载图标资源
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = NULL;//(char*)IDR_MENU1;//添加菜单方式一
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
		
//	HMENU hMenu = LoadMenu(g_hInstance, (char*)IDR_MENU1);//添加菜单方式二
	char strText[256] = { 0 };
	LoadString(hIns, IDS_WND, strText, 256);//添加字符串资源，可用于翻译，表中标题改一下，其他保持不变即可
	HWND hWnd = CreateWindowEx(0, "Main", strText, WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL/*hMenu*/, hIns, NULL);
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	HACCEL hAccel = LoadAccelerators(hIns, (char*)IDR_ACCELERATOR1);//添加加速键资源
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		if (!TranslateAccelerator(hWnd, hAccel, &nMsg))//如果在表中找到快捷键，内部会SendMessage发送WM_COMMAND消息，从而执行点击菜单项同样的功能
		{
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);
		}
	}
	return 0;
}