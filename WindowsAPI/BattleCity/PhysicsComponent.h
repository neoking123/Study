#pragma once
#include <Windows.h>

class GameObject;

class PhysicsComponent
{
private:
	RECT colliderBox;
	SIZE colliderSize;
	
	void Move(GameObject& gameObject, float elapseTime);
	bool CheckBlockCollision(GameObject& gameObject);
	bool CheckTankCollision(GameObject& gameObject);

public:
	int left;
	int top;
	int right;
	int bottom;

public:
	void Update(GameObject& gameObject, float elapseTime);
	void SetColliderBox(SIZE boxSize);
	void SetColliderBox(GameObject& gameObject, SIZE boxSize, int left = 0, int top = 0, int right = 0, int bottom = 0);
	RECT GetColliderBox();
	SIZE GetColliderSize();
	void SyncClliderPos(GameObject& gameObject);
	void RenderColliderBox(HDC hdc);
};

