#pragma once
#include "Utility.h"

class InputManager
{
private:
	string inputString;
	Utility::Position position;
	int maxInputNum;

public:
	InputManager();
	~InputManager();

	void Input(WPARAM wParam);
	void PrintInputString(HDC hdc);
	void InputBackSpace();
	void ClearInputString();
	void DrawInputBox(HDC hdc);
	void SetPosition(int _x, int _y);
	string GetInputString();
};

