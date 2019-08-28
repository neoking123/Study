#pragma once
#include "Utility.h"

class InputManager
{
private:
	string inputString;


public:
	InputManager();
	~InputManager();

	void Input(WPARAM wParam);
	void PrintInputString(HDC hdc);
	void InputBackSpace();
	string GetInputString();
};

