#pragma once
#include "InputComponent.h"

class EnemyInputComponent : public InputComponent
{
private:
	int directionChangeCount = 0;
	int randomDirectionChangeDelayCount = 0;
	int randomDirection = 4;

public:
	virtual void Update(GameObject& gameObject) override;
};

