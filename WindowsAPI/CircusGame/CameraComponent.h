#pragma once
#include <windows.h>

class GameObject;

class CameraComponent
{
public:
	HDC cameraDC;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;
	SIZE screenSize;

public:
	void Init(HDC gameDC, SIZE screenSize);
	void InputDC(HDC gameDC, GameObject& cameraObject);
	HDC GetCameraDC();
	SIZE GetCameraScreen();
	void Release();
};

