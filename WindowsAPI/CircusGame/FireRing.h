#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

enum FIRE_ANIM_STATE
{
	ON,
	OFF
};

class FireRing : public GameObject
{
private:
	PhysicsComponent physics;

public:
	int speed;
	FIRE_ANIM_STATE animState;

public:
	FireRing();
	~FireRing();

	void Init(int x, int y);
	void Update(HDC hdc);
	void SetAnimState(FIRE_ANIM_STATE newState);
	void DrawBack(HDC hdc);
	RECT GetColliderBox();
};

