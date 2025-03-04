#include <windows.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;
INT CALLBACK DlgProc(HWND hwndlg, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_INITDIALOG://�Ի��򴴽�֮����ʾ֮ǰ����Ϣ��������WM_CREATE��Ϣ
		MessageBox(hwndlg, "WM_INITDIALOG", "Infor", MB_OK);
		break;
	case WM_CREATE:
		MessageBox(hwndlg, "WM_CREATE", "Infor", MB_OK);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			EndDialog(hwndlg, 100);//����ģʽ�Ի��򣬺���DialogBox����ֵΪ100
//			DestroyWindow( hwndlg );//���ٷ�ģʽ�Ի���
		}
		break;
	}
	return FALSE;//����Ϣ���������ĶԻ��򴰿ڴ������ĺ�����������Ǵ���
}
void OnCommand(HWND hWnd, WPARAM wParam) {
	switch (LOWORD(wParam)) {
	case ID_MODEL://�˵���id
	{
		int nRet = DialogBox(g_hInstance, (char*)IDD_DIALOG1, hWnd, (DLGPROC)DlgProc);
		if (nRet == 100)//EndDialog�����ڶ�������ֵ
			MessageBox(hWnd, "successful", "Infor", MB_OK);
	}
	break;
	}
}
//���ڴ�����( �Զ��壬������Ϣ)
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
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow) {
	g_hInstance = hIns;
	//ע�ᴰ����
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
	RegisterClass(&wc);//���������и�ֵȫ��д�����ϵͳ��
	//���ڴ洴������
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hIns, NULL);
	//��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);//����Ϣ�������ڴ�����������
	}
	return 0;
}