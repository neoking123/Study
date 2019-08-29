#include "InputManager.h"
#include "TypingGame.h"

InputManager::InputManager()
{
	position.x = 0;
	position.y = 0;
	maxInputNum = 24;
}

InputManager::~InputManager()
{
}

void InputManager::Input(WPARAM wParam)
{
	//(TCHAR)wParam == '\b'
	if (wParam == 0x08) // 백스페이스
	{
		InputBackSpace();
	}
	else if (wParam == 0x0D) // 엔터
	{
		TypingGame::GetInstance()->CheckString();
	}
	else
	{
		if (inputString.length() < maxInputNum)
		{
			inputString += wParam;
		}
	}
}

void InputManager::PrintInputString(HDC hdc)
{
	HFONT myFont = CreateFont(24, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, (LPCWSTR)"궁서체");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

	TCHAR sz[256];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, inputString.c_str(), -1, sz, 256);
	TextOut(hdc, position.x, position.y, sz, lstrlen(sz));

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void InputManager::InputBackSpace()
{
	if (!inputString.empty())
	{
		inputString.erase(inputString.end() - 1);
	}
}

void InputManager::ClearInputString()
{
	inputString.clear();
}

void InputManager::DrawInputBox(HDC hdc)
{
	Rectangle(hdc, position.x - 10, position.y - 10, position.x + 200, position.y + 30);
}

void InputManager::SetPosition(int _x, int _y)
{
	position.x = _x;
	position.y = _y;
}

string InputManager::GetInputString()
{
	return inputString;
}
