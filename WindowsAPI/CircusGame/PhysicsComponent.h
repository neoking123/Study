#pragma once
#include <Windows.h>

class GameObject;
class Character;
class FireRing;

class PhysicsComponent
{
private:
	RECT colliderBox;
	SIZE colliderSize;
	int jumpTime = 0;

	void Move(Character& character);
	void Move(FireRing& fireRing);
	void Jump(Character& character);
	void CheckCollision(Character& character);

public:
	void Update(Character& character);
	void Update(FireRing& fireRing);
	void SetColliderBox(SIZE boxSize);
	void SetColliderBox(GameObject& gameObject, SIZE boxSize);
	RECT GetColliderBox();
	void SyncClliderPos(GameObject& gameObject);
	void SyncClliderPos(FireRing& fireRing);
};

