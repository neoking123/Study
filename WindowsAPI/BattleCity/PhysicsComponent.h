#pragma once
#include <Windows.h>

class GameObject;

class PhysicsComponent
{
private:
	RECT colliderBox;
	SIZE colliderSize;

	void Move(GameObject& gameObject, float elapseTime);

public:
	void Update(GameObject& gameObject, float elapseTime);
	void SetColliderBox(SIZE boxSize);
	void SetColliderBox(GameObject& gameObject, SIZE boxSize);
	RECT GetColliderBox();
	void SyncClliderPos(GameObject& gameObject);
};

