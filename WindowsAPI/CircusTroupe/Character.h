#pragma once
#include <Windows.h>
#include <vector>
#include "SceneObject.h"
using namespace std;

class BitMap;

enum CHARACTER_STATE
{
	STOP,
	MOVE,
	DIE,
};

class Character : public SceneObject
{
private:

public:
	Character();
	~Character();

	virtual void Init(int index, POINT pos = { 0, 0 }, int spriteNum = 0) override;
	void Input(WPARAM wParam);
};

