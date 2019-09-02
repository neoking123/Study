#include <Windows.h>
#include "CardGame.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Setting(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("Card Game");

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // 메뉴
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
		hdc = GetDC(hWnd);
		CardGame::GetInstance()->Init(hWnd, hdc, g_hlnst);


		ReleaseDC(hWnd, hdc);
		return 0;
		
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_SETTING:
			DialogBox(g_hlnst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Setting);
			break;
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		CardGame::GetInstance()->Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		CardGame::GetInstance()->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}

INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM IParam)
{
	HWND hRadio;

	switch (message)
	{
	case WM_INITDIALOG:
		hRadio = GetDlgItem(hDlg, IDC_RADIO1);
		SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, IParam);
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
			{

			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
			{

			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
			{

			}
		}
		break;
	}

	return DefWindowProc(hDlg, message, wParam, IParam);
}