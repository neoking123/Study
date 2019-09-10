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
	//�޸� �� <crtdbg.h>
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
	//_CrtSetBreakAlloc(160);

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // �޴�
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
		((MINMAXINFO*)IParam)->ptMaxTrackSize.x = 800;
		((MINMAXINFO*)IParam)->ptMaxTrackSize.y = 600;
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
			MapEditor::GetInstance()->MakeNew();
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
				sprintf(str, "%s ������ �������ϴ�.", OFN.lpstrFile);
				MapEditor::GetInstance()->Load(OFN.lpstrFile);
				MessageBox(hWnd, str, "���� ���� ����", MB_OK);
			}
			return 0;

		case ID_FILE_SAVE:
			if (MapEditor::GetInstance()->IsFileOpen())
			{
				MapEditor::GetInstance()->Save();
				return 0;
			}

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
				sprintf(str, "%s ������ �����߽��ϴ�.", OFN.lpstrFile);
				MapEditor::GetInstance()->SaveAs(OFN.lpstrFile);
				MessageBox(hWnd, str, "���� ���� ����", MB_OK);
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