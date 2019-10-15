#pragma once
#include <string>
#include "TransformComponent.h"
#include "GraphicsComponent.h"
using namespace std;

__interface GameObjectInterface
{
	void Init();
	void Update();
};

class GameObject abstract : public GameObjectInterface
{
public:
	bool isActive = false;
	string tag;
	TransformComponent transform;
	GraphicsComponent graphics;

public:
	virtual ~GameObject() {};
};

