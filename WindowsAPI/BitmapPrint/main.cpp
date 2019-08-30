#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("Neoking");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass; // 옵션 구조체
	g_hlnst = hInstance;

	WndClass.cbClsExtra = 0; // 화면 넘어올 때 메모리
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경화면
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 아이콘
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; // 프로시저 함수 포인터
	WndClass.lpszClassName = lpszClass; // 이름
	WndClass.lpszMenuName = NULL; // 메뉴
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass); // 클래스 등록

	// 클래스네임, 타이틀, 윈도우스타일, 창 시작 위치, 넓이, 높이, 계층구조, 메뉴, 인스턴스, 파라미터
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow); // 윈도우 출력

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

HDC hMemDC;
HBITMAP hBitMap;
HBITMAP hOldBitMap;

// 핸들, 메세지 타입, 파라미터
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int i = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		hMemDC = CreateCompatibleDC(hdc);
		hBitMap = LoadBitmap(g_hlnst, MAKEINTRESOURCE(IDB_BITMAP2));
		hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);


		ReleaseDC(hWnd, hdc);

		SetTimer(hWnd, 1, 1000, NULL);
		return 0;

	case WM_TIMER:
		
		if (i < 4)
		{
			hBitMap = LoadBitmap(g_hlnst, MAKEINTRESOURCE(IDB_BITMAP2 + i++));
			hOldBitMap = (HBITMAP)SelectObject(hMemDC, hBitMap);
			ReleaseDC(hWnd, hdc);
		}
		else if (i == 4)
		{
			i = 0;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		BitBlt(hdc, 200, 150, 400, 250, hMemDC, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:

		SelectObject(hMemDC, hOldBitMap);
		DeleteObject(hBitMap);
		DeleteDC(hMemDC);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}