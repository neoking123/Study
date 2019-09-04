#include <Windows.h>
#include <crtdbg.h>
#include "MineSweeper.h"
#include "resource.h"

int WIDTH = 9;
int HEIGHT = 9;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Setting(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("Mine Sweeper");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//�޸� ��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(160);

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass; // �ɼ� ����ü
	g_hlnst = hInstance;

	WndClass.cbClsExtra = 0; // ȭ�� �Ѿ�� �� �޸�
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���ȭ��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ������
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc; // ���ν��� �Լ� ������
	WndClass.lpszClassName = lpszClass; // �̸�
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // �޴�
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass); // Ŭ���� ���

	// Ŭ��������, Ÿ��Ʋ, �����콺Ÿ��, â ���� ��ġ, ����, ����, ��������, �޴�, �ν��Ͻ�, �Ķ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow); // ������ ���

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

// �ڵ�, �޼��� Ÿ��, �Ķ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT pt;
	int clickButton = -1;

	switch (iMessage)
	{
	case WM_CREATE:
		srand(GetTickCount());
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 1000, NULL);
		MineSweeper::GetInstance()->Init(hdc, g_hlnst, hWnd);

		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 880;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 570;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 880;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 570;

		return 0;

	case WM_TIMER:
		MineSweeper::GetInstance()->Update();
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_LBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		clickButton = 0;
		MineSweeper::GetInstance()->Input(pt, clickButton);
		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_RBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		clickButton = 1;
		MineSweeper::GetInstance()->Input(pt, clickButton);
		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_LBUTTONUP:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		clickButton = 2;
		MineSweeper::GetInstance()->Input(pt, clickButton);
		InvalidateRect(hWnd, NULL, false);
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

		MineSweeper::GetInstance()->Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		MineSweeper::GetInstance()->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
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
				WIDTH = 9;
				HEIGHT = 9;
				MineSweeper::GetInstance()->ReInit(10);
				InvalidateRect(hDlg, NULL, true);
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
			{
				WIDTH = 16;
				HEIGHT = 16;
				MineSweeper::GetInstance()->ReInit(40);
				InvalidateRect(hDlg, NULL, true);
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
			{
				WIDTH = 30;
				HEIGHT = 16;
				MineSweeper::GetInstance()->ReInit(99);
				InvalidateRect(hDlg, NULL, true);
			}
			EndDialog(hDlg, LOWORD(wParam));
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}

	//return DefWindowProc(hDlg, message, wParam, IParam);
	return 0;
}