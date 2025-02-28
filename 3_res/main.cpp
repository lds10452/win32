#include <windows.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;

void OnCreate(HWND hWnd) {
	HMENU hMenu = LoadMenu(g_hInstance, (char*)IDR_MENU1);
	SetMenu(hWnd, hMenu);//��Ӳ˵���ʽ��
}
void OnCommand(HWND hWnd, WPARAM wParam) {
	switch (LOWORD(wParam)) {
	case ID_NEW:
		MessageBox(hWnd, "�½������", "Infor", MB_OK);
		break;
	case ID_EXIT:
		MessageBox(hWnd, "�˳������", "Infor", MB_OK);
		break;
	case ID_ABOUT:
		MessageBox(hWnd, "���ڱ����", "Infor", MB_OK);
		break;
	}
}
void OnContextMenu(HWND hWnd, LPARAM lParam) {
	HMENU hMain = LoadMenu(g_hInstance, (CHAR*)IDR_MENU1);
	HMENU hPopup = GetSubMenu(hMain, 0);
	TrackPopupMenu(hPopup, TPM_LEFTALIGN | TPM_TOPALIGN,
		LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_CONTEXTMENU:
		OnContextMenu(hWnd, lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);//�˵�������Ĵ���
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
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = NULL;//(char*)IDR_MENU1;//��Ӳ˵���ʽһ
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
		
//	HMENU hMenu = LoadMenu(g_hInstance, (char*)IDR_MENU1);//��Ӳ˵���ʽ��
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL/*hMenu*/, hIns, NULL);
	
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}
	return 0;
}