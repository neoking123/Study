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

HDC g_MemDC[3];
HBITMAP g_hBitMap[3];
HBITMAP g_hOld[3];

// �ڵ�, �޼��� Ÿ��, �Ķ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static int x = 100;
	static int y = 100;

	switch (iMessage)
	{
	case WM_CREATE:
		//1. ����۴� CreateCompatibleBitmap ���� �����.
		//2. �ٸ� �̹����� ����� hdc�� �������� �����Ѵ�.
		//3. ��½� ����ۿ� ����ϰ� �������� hdc�� ����Ѵ�.
		// TransparentBlt(g_MemDC[0], 300, 300, 240, 192, g_MemDC[2], 0, 0, 240, 192, RGB(255, 0, 255));
		// msimg32.lib �ʿ���.

		SetTimer(hWnd, 1, 10, NULL);

		hdc = GetDC(hWnd);
		g_MemDC[0] = CreateCompatibleDC(hdc);
		g_hBitMap[0] = CreateCompatibleBitmap(hdc, 870, 512);
		g_hOld[0] = (HBITMAP)SelectObject(g_MemDC[0], g_hBitMap[0]);

		g_MemDC[1] = CreateCompatibleDC(hdc);
		g_hBitMap[1] = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[1] = (HBITMAP)SelectObject(g_MemDC[1], g_hBitMap[1]);

		g_MemDC[2] = CreateCompatibleDC(hdc);
		g_hBitMap[2] = (HBITMAP)LoadImage(NULL, "char.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		g_hOld[2] = (HBITMAP)SelectObject(g_MemDC[2], g_hBitMap[2]);

		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			x -= 8;
			break;
		case VK_RIGHT:
			x += 8;
			break;
		case VK_UP:
			y -= 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;

	case WM_TIMER:

		InvalidateRect(hWnd, NULL, false);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		BitBlt(g_MemDC[0], 0, 0, 1024, 768, g_MemDC[1], 0, 0, SRCCOPY);
		TransparentBlt(g_MemDC[0], x, y, 69, 70, g_MemDC[2], 0, 0, 69, 70, RGB(255, 0, 255));

		BitBlt(hdc, 0, 0, 1024, 768, g_MemDC[0], 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, NULL);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}