#include "CameraComponent.h"
#include "GameObject.h"
#include "CircusGame.h"

void CameraComponent::Init(HDC gameDC, SIZE screenSize)
{
	this->screenSize = screenSize;
	cameraDC = CreateCompatibleDC(gameDC);
	hBitMap = CreateCompatibleBitmap(gameDC, this->screenSize.cx, this->screenSize.cy);
	hOldBitMap = (HBITMAP)SelectObject(cameraDC, hBitMap);
}

void CameraComponent::InputDC(HDC gameDC, GameObject& cameraObject)
{
	//BitBlt(cameraDC, 0, 0, screenSize.cx, screenSize.cy, gameDC, 100, 100, SRCCOPY);
	BitBlt(cameraDC, 0, 0, screenSize.cx, screenSize.cy, gameDC, cameraObject.transform.position.x - (screenSize.cx / 2), cameraObject.transform.position.y - (screenSize.cy / 2), SRCCOPY);
}

HDC CameraComponent::GetCameraDC()
{
	return cameraDC;
}

SIZE CameraComponent::GetCameraScreen()
{
	return screenSize;
}

void CameraComponent::Release()
{
	SelectObject(cameraDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(cameraDC);
}
