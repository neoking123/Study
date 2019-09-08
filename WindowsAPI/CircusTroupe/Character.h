#pragma once
#include <Windows.h>
#include <vector>
#include "SceneObject.h"
#include "Utility.h"
using namespace std;

enum MOVE_DIR
{
	STOP,
	FORWARD,
	BACKWORD,
	NONE,
};

enum ANIM_STATE
{
	CURRENT,
	IDLE,
	BACKWARD,
	JUMP,
	COLLISION,
	WIN_POSE,
	WIN_POSE2
};

class Collision;

class Character : public SceneObject
{
private:
	int speed;
	bool isJump;
	Collision* collision;
	ANIM_STATE animState;
	MOVE_DIR moveDir;
	DWORD lastChangeTime;
	int jumpSpeed;
	int jumpPower;
	int jumpAngle;
	bool isJumpUp;
	bool isJumpDown;
	
	void SetDirecton(MOVE_DIR newDir);
	void UpdateAnim(MOVE_DIR dir);

public:
	Character();
	~Character();

	virtual void Init(POINT pos = { 0, 0 }, int spriteNum = 0) override;
	void Input(WPARAM wParam, KEY_STATE keyState);
	void SetSpeed(int newSpeed);
	void Jump();
};

