#pragma once
#include "Tank.h"

class Enemy : public Tank
{
public:
	Enemy();
	~Enemy();

	virtual void Init(InputComponent* input, int x, int y, string tag) override;
};

