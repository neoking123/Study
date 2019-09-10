#pragma once
#include <Windows.h>
#include "GameObject.h"

__interface InputInterface
{
	void Update(GameObject& gameObject);
};

class InputComponent abstract : public InputInterface
{
public:
	virtual ~InputComponent(){}
};

