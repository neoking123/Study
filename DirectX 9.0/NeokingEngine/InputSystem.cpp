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
	// ������ ���콺 ��ġ ����
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
	float	fDelta = 0.0005f;	// ���콺�� �ΰ���, �� ���� Ŀ������ ���� �����δ�.

	GetCursorPos(&pt);
	int dx = pt.x - mouseX;	// ���콺�� ��ȭ��
	int dy = pt.y - mouseY;	// ���콺�� ��ȭ��

	CAMERA->RotateLocalX(dy * fDelta);	// ���콺�� Y�� ȸ������ 3D world��  X�� ȸ����
	CAMERA->RotateLocalY(dx * fDelta);	// ���콺�� X�� ȸ������ 3D world��  Y�� ȸ����
	D3DXMATRIXA16*	pmatView = CAMERA->GetViewMatrix();		// ī�޶� ����� ��´�.
	DXDEVICE->SetTransform(D3DTS_VIEW, pmatView);			// ī�޶� ��� ����


	// ���콺�� �������� �߾����� �ʱ�ȭ
	SetCursor( NULL );	// ���콺�� ��Ÿ���� �ʰ� �ʴ�.
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
		//CAMERA->MoveLocalZ(cameraMoveForce);	// ī�޶� ����!
		GAME_FRAME->GetTank()->MoveLocalZ(moveForce);
	if (KEYDOWN('S'))
		//CAMERA->MoveLocalZ(-cameraMoveForce);	// ī�޶� ����!
		GAME_FRAME->GetTank()->MoveLocalZ(-moveForce);
	if (KEYDOWN('A'))
		//CAMERA->MoveLocalX(-cameraMoveForce);	// ī�޶� ������ �̵�!
		GAME_FRAME->GetTank()->MoveLocalX(-moveForce);
	if (KEYDOWN('D'))
		//CAMERA->MoveLocalX(cameraMoveForce);	// ī�޶� ���� �̵�!
		GAME_FRAME->GetTank()->MoveLocalX(moveForce);

	if (KEYDOWN(VK_UP))
		CAMERA->MoveLocalZ(cameraMoveForce);	// ī�޶� ����!
	if (KEYDOWN(VK_DOWN))
		CAMERA->MoveLocalZ(-cameraMoveForce);	// ī�޶� ����!
	if (KEYDOWN(VK_RIGHT))
		CAMERA->MoveLocalX(cameraMoveForce);	// ī�޶� ������ �̵�!
	if (KEYDOWN(VK_LEFT))
		CAMERA->MoveLocalX(-cameraMoveForce);	// ī�޶� ���� �̵�!
	


}
