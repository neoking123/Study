#pragma once
#include "Tank.h"

class Enemy : public Tank
{
public:
	Enemy();
	~Enemy();

	virtual void Init(InputComponent* input, int x, int y, string tag) override;
	virtual void Update(float elapseTime) override;
	virtual void Render(HDC hdc) override;
	virtual void SetPosition(int x, int y) override;
};

