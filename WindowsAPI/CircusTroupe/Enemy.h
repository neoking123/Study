#pragma once
#include "SceneObject.h"

class Enemy : public SceneObject
{
private:
	int speed;

public:
	Enemy();
	~Enemy();

	virtual void Init(POINT pos = { 0, 0 }, int spriteNum = 0) override;
	void Move();
};

