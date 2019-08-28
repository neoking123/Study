#include "InputManager.h"
#include "TypingGame.h"

// 싱글톤 초기화
TypingGame* TypingGame::pInstance = nullptr;

InputManager::InputManager()
{
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
		inputString += wParam;
	}
}

void InputManager::PrintInputString(HDC hdc)
{
	TextOut(hdc, 800, 700, Utility::StringToTCHAR(inputString), inputString.length());
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

string* InputManager::GetInputString()
{
	return &inputString;
}
