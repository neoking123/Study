#pragma once
#include "InputComponent.h"

class PlayerInputComponent : public InputComponent
{
public:
	virtual void Update(GameObject& gameObject) override;
};

