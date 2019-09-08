#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

enum ANIM_STATE
{
	IDLE,
	BACKWARD,
	JUMP,
	DEAD,
	WIN_POSE,
	WIN_POSE2
};

class InputComponent;

class Character : public GameObject
{
private:
	PhysicsComponent physics;
	InputComponent* input;

public:
	int direction;
	int speed;
	int jumpPower;
	bool isJump;
	bool isDead;
	ANIM_STATE animState;

public:
	Character();
	~Character();

	void Init(InputComponent* input, int x, int y);
	void Update(HDC hdc);
	void SetAnimState(ANIM_STATE newState);
};

