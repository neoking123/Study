#include "InputManager.h"
#include "TypingGame.h"

// 싱글톤 초기화
TypingGame* TypingGame::pInstance = nullptr;

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
	TextOut(hdc, position.x, position.y, Utility::StringToTCHAR(inputString), inputString.length());
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
