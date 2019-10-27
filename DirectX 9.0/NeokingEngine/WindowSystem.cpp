#include "WindowSystem.h"
#include "GraphicSystem.h"
#include "InputSystem.h"
#include "GameFrame.h"

WindowSystem* WindowSystem::instance = nullptr;

WindowSystem::WindowSystem()
{
}

WindowSystem::~WindowSystem()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0L);
			break;
		case '1':
			GRAPHIC_SYSTEM->bWireframe = !GRAPHIC_SYSTEM->bWireframe;
			break;
		case '2':
			GRAPHIC_SYSTEM->bLockFrustum = !GRAPHIC_SYSTEM->bLockFrustum;
			GRAPHIC_SYSTEM->bHideFrustum = !GRAPHIC_SYSTEM->bHideFrustum;
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void WindowSystem::Init(HINSTANCE hInstance, const char* windowName)
{
	hWnd = NULL;
	this->hInstance = hInstance;
	exitState = 0;
	strcpy(this->windowName, windowName);

	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = this->windowName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
}

void WindowSystem::InitWindow()
{
	hWnd = CreateWindow(windowName, windowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

void WindowSystem::ProcessMessage()
{
	MSG message;

	while (true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			INPUT_SYSTEM->ProcessInput();
			GAME_FRAME->Update();
			GRAPHIC_SYSTEM->Render();
		}
	}
}
