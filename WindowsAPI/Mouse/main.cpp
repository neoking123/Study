#include <Windows.h>
#include <vector>
#include <utility>
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
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
	static int x;
	static int y;
	static BOOL bNowDraw = FALSE;
	static vector<pair<int, int>, pair<int, int>> mouseTrack;
	mouseTrack.reserve(1000);

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		x = LOWORD(IParam);
		y = HIWORD(IParam);
		bNowDraw = TRUE;
		return 0;
	
	case WM_MOUSEMOVE:
		if (bNowDraw == TRUE)
		{
			hdc = GetDC(hWnd);
			MoveToEx(hdc, x, y, NULL);
			int prevX = x;
			int prevY = y;
			x = LOWORD(IParam);
			y = HIWORD(IParam);
			LineTo(hdc, x, y);
			mouseTrack.push_back(make_pair(prevX, prevY), make_pair(x, y));
			
			ReleaseDC(hWnd, hdc);
		}
		return 0;

	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;

	case WM_PAINT:
		

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}