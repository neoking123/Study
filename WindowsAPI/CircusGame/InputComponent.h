#pragma once
#include <Windows.h>
#include "Character.h"

__interface InputInterface
{
	void Update(Character& character);
};

class InputComponent abstract : public InputInterface
{
public:
	virtual ~InputComponent(){}
};

