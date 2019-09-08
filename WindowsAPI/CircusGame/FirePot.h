#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

enum FIREPOT_ANIM_STATE
{
	FIREPOT_ANIM_STATE1,
	FIREPOT_ANIM_STATE2,
};

class FirePot : public GameObject
{
private:
	PhysicsComponent physics;

public:
	FIREPOT_ANIM_STATE animState;

public:
	FirePot();
	~FirePot();

	void Init(int x, int y);
	void Update(HDC hdc);
	void SetAnimState(FIREPOT_ANIM_STATE newState);
	RECT GetColliderBox();
};

