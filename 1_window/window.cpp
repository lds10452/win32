#include <windows.h>

//窗口处理函数( 自定义，处理消息)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);//给各种消息默认处理.
}
//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow) {
	//注册窗口类
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将以上所有赋值全部写入操作系统。
	//在内存创建窗口
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hIns, NULL);

	//注册窗口类
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = DefWindowProc;/***********************************/
	wc.lpszClassName = "Child";/****************************/
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将以上所有赋值全部写入操作系统。
	//创建子窗口
	HWND hChild1 = CreateWindowEx(0, "main", "c1", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		0, 0, 200, 200, hWnd, NULL, hIns, NULL);//使用main窗口类创建窗口。关闭该窗口，程序会终止，因为最终调了PostQuitMessage(0);
	HWND hChild2 = CreateWindowEx(0, "Child", "c2", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		200, 0, 200, 200, hWnd, NULL, hIns, NULL);//使用child窗口类创建窗口
	HWND hChild3 = CreateWindowEx(0, "Edit", "c3", WS_CHILD  | WS_OVERLAPPEDWINDOW,
		200, 200, 200, 200, hWnd, NULL, hIns, NULL);//使用系统自带Edit窗口类创建窗口

	//显示窗口
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	ShowWindow(hChild3, SW_SHOW);//创建窗口时使用WS_VISIBLE风格可替换此行代码
	UpdateWindow(hChild3);

	//消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {//无消息时会阻塞
		TranslateMessage(&nMsg);//检查消息是否是按键的消息，如果不是按键消息，不做任何处理，继续执行。
		DispatchMessage(&nMsg);//将消息交给窗口处理函数来处理。
	}
	return 0;
}