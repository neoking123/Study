#pragma once
#include <Windows.h>

class GameObject;

class PhysicsComponent
{
private:
	RECT colliderBox;
	SIZE colliderSize;
	int left;
	int top;
	int right;
	int bottom;

	void Move(GameObject& gameObject, float elapseTime);
	void CheckBlockCollision(GameObject& gameObject);

public:
	void Update(GameObject& gameObject, float elapseTime);
	void SetColliderBox(SIZE boxSize);
	void SetColliderBox(GameObject& gameObject, SIZE boxSize, int left = 0, int top = 0, int right = 0, int bottom = 0);
	RECT GetColliderBox();
	void SyncClliderPos(GameObject& gameObject);
	void RenderColliderBox(HDC hdc);
};

