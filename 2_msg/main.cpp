#include <windows.h>
#include <stdio.h>
HANDLE g_hOutput = 0;//���ձ�׼������

#define WM_MYMESSAGE WM_USER+1001

void OnCreate(HWND hWnd, LPARAM lParam) {
	CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	char* pszText = (char*)pcs->lpCreateParams;
	MessageBox(NULL, pszText, "Infor", MB_OK);

	SendMessage(hWnd, WM_MYMESSAGE, 1, 2);

	CreateWindowEx(0, "EDIT", "hello", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 200, 200, hWnd, NULL, 0, NULL);
}
void OnSize(HWND hWnd, LPARAM lParam) {
	short nWidth = LOWORD(lParam);
	short nHight = HIWORD(lParam);
	char szText[256] = { 0 };
	sprintf(szText, "WM_SIZE����:%d,��:%d\n", nWidth, nHight);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnMyMessage(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char szText[256] = { 0 };
	sprintf(szText, "�Զ�����Ϣ������: wParam=%d,lParam=%d\n", wParam, lParam);
	MessageBox(hWnd, szText, "Infor", MB_OK);
}
//���ڴ�����( �Զ��壬������Ϣ)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_MYMESSAGE:
		OnMyMessage(hWnd, wParam, lParam);
		break;
	case WM_SIZE:
		OnSize(hWnd, lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd, lParam);
		break;
	case WM_DESTROY:
		//		PostQuitMessage( 0 );//����ʹGetMessage��������0
		PostMessage(hWnd, WM_QUIT, 0, 0);
		//		SendMessage( hWnd, WM_QUIT, 0, 0);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) {
			int nRet = MessageBox(hWnd, "�Ƿ��˳�", "Infor", MB_YESNO);
			if (nRet == IDYES) {
				//ʲô����д
			}
			else {
				return 0;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow) {
	AllocConsole();//����DOS����������ݵ��ն�
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
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
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//���������и�ֵȫ��д�����ϵͳ��
	//���ڴ洴������
	const char* pszText = "hello data";
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hIns, (void *)pszText);
	//��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//��Ϣѭ��
	MSG nMsg = { 0 };
	/*	while( GetMessage(&nMsg,NULL,0,0) ){
			TranslateMessage( &nMsg );
			DispatchMessage( &nMsg );//����Ϣ�������ڴ�����������
		}*/
	while (1) {
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE)) {
			//����Ϣ
			if (GetMessage(&nMsg, NULL, 0, 0)) {
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			}
			else {
				return 0;
			}
		}
		else {
			//���д���
			WriteConsole(g_hOutput, "OnIdle", strlen("OnIdle"), NULL, NULL);
		}
	}
	return 0;
}