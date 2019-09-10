#pragma once
#include "InputComponent.h"

class GameObject;

class CursorInputComponent : public InputComponent
{
public:
	virtual void Update(GameObject& gameObject) override;
};

