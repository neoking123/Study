#include <Windows.h>
#include "CardGame.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
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
	WndClass.lpszMenuName = NULL; // �޴�
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

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		CardGame::GetInstance()->Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}