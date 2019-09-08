#pragma once
#include <Windows.h>
#include "GameObject.h"
#include "CameraComponent.h"

class Camera : public GameObject
{
private:
	CameraComponent camera;
	GameObject* target;
	int offsetX;
	int offsetY;
	
public:
	Camera();
	~Camera();

	void Init(HDC hdc, SIZE screenSize, int x, int y);
	void Update(HDC hdc);
	HDC GetDC();
	SIZE GetSize();
	void SetTarget(GameObject& target);
	void SyncPostionToTarget();
};

