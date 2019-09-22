#pragma once
#include <Windows.h>
#include <string>
#include "TransformComponent.h"
using namespace std;

__interface UIObectInterface
{
	void Init(int x = 0, int y = 0);
	void Update();
	void Render(HDC hdc);
	void Release();
};

class UIObject abstract : public UIObectInterface
{
public:
	TransformComponent transform;
	string tag;
	virtual ~UIObject() {};
};