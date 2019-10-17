#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init(LPDIRECT3DDEVICE9 D3DDevice)
{
	this->D3DDevice = D3DDevice;
	vEyept = { 0.0f, 0.0f, -10.0f };
	vLootatPt = { 0.0f, 0.0f, 0.0f };
	vUpVec = { 0.0f, 1.0f, 0.0f };
	fAngleX = 0.0f;
	fAngleY = 0.0f;
	D3DXMatrixRotationX(&matWorld, fAngleX);
	D3DXMatrixRotationY(&matWorld, fAngleY);

	prePos;
	ZeroMemory(&prePos, sizeof(POINT));
}

void Camera::View()
{
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	D3DXMatrixLookAtLH(&matView, &vEyept, &vLootatPt, &vUpVec);
	D3DDevice->SetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void Camera::MoveUp()
{
	vEyept.y += 0.1f;
	vLootatPt.y += 0.1f;
}

void Camera::MoveDown()
{
	vEyept.y -= 0.1f;
	vLootatPt.y -= 0.1f;
}

void Camera::MoveRight()
{
	vEyept.x += 0.1f;
	vLootatPt.x += 0.1f;
}

void Camera::MoveLeft()
{
	vEyept.x -= 0.1f;
	vLootatPt.x -= 0.1f;
}

void Camera::Rotation(int x, int y)
{
	RotationX(x);
	RotationY(y);
	prePos = { x, y };
}

void Camera::RotationX(int y)
{
	if (prePos.x > y)
	{
		fAngleX -= y * 0.0001f;
	}
	else
	{
		fAngleX += y * 0.0001f;
	}
	
	D3DXMatrixRotationX(&matWorld, fAngleX);
}

void Camera::RotationY(int x)
{
	if (prePos.x > x)
	{
		fAngleY -= x * 0.0001f;
	}
	else
	{
		fAngleY += x * 0.0001f;
	}
	D3DXMatrixRotationY(&matWorld, fAngleY);
}
