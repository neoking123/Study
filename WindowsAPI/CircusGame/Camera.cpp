#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(HDC hdc, SIZE screenSize, int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
	offsetX = 0;
	offsetY = 0;
	camera.Init(hdc, screenSize);
}

void Camera::Update(HDC hdc)
{
	camera.InputDC(hdc, *this);

	if (target->transform.position.x < 4000)
	{
		SyncPostionToTarget();
	}
}

HDC Camera::GetDC()
{
	return camera.GetCameraDC();
}

SIZE Camera::GetSize()
{
	return camera.GetCameraScreen();
}

void Camera::SetTarget(GameObject & target)
{
	this->target = &target;
	offsetX = target.transform.position.x - transform.position.x;
	//offsetY = target.transform.position.y - transform.position.y;
}

void Camera::SyncPostionToTarget()
{
	transform.position.x = target->transform.position.x - offsetX;
	//transform.position.y = target->transform.position.y + offsetY;
}
