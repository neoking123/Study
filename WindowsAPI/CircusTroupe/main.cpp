#include <Windows.h>
#include <vector>
#include "CircusTroupe.h"
#include "Utility.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("Circus Troupe");

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

// 핸들, 메세지 타입, 파라미터
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, nullptr);
		hdc = GetDC(hWnd);
		CircusTroupe::GetInstance()->Init(hWnd, hdc);
		

		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)IParam)->ptMaxTrackSize.x = 515;
		((MINMAXINFO*)IParam)->ptMaxTrackSize.y = 450;
		((MINMAXINFO*)IParam)->ptMinTrackSize.x = 515;
		((MINMAXINFO*)IParam)->ptMinTrackSize.y = 450;
		return 0;

	case WM_TIMER:
		CircusTroupe::GetInstance()->Update();
		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_KEYDOWN:
		CircusTroupe::GetInstance()->Input(wParam, KEY_STATE::BUTTONDOWN);
		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_KEYUP:
		CircusTroupe::GetInstance()->Input(wParam, KEY_STATE::BUTTONUP);
		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		CircusTroupe::GetInstance()->Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		CircusTroupe::GetInstance()->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}