#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("Neoking");

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

#define ID_EDIT 100
HWND hEdit;
// �ڵ�, �޼��� Ÿ��, �Ķ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	TCHAR str[128];

	switch (iMessage)
	{
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			10, 10, 200, 25, hWnd, (HMENU)ID_EDIT, g_hlnst, NULL);
		return 0;
		
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128);
				SetWindowText(hWnd, str);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}