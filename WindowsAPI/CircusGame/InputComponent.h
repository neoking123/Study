#pragma once
#include <Windows.h>
#include "Character.h"

__interface InputInterface
{
	void Input(UINT iMessage, WPARAM wParam);
	void Update(Character& character);
};

class InputComponent abstract : public InputInterface
{
protected:
	WPARAM wParam;
	UINT iMessage;

public:
	virtual ~InputComponent(){}
};

