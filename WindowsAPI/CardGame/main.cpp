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