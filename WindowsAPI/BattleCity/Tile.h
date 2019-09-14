#pragma once
#include "GameObject.h"
#include "PhysicsComponent.h"

class Tile : public GameObject
{
public:
	PhysicsComponent phsics1;
	PhysicsComponent phsics2;
	PhysicsComponent phsics3;
	PhysicsComponent phsics4;

	int tileNum;

public:
	Tile();
	~Tile();

	virtual void Init(InputComponent* input, int x = 0, int y = 0, string tag = "") override;
	void Init(InputComponent* input, int x = 0, int y = 0, string tag = "", int tileNum = 47);
	virtual void Update(float elapseTime) override;
	virtual void Render(HDC hdc) override;
	virtual void SetPosition(int x, int y) override;
};

