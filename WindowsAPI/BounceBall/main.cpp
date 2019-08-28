#include <Windows.h>
#include <utility>
using namespace std;

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

// �ڵ�, �޼��� Ÿ��, �Ķ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static int radius = 50;
	static int radius2 = 30;
	static int speedX = 1;
	static int speedY = 1;
	static float distance;

	static pair<int, int> circle = { 500, 300 };
	static pair<int, int> userCircle = { 300, 400 };
	static pair<int, int> rect = { 500, 300 }; //100, 100, 1000, 600

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			userCircle.second -= 8;
			break;
		case VK_DOWN:
			userCircle.second += 8;
			break;
		case VK_LEFT:
			userCircle.first -= 8;
			break;
		case VK_RIGHT:
			userCircle.first += 8;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_CREATE:
		SetTimer(hWnd, 1, 10, NULL);
		return 0;
	case WM_TIMER:
		distance = sqrt(pow(userCircle.first - circle.first, 2) + pow(userCircle.second - circle.second, 2));
		if (distance <= radius + radius2)
		{
			KillTimer(hWnd, 1);
			MessageBox(hWnd, TEXT("�浹!"), TEXT("���"), MB_OK);
			SendMessage(hWnd, WM_DESTROY, 1, 0);
		}

		if (circle.first >= rect.first + 500 - radius)
		{
			speedX = -1;
			
		}
		else if (circle.first <= rect.first - 400 + radius)
		{
			speedX = 1;
		}
		circle.first += speedX;

		if (circle.second >= rect.second + 300 - radius)
		{
			speedY = -1;
		}
		if (circle.second <= rect.second - 200 + radius)
		{
			speedY = 1;
		}
		circle.second += speedY;
		
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Rectangle(hdc, rect.first - 400, rect.second - 200, rect.first + 500, rect.second + 300);
		Ellipse(hdc, circle.first - radius, circle.second - radius, circle.first + radius, circle.second + radius);
		Ellipse(hdc, userCircle.first - radius2, userCircle.second - radius2, userCircle.first + radius2, userCircle.second + radius2);

		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}