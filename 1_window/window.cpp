#include <windows.h>

//���ڴ�����( �Զ��壬������Ϣ)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam) {
	switch (msgID) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);//��������ϢĬ�ϴ���.
}
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow) {
	//ע�ᴰ����
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
	RegisterClass(&wc);//���������и�ֵȫ��д�����ϵͳ��
	//���ڴ洴������
	HWND hWnd = CreateWindowEx(0, "Main", "window", WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, NULL, NULL, hIns, NULL);

	//ע�ᴰ����
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
	RegisterClass(&wc);//���������и�ֵȫ��д�����ϵͳ��
	//�����Ӵ���
	HWND hChild1 = CreateWindowEx(0, "main", "c1", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		0, 0, 200, 200, hWnd, NULL, hIns, NULL);//ʹ��main�����ഴ�����ڡ��رոô��ڣ��������ֹ����Ϊ���յ���PostQuitMessage(0);
	HWND hChild2 = CreateWindowEx(0, "Child", "c2", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		200, 0, 200, 200, hWnd, NULL, hIns, NULL);//ʹ��child�����ഴ������
	HWND hChild3 = CreateWindowEx(0, "Edit", "c3", WS_CHILD  | WS_OVERLAPPEDWINDOW,
		200, 200, 200, 200, hWnd, NULL, hIns, NULL);//ʹ��ϵͳ�Դ�Edit�����ഴ������

	//��ʾ����
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	ShowWindow(hChild3, SW_SHOW);//��������ʱʹ��WS_VISIBLE�����滻���д���
	UpdateWindow(hChild3);

	//��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0)) {//����Ϣʱ������
		TranslateMessage(&nMsg);//�����Ϣ�Ƿ��ǰ�������Ϣ��������ǰ�����Ϣ�������κδ�������ִ�С�
		DispatchMessage(&nMsg);//����Ϣ�������ڴ�����������
	}
	return 0;
}