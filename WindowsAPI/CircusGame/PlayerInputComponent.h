#pragma once
#include "InputComponent.h"

class PlayerInputComponent : public InputComponent
{
public:
	virtual void Input(UINT iMessage, WPARAM wParam) override;
	virtual void Update(Character& character) override;
};
