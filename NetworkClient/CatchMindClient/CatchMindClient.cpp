/**
* @mainpage Catch Mind 클라이언트 매뉴얼
* @brief Catch Mind 클라이언트의 데이터 및 함수 설명
*/

#include "IOCompletionPort.h"
#include "ChattingManager.h"
#include "CatchMind.h"
#include "SketchBook.h"
#include <crtdbg.h>
using namespace std;

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_db(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void err_display(const char* msg);
void err_display(int errcode);
void err_quit(const char* msg);

HINSTANCE g_hInst;
HBRUSH hBrush = NULL;
HWND hChatCtrl = NULL;

char g_szClassName[256] = "CatchMindClient";
MOUSE_STATE mouseState = MOUSE_STATE::LCLICK_UP;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//메모리 릭
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(300);

	HWND hWnd;
	MSG Message;
	WNDCLASS wndClass;
	g_hInst = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_szClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// 게임 초기화
	CatchMind::GetInstance()->Init(hWnd, g_hInst);

	// IOCP 설정
	if (IOCompletionPort::GetInstance()->Init())
	{
		// IOCP 시작
		IOCompletionPort::GetInstance()->StartClient();
	}

	// 네트워크 초기화
	NetworkManager::GetInstance()->SetClientSocket(IOCompletionPort::GetInstance()->GetClientSocket());
	
	while (true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			CatchMind::GetInstance()->Update();
		}
	}
	//IOCompletionPort::FreeInstance();
	NetworkManager::GetInstance()->Release();
	NetworkManager::FreeInstance();
	CatchMind::GetInstance()->Release();
	CatchMind::FreeInstance();
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		CatchMind::GetInstance()->InitLogin();
		ChattingManager::GetInstance()->Init(hWnd, g_hInst);
		return 0;

	case WM_LBUTTONDOWN:
		CatchMind::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::LCLICK_DOWN);
		return 0;

	case WM_LBUTTONUP:
		CatchMind::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::LCLICK_UP);
		return 0;

	case WM_RBUTTONDOWN:
		CatchMind::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::RCLICK_DOWN);
		return 0;

	case WM_RBUTTONUP:
		CatchMind::GetInstance()->MouseInput(LOWORD(lParam), HIWORD(lParam), MOUSE_STATE::RCLICK_UP);
		return 0;

	case WM_MOUSEMOVE:
		if (SketchBook::GetInstance()->GetIsClicked())
		{
			SketchBook::GetInstance()->DrawToSketchBook(LOWORD(lParam), HIWORD(lParam));
		}
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 1280;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 995;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 1280;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 995;
		return 0;

	case WM_CTLCOLOREDIT:
		if ((HWND)lParam == ChattingManager::GetInstance()->hChat || (HWND)lParam == ChattingManager::GetInstance()->hChatList)
		{
			if (hBrush) { DeleteObject(hBrush); hBrush = NULL; }
			hBrush = CreateSolidBrush(RGB(0, 91, 184));
			SetBkColor((HDC)wParam, RGB(0, 91, 184));
			SetTextColor((HDC)wParam, RGB(255, 255, 255));
			return (LRESULT)hBrush;
		}
		return 0;

	case WM_DESTROY:
		DeleteObject(hBrush);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char*)IpMsgBuf);
	LocalFree(IpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(int errcode)
{
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	printf("[%s] %s", (char*)IpMsgBuf);
	LocalFree(IpMsgBuf);
}

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg)
{
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)IpMsgBuf, msg, MB_ICONERROR);
	LocalFree(IpMsgBuf);
	exit(1);
}
