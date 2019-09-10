#include <Windows.h>
#include <cstdio>
#include <crtdbg.h>
#include "resource.h"
#include "MapEditor.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hlnst;
LPCTSTR lpszClass = TEXT("Battle City MapEditor");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//메모리 릭 <crtdbg.h>
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(160);

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // 메뉴
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

// 핸들, 메세지 타입, 파라미터
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 24, 24, 24 + 416, 24 + 416 };
	OPENFILENAME OFN;
	char str[256];
	char lpstrFile[MAX_PATH] = "";

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		SetTimer(hWnd, 1, 10, nullptr);
		MapEditor::GetInstance()->Init(hdc, hWnd, g_hlnst, SIZE{ 416, 416 });
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)IParam)->ptMaxTrackSize.x = 1280;
		((MINMAXINFO*)IParam)->ptMaxTrackSize.y = 1024;
		((MINMAXINFO*)IParam)->ptMinTrackSize.x = 800;
		((MINMAXINFO*)IParam)->ptMinTrackSize.y = 600;
		return 0;

	case WM_LBUTTONDOWN:
		//MapEditor::GetInstance()->SetTile(LOWORD(IParam), HIWORD(IParam), 0);
		MapEditor::GetInstance()->CheckTilePosition(LOWORD(IParam), HIWORD(IParam));
		return 0;

	case WM_KEYDOWN:
		MapEditor::GetInstance()->Input(wParam);
		return 0;

	case WM_TIMER:
		MapEditor::GetInstance()->Update();
		InvalidateRect(hWnd, &rt, false);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MapEditor::GetInstance()->Draw(hdc);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_COMMAND:
		MapEditor::GetInstance()->PushButton(wParam);

		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
			return 0;

		case ID_FILE_OPEN:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.ini\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = "c:\\";
			if (GetOpenFileName(&OFN) != 0)
			{
				sprintf(str, "%s 파일을 열었습니다.", OFN.lpstrFile);
				MessageBox(hWnd, str, "파일 열기 성공", MB_OK);
			}
			return 0;

		case ID_FILE_SAVE:
			return 0;

		case ID_FILE_SAVEAS:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.ini\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = "c:\\";
			if (GetSaveFileName(&OFN) != 0)
			{
				sprintf(str, "%s 파일을 저장했습니다.", OFN.lpstrFile);
				MessageBox(hWnd, str, "파일 저장 성공", MB_OK);
			}
			return 0;

		case ID_FILE_EXIT:
			PostQuitMessage(0);
			return 0;
		}

		SetFocus(hWnd);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		MapEditor::GetInstance()->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}

HWND hOFN;

INT_PTR CALLBACK MainDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	OPENFILENAME OFN;
	char str[256];
	char lpstrFile[MAX_PATH] = "";

	//ZeroMemory(&OFN, sizeof(OPENFILENAME));
	/*memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "Every File(*.*)\n*.*\0Text File\0*.txt;*.ini\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = "c:\\";*/

	//GetOpenFileName
	/*if (GetSaveFileName(&OFN) != 0)
	{
		sprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
		MessageBox(hWnd, str, "파일 열기 성공", MB_OK);
	}*/

	switch (message)
	{
	case WM_INITDIALOG:
		hOFN = GetDlgItem(hWnd, ID_FILE_OPEN);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = "Every File(*.*)\n*.*\0Text File\0*.txt;*.ini\0";
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = "c:\\";
			EndDialog(hWnd, LOWORD(wParam));
		}
	}

	//return DefWindowProc(hDlg, message, wParam, IParam);
	return 0;
}