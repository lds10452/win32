#include <windows.h>
#include <stdio.h>
HANDLE g_hOutput = 0;//接收标准输出句柄

#define WM_MYMESSAGE WM_USER+1001

void OnTimer(HWND hWnd, WPARAM wParam) {
/*	switch( wParam ){
	case 1:
		//.....
		break;
	case 2:
		//....
		break;
	}*/
	char szText[256] = { 0 };
	sprintf(szText, "WM_TIMER: 定时器ID=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);

	static unsigned short count = 0;
	if (count > 3)
	{
		KillTimer(hWnd, 1);//关闭定时器
		KillTimer(hWnd, 2);
	}
	count++;
}
void OnLButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONDOWN: 其他按键状态:%d, X=%d,Y=%d\n",
		wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char szText[256] = { 0 };
	sprintf(szText, "WM_LBUTTONUP: 其他按键状态:%d, X=%d,Y=%d\n",
		wParam, LOWORD(lParam), HIWORD(lParam));
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char szText[256] = { 0 };
	sprintf(szText, "WM_MOUSEMOVE: 其他按键状态:%d, X=%d,Y=%d\n",
		wParam, LOWORD(lParam), HIWORD(lParam));
	//	WriteConsole( g_hOutput, szText, strlen(szText), NULL, NULL );
}
void OnLButtonDblClk(HWND hWnd) {
	const char* szText = "WM_LBUTTONDBLCLK\n";
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnMouseWheel(HWND hWnd, WPARAM wParam) {
	short nDelta = HIWORD(wParam);//偏移量
	char szText[256] = { 0 };
	sprintf(szText, "WM_MOUSEWHEEL:nDetal=%d\n", nDelta);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnKeyDown(HWND hWnd, WPARAM wParam) {
	char szText[256] = { 0 };
	sprintf(szText, "WM_KEYDOWN: 键码值=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnKeyUp(HWND hWnd, WPARAM wParam) {
	char szText[256] = { 0 };
	sprintf(szText, "WM_KEYUP: 键码值=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnChar(HWND hWnd, WPARAM wParam) {
	char szText[256] = { 0 };
	sprintf(szText, "WM_CHAR: wParam=%d\n", wParam);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnPaint(HWND hWnd) {
	const char* pszText = "WM_PAINT\n";
	WriteConsole(g_hOutput, pszText, strlen(pszText), NULL, NULL);

	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint(hWnd, &ps);
	TextOut(hdc, 300, 300, "hello", 5);
	EndPaint(hWnd, &ps);
	//以上绘制图的代码，必须放在处理WM_PAINT消息时调用。
}
void OnCreate(HWND hWnd, LPARAM lParam) {
	CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
	char* pszText = (char*)pcs->lpCreateParams;
	MessageBox(NULL, pszText, "Infor", MB_OK);//显示CreateWindowEx函数最后一个参数的值

	CreateWindowEx(0, "EDIT", "hello", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 200, 200, hWnd, NULL, 0, NULL);//创建子窗口

	SendMessage(hWnd, WM_MYMESSAGE, 1, 2);//发送用户自定义消息，该消息不进入消息队列，会直接调用窗口处理函数处理，直到处理完成再返回
}
void OnSize(HWND hWnd, LPARAM lParam) {
	short nWidth = LOWORD(lParam);
	short nHight = HIWORD(lParam);
	char szText[256] = { 0 };
	sprintf(szText, "WM_SIZE：宽:%d,高:%d\n", nWidth, nHight);
	WriteConsole(g_hOutput, szText, strlen(szText), NULL, NULL);
}
void OnMyMessage(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	char szText[256] = { 0 };
	sprintf(szText, "自定义消息被处理: wParam=%d,lParam=%d\n", wParam, lParam);
	MessageBox(hWnd, szText, "Infor", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_TIMER://由GetMessage产生发送的队列消息。
		OnTimer(hWnd, wParam);
		break;
	case WM_MOUSEWHEEL:
		OnMouseWheel(hWnd, wParam);
		break;
	case WM_LBUTTONDBLCLK:
		OnLButtonDblClk(hWnd);
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(hWnd, wParam, lParam);
		InvalidateRect(hWnd, NULL, TRUE);//测试WM_PAINT消息
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(hWnd, wParam, lParam);
		break;
	case WM_CHAR://这个消息必定在按键按下之后产生，可见字符才会产生，大小写的值不同，TranslateMessage中发出的消息
		OnChar(hWnd, wParam);
		break;
	case WM_KEYDOWN:
		OnKeyDown(hWnd, wParam);
		break;
	case WM_KEYUP:
		OnKeyUp(hWnd, wParam);
		break;
	case WM_PAINT://1、ShowWindow发送的非队列消息。2、当窗口需要绘制的时候，由GetMessage产生发送的队列消息。
		OnPaint(hWnd);
		break;
	case WM_MYMESSAGE://用户自定义消息
		OnMyMessage(hWnd, wParam, lParam);
		break;
	case WM_SIZE:
		OnSize(hWnd, lParam);
		break;
	case WM_CREATE://窗口创建后，未显示之前产生，非队列消息
		OnCreate(hWnd, lParam);

		SetTimer(hWnd, 1, 1000, NULL);//创建并启动定时器，单位ms
		SetTimer(hWnd, 2, 2000, NULL);
		break;
	case WM_DESTROY:
		//		PostQuitMessage( 0 );//可以使GetMessage函数返回0
		PostMessage(hWnd, WM_QUIT, 0, 0);
		//		SendMessage( hWnd, WM_QUIT, 0, 0);
		break;
	case WM_SYSCOMMAND://窗口右上角放大缩小关闭按钮产生
		if (wParam == SC_CLOSE) {
			int nRet = MessageBox(hWnd, "是否退出", "Infor", MB_YESNO);
			if (nRet == IDYES) {
				//什么都不写
			}
			else {
				return 0;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow) {
	AllocConsole();//增加DOS用于输出内容到终端
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
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
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&wc);//将以上所有赋值全部写入操作系统。
	//在内存创建窗口
	const char* pszText = "hello data";
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hIns, (void *)pszText);
	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	//消息循环
	MSG nMsg = { 0 };
	/*	while( GetMessage(&nMsg,NULL,0,0) ){//时常阻塞，效率低
			TranslateMessage( &nMsg );
			DispatchMessage( &nMsg );//将消息交给窗口处理函数来处理。
		}*/
	while (1) {
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_NOREMOVE)) {
			//有消息
			if (GetMessage(&nMsg, NULL, 0, 0)) {
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			}
			else {
				return 0;
			}
		}
		else {
			//空闲处理
			//WriteConsole(g_hOutput, "OnIdle", strlen("OnIdle"), NULL, NULL);
		}
	}
	return 0;
}