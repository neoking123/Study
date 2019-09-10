#pragma once
#include "GameObject.h"

class Cursor : public GameObject
{
public:
	Cursor();
	~Cursor();

	virtual void Init() override;
	virtual void Update() override;
};

