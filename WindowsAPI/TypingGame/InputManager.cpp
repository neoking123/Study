#include "InputManager.h"

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Input(WPARAM wParam)
{
	if ((TCHAR)wParam == '\b')
	{
		InputBackSpace();
	}
	else if ((TCHAR)wParam == '\n')
	{

	}
	else
	{
		inputString += wParam;
	}
}

void InputManager::PrintInputString(HDC hdc)
{
	TextOut(hdc, 300, 300, Utility::StringToTCHAR(inputString), inputString.length());
}

void InputManager::InputBackSpace()
{
	if (!inputString.empty())
	{
		inputString.erase(inputString.end() - 1);
	}
}

string InputManager::GetInputString()
{
	return inputString;
}
