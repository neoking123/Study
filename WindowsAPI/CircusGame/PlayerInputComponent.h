#pragma once
#include "InputComponent.h"

class PlayerInputComponent : public InputComponent
{
public:
	virtual void Update(Character& character) override;
};
