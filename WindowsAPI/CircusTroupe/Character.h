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

class BitMap;
class Collision;

//enum CHARACTER_STATE
//{
//	STOP,
//	MOVE,
//	DIE,
//};

class Character : public SceneObject
{
private:
	int speed;
	bool isJump;
	Collision* collision;
	ANIM_STATE animState;
	MOVE_DIR moveDir;
	DWORD lastChangeTime;
	POINT jumpTargetPos;
	POINT landingPos;
	float jumpTime;
	float jumpHeight;
	float jumpPower;

	void SetDirecton(MOVE_DIR newDir);
	void UpdateAnim(MOVE_DIR dir);
	void SetJumpTargetPos();

public:
	Character();
	~Character();

	virtual void Init(POINT pos = { 0, 0 }, int spriteNum = 0) override;
	void Input(WPARAM wParam, KEY_STATE keyState);
	void SetSpeed(int newSpeed);
	void Jump();
	void ForceGravity();
};

