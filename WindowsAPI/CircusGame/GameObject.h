#pragma once
#include "TransformComponent.h"
#include "GraphicsComponent.h"

class GameObject
{
public:
	bool isActive = false;
	TransformComponent transform;
	GraphicsComponent graphics;

public:
	GameObject();
	~GameObject();
};

