#include <windows.h>
#include "resource.h"
HINSTANCE g_hInstance = 0;
void DrawPit( HDC hdc ){
//	SetPixel( hdc, 100, 100, RGB(255,0,0));
	for(int i=0; i<256; i++){
		for(int j=0; j<256; j++){
			SetPixel( hdc, i, j, RGB(i,j,0));
		}
	}
}
void DrawLine( HDC hdc ){
	MoveToEx( hdc, 100,100, NULL );//���û�����ʼ��
	LineTo( hdc, 300,300 );//�ڲ�ʵ����MoveToEx
//	MoveToEx(hdc, 300,300,NULL);
	LineTo(hdc, 0,300);
	LineTo(hdc, 100,100);
}
void DrawRect( HDC hdc ){
	Rectangle( hdc, 100, 100, 300, 300 );
}
void DrawEll( HDC hdc ){
	Ellipse( hdc, 100, 100, 300, 300 );
}
void DrawBmp( HDC hdc ){
	//���λͼ��Դ������Ҫ���룩
	HBITMAP hBmp = LoadBitmap( g_hInstance, (CHAR*)IDB_BITMAP1);
	//����һ���ڴ�DC��������һ���������򣬲����ڴ�DC�����������л�ͼ
	HDC hMemdc = CreateCompatibleDC( hdc );
	//��λͼ�����͸��ڴ�DC���ڴ�DC�����������н�λͼ���Ƴ�����
	HGDIOBJ nOldBmp = SelectObject( hMemdc, hBmp);
	//�����������л��ƺõ�ͼ����񵽴�����
	BitBlt( hdc, 100 ,100, 48, 48, hMemdc, 0, 0, SRCCOPY );
	//���ų���
	StretchBlt( hdc, 200,200, 96, 96, hMemdc, 0, 0, 48, 48, SRCCOPY );
	SelectObject( hMemdc, nOldBmp );
	DeleteObject( hBmp );
	DeleteDC( hMemdc );
}
void DrawBase(HDC hdc)
{
	HPEN hPen = CreatePen( PS_DASH, 1, RGB(255,0,0));//PS_SOLID��Ĭ�Ϻ�ɫʵ�߱�
	HGDIOBJ nOldPen = SelectObject( hdc, hPen );//��Ҫ����Ĭ�ϱʣ������滻��ȥ����ɾ���Լ������ı�
	
//	HBRUSH hBrush = CreateSolidBrush( RGB(0,255,0) );//Ĭ�ϰ�ɫʵ�Ļ�ˢ
//	HBRUSH hBrush = CreateHatchBrush(HS_CROSS,RGB(0,255,0));
	HGDIOBJ hBrush = GetStockObject( NULL_BRUSH );//ʹ��ϵͳ�Դ���͸��ˢ
	HGDIOBJ nOldBrush = SelectObject( hdc, hBrush );

//	DrawPit( hdc );//���Ƶ�
//	DrawLine( hdc );//����ֱ��
//	DrawRect( hdc );//���ƾ���
//	DrawEll( hdc );//����Բ��
	DrawBmp( hdc );//����λͼ

	SelectObject( hdc, nOldBrush );//�ָ�Ĭ�ϱ�
//	DeleteObject( hBrush );

	SelectObject( hdc, nOldPen );
	DeleteObject( hPen );
}
void DrawMyText(HDC hdc)
{
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 255, 0));//ֻ������OPAQUEģʽ
	SetBkMode(hdc, TRANSPARENT);
	HFONT hFont = CreateFont(30, 0, 45, 0, 900, 1, 1, 1, GB2312_CHARSET, 0, 0, 0, 0, "����");
	HGDIOBJ nOldFont = SelectObject(hdc, hFont);
	char szText[] = "hello txt";
	TextOut(hdc, 100, 100, szText, strlen(szText));

	RECT rc;
	rc.left = 100;
	rc.top = 150;
	rc.right = 200;
	rc.bottom = 200;
	//	Rectangle( hdc, 100, 150, 200, 200);
	DrawText(hdc, szText, strlen(szText), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
	//DT_VCENTER / DT_BOTTOM ֻ������ DT_SINGLELINE, �� DT_WORDBREAK(���У���ͻ

	SelectObject(hdc, nOldFont);
	DeleteObject(hFont);
}
void OnPaint( HWND hWnd ){
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint( hWnd, &ps );

//	DrawBase(hdc);//���ƻ���ͼ�Ρ�λͼ
	DrawMyText(hdc);//�����ı�

	EndPaint( hWnd, &ps );
}
//���ڴ�����( �Զ��壬������Ϣ)
LRESULT CALLBACK WndProc( HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam ){
	switch(msgID){
	case WM_PAINT:
		OnPaint( hWnd );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}
	return DefWindowProc( hWnd, msgID, wParam, lParam );
}
//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	g_hInstance = hIns;
	//ע�ᴰ����
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;/***********************************/
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "Main";/****************************/
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &wc );//���������и�ֵȫ��д�����ϵͳ��
	//���ڴ洴������
	HWND hWnd = CreateWindowEx( 0, "Main", "window", WS_OVERLAPPEDWINDOW,
																	100, 100, 500, 500, NULL, NULL, hIns, NULL );
	//��ʾ����
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
	//��Ϣѭ��
	MSG nMsg = { 0 };
	while( GetMessage(&nMsg,NULL,0,0) ){
		TranslateMessage( &nMsg );
		DispatchMessage( &nMsg );//����Ϣ�������ڴ�����������
	}
	return 0;
}