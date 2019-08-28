#include "InputManager.h"
#include "TypingGame.h"

// �̱��� �ʱ�ȭ
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
	if (wParam == 0x08) // �齺���̽�
	{
		InputBackSpace();
	}
	else if (wParam == 0x0D) // ����
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
