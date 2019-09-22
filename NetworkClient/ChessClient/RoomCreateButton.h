#pragma once
#include "UIObject.h"
#include "ButtonComponent.h"

class RoomCreateButton : public UIObject
{
private:
	ButtonComponent button;

	void CheckIsCliked(int x, int y);

public:
	RoomCreateButton();
	~RoomCreateButton();

	virtual void Init(int x = 0, int y = 0) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

