#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

enum TANK_ANIM_STATE
{
	DOWN_00,
	DOWN_01,
	LEFT_00,
	LEFT_01,
	RIGHT_00,
	RIGHT_01,
	UP_00,
	UP_01
};

class Missile;

class Tank : public GameObject
{
private:
	PhysicsComponent phsics;
	vector<Missile*> missilePool;

public:
	Tank();
	~Tank();

	int speed;
	TANK_ANIM_STATE animState;
	DIRECTION fireDirection;

	virtual void Init(InputComponent* input, int x, int y, string tag) override;
	virtual void Update(float elapseTime) override;
	virtual void Render(HDC hdc) override;
	virtual void SetPosition(int x, int y) override;
	virtual void SetDirection(DIRECTION newDirection) override;

	void Release();
	void SetAnimState(TANK_ANIM_STATE newAnimState);
	void Fire();
};

