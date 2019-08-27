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

#define PI 3.141592f

float DegreeToRadian(float degree)
{
	return (PI / 180) * degree;
}

// x y의 중점 xr x반지름 yr y반지름
void DrawCircle(HDC hdc, int x, int y, int xR, int yR)
{
	for (float i = 0.1f; i < 360.0f; i += 0.1f)
	{
		SetPixel(hdc, cosf(DegreeToRadian(i)) * xR + x, sinf(DegreeToRadian(i)) * yR + y, RGB(0, 0, 0));
	}
}


// 핸들, 메세지 타입, 파라미터
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100, 100, 400, 300 };
	const TCHAR *str = TEXT("님은 갔습니다.");

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