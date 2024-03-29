#pragma once
#include "TypingGame.h"

TypingGame* TypingGame::pInstance = new TypingGame();

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("타자 게임");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass; // 옵션 구조체
	g_hlnst = hInstance;

	WndClass.cbClsExtra = 0; // 화면 넘어올 때 메모리
	WndClass.cbWndExtra = 0;
	//WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경화면
	WndClass.hbrBackground = CreateSolidBrush(RGB(255, 220, 220));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 아이콘
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; // 프로시저 함수 포인터
	WndClass.lpszClassName = lpszClass; // 이름
	WndClass.lpszMenuName = NULL; // 메뉴
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass); // 클래스 등록

	// 클래스네임, 타이틀, 윈도우스타일, 창 시작 위치, 넓이, 높이, 계층구조, 메뉴, 인스턴스, 파라미터
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1800, 1000,
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
		TypingGame::GetInstance()->Init(hWnd);
		SetTimer(hWnd, 1, TypingGame::GetInstance()->GetGameSpeed(), NULL);
		return 0;

	case WM_TIMER:
		TypingGame::GetInstance()->Update();
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_LBUTTONDOWN:
		TypingGame::GetInstance()->GetWordManager()->SpawnWord(LOWORD(IParam), HIWORD(IParam));
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_CHAR:
		TypingGame::GetInstance()->GetInputManager()->Input(wParam);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TypingGame::GetInstance()->Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)IParam)->ptMaxTrackSize.x = 1800;
		((MINMAXINFO*)IParam)->ptMaxTrackSize.y = 1000;
		((MINMAXINFO*)IParam)->ptMinTrackSize.x = 1800;
		((MINMAXINFO*)IParam)->ptMinTrackSize.y = 1000;

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}