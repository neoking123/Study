#pragma once
#include <string>
#include <Windows.h>
#include "TransformComponent.h"
#include "GraphicsComponent.h"
using namespace std;

class InputComponent;

__interface GameObjectInterface
{
	void Init(InputComponent* input, int x = 0, int y = 0, string tag = "");
	void Update(float elapseTime);
	void Render(HDC hdc);
	void SetPosition(int x, int y);
};

/**
* @brief 게임 오브젝트 추상 클래스
* @author Dayeol Hyeon
*/

class GameObject abstract : public GameObjectInterface
{
public:
	bool isActive = false;
	string tag;
	TransformComponent transform;
	GraphicsComponent graphics;
	InputComponent* input;

public:
	virtual ~GameObject() {};
};

