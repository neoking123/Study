#include "InputSystem.h"
#include "WindowSystem.h"
#include "GraphicSystem.h"
#include "GameFrame.h"
#include "Camera.h"

InputSystem* InputSystem::instance = nullptr;

InputSystem::InputSystem()
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::Init()
{
	// 최초의 마우스 위치 보관
	POINT	pt;
	GetCursorPos(&pt);
	mouseX = pt.x;
	mouseY = pt.y;

	cameraMoveForce = 0.1f;
	moveForce = 0.1f;
}

void InputSystem::ProcessInput()
{
	ProcessMouse();
	ProcessKey();
}

void InputSystem::ProcessMouse()
{
	POINT	pt;
	float	fDelta = 0.0005f;	// 마우스의 민감도, 이 값이 커질수록 많이 움직인다.

	GetCursorPos(&pt);
	int dx = pt.x - mouseX;	// 마우스의 변화값
	int dy = pt.y - mouseY;	// 마우스의 변화값

	CAMERA->RotateLocalX(dy * fDelta);	// 마우스의 Y축 회전값은 3D world의  X축 회전값
	CAMERA->RotateLocalY(dx * fDelta);	// 마우스의 X축 회전값은 3D world의  Y축 회전값
	D3DXMATRIXA16*	pmatView = CAMERA->GetViewMatrix();		// 카메라 행렬을 얻는다.
	DXDEVICE->SetTransform(D3DTS_VIEW, pmatView);			// 카메라 행렬 셋팅


	// 마우스를 윈도우의 중앙으로 초기화
	SetCursor( NULL );	// 마우스를 나타나지 않게 않다.
	RECT	rc;
	GetClientRect(WINDOW_HANDLE, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(WINDOW_HANDLE, &pt);
	SetCursorPos(pt.x, pt.y);
	mouseX = pt.x;
	mouseY = pt.y;
}

void InputSystem::ProcessKey()
{
	if (KEYDOWN(VK_SHIFT))
	{
		moveForce = 0.5f;
		cameraMoveForce = 0.5f;
	}
		
	if (KEYUP(VK_SHIFT))
	{
		moveForce = 0.1f;
		cameraMoveForce = 0.1f;
	}

	//if (KEYDOWN(VK_ESCAPE))
	//	PostMessage(WINDOW_HANDLE, WM_DESTROY, 0, 0L);
	//if (KEYDOWN('1'))
	//	GRAPHIC_SYSTEM->bWireframe = !GRAPHIC_SYSTEM->bWireframe;

	if (KEYDOWN('W'))
		//CAMERA->MoveLocalZ(cameraMoveForce);	// 카메라 전진!
		GAME_FRAME->GetTank()->MoveLocalZ(moveForce);
	if (KEYDOWN('S'))
		//CAMERA->MoveLocalZ(-cameraMoveForce);	// 카메라 후진!
		GAME_FRAME->GetTank()->MoveLocalZ(-moveForce);
	if (KEYDOWN('A'))
		//CAMERA->MoveLocalX(-cameraMoveForce);	// 카메라 오른쪽 이동!
		GAME_FRAME->GetTank()->MoveLocalX(-moveForce);
	if (KEYDOWN('D'))
		//CAMERA->MoveLocalX(cameraMoveForce);	// 카메라 왼쪽 이동!
		GAME_FRAME->GetTank()->MoveLocalX(moveForce);

	if (KEYDOWN(VK_UP))
		CAMERA->MoveLocalZ(cameraMoveForce);	// 카메라 전진!
	if (KEYDOWN(VK_DOWN))
		CAMERA->MoveLocalZ(-cameraMoveForce);	// 카메라 후진!
	if (KEYDOWN(VK_RIGHT))
		CAMERA->MoveLocalX(cameraMoveForce);	// 카메라 오른쪽 이동!
	if (KEYDOWN(VK_LEFT))
		CAMERA->MoveLocalX(-cameraMoveForce);	// 카메라 왼쪽 이동!
	


}
