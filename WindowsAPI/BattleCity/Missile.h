#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

enum MISSILE_ANIM_STATE
{
	FIRE_LEFT,
	FIRE_UP,
	FIRE_RIGHT,
	FIRE_DOWN,
	BOMB_0,
	BOMB_1,
	BOMB_2,
	BOMB_START,
	NOT_FIRED
};

class Missile :public GameObject
{
public:
	int speed;
	bool isFired;
	bool isCollide;
	DIRECTION direction;
	MISSILE_ANIM_STATE animState;
	PhysicsComponent phsics;

public:
	Missile();
	~Missile();
	virtual void Init(InputComponent* input, int x = 0, int y = 0, string tag = "") override;
	virtual void Update(float elapseTime) override;
	virtual void Render(HDC hdc) override;
	virtual void SetPosition(int x, int y) override;
	void SetFirePosition(int x, int y);
	void SetDirection(DIRECTION newDirection);
	void SetSpeed(int newSpeed);
	void Reset();

	void SetAnimState(MISSILE_ANIM_STATE newAnimState);
	void CheckBoundary();
};

