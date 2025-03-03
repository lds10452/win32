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
	MoveToEx( hdc, 100,100, NULL );//设置绘制起始点
	LineTo( hdc, 300,300 );//内部实现了MoveToEx
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
	//添加位图资源（不需要代码）
	HBITMAP hBmp = LoadBitmap( g_hInstance, (CHAR*)IDB_BITMAP1);
	HDC hMemdc = CreateCompatibleDC( hdc );
	//创建一个内存DC，并构建一个虚拟区域，并且内存DC在虚拟区域中绘图
	HGDIOBJ nOldBmp = SelectObject( hMemdc, hBmp);
	//将位图数据送给内存DC，内存DC在虚拟区域中将位图绘制出来。
	BitBlt( hdc, 100 ,100, 48, 48, hMemdc, 0, 0, SRCCOPY );
	//将虚拟区域中绘制好的图像成像到窗口中
	StretchBlt( hdc, 200,200, 96, 96, hMemdc, 0, 0, 48, 48, SRCCOPY );
	//缩放成像
	SelectObject( hMemdc, nOldBmp );
	DeleteObject( hBmp );
	DeleteDC( hMemdc );
}
void OnPaint( HWND hWnd ){
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint( hWnd, &ps );

	HPEN hPen = CreatePen( PS_DASH, 1, RGB(255,0,0));//PS_SOLID，默认黑色实线笔
	HGDIOBJ nOldPen = SelectObject( hdc, hPen );//需要返回默认笔，后面替换回去用于删除自己创建的笔
	
//	HBRUSH hBrush = CreateSolidBrush( RGB(0,255,0) );//默认白色实心画刷
//	HBRUSH hBrush = CreateHatchBrush(HS_CROSS,RGB(0,255,0));
	HGDIOBJ hBrush = GetStockObject( NULL_BRUSH );//使用系统自带的透明刷
	HGDIOBJ nOldBrush = SelectObject( hdc, hBrush );

//	DrawPit( hdc );//绘制点
//	DrawLine( hdc );//绘制直线
//	DrawRect( hdc );//绘制矩形
//	DrawEll( hdc );//绘制圆形
	DrawBmp( hdc );//绘制位图

	SelectObject( hdc, nOldBrush );//恢复默认笔
//	DeleteObject( hBrush );

	SelectObject( hdc, nOldPen );
	DeleteObject( hPen );

	EndPaint( hWnd, &ps );
}
//窗口处理函数( 自定义，处理消息)
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
//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow){
	g_hInstance = hIns;
	//注册窗口类
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
	RegisterClass( &wc );//将以上所有赋值全部写入操作系统。
	//在内存创建窗口
	HWND hWnd = CreateWindowEx( 0, "Main", "window", WS_OVERLAPPEDWINDOW,
																	100, 100, 500, 500, NULL, NULL, hIns, NULL );
	//显示窗口
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );
	//消息循环
	MSG nMsg = { 0 };
	while( GetMessage(&nMsg,NULL,0,0) ){
		TranslateMessage( &nMsg );
		DispatchMessage( &nMsg );//将消息交给窗口处理函数来处理。
	}
	return 0;
}