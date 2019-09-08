#pragma once
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"

class InputComponent;

class Character : public GameObject
{
private:
	PhysicsComponent physics;
	GraphicsComponent graphics;
	InputComponent* input;

public:
	int direction;
	int speed;

public:
	Character();
	~Character();

	void Init(InputComponent* input, int x, int y);
	void Update(HDC hdc);
};

