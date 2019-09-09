#pragma once
#include <string>
#include "TransformComponent.h"
#include "GraphicsComponent.h"
using namespace std;

class GameObject
{
public:
	bool isActive = false;
	string tag;
	TransformComponent transform;
	GraphicsComponent graphics;

public:
	GameObject();
	~GameObject();
};

