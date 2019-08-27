#include <Windows.h>
#include <cmath>
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

#define PI 3.141592f

float DegreeToRadian(float degree)
{
	return (PI / 180) * degree;
}

// x y�� ���� xr x������ yr y������
void DrawCircle(HDC hdc, int x, int y, int xR, int yR)
{
	for (float i = 0.1f; i < 360.0f; i += 0.1f)
	{
		SetPixel(hdc, cosf(DegreeToRadian(i)) * xR + x, sinf(DegreeToRadian(i)) * yR + y, RGB(0, 0, 0));
	}
}


// �ڵ�, �޼��� Ÿ��, �Ķ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100, 100, 400, 300 };
	const TCHAR *str = TEXT("���� �����ϴ�.");

	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		/*MoveToEx(hdc, 50, 140, NULL);
		LineTo(hdc, 125, 100);
		Rectangle(hdc, 50, 100, 200, 180);
		Ellipse(hdc, 50, 100, 200, 180);*/
		DrawCircle(hdc, 500, 300, 400, 200);
		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}