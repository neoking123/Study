#include "Camera.h"

Camera* Camera::instacne = nullptr;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	D3DXVECTOR3	eye(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	lookat(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	up(0.0f, 1.0f, 0.0f);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matBill);
	SetView(&eye, &lookat, &up);
}

D3DXMATRIXA16 * Camera::SetView(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvLookat, D3DXVECTOR3 * pvUp)
{
	vEye = *pvEye;
	vLookat = *pvLookat;
	vUp = *pvUp;
	D3DXVec3Normalize(&vView, &(vLookat - vEye));
	D3DXVec3Cross(&vCross, &vUp, &vView);

	D3DXMatrixLookAtLH(&matView, &vEye, &vLookat, &vUp);
	D3DXMatrixInverse(&matBill, NULL, &matView);
	matBill._41 = 0.0f;
	matBill._42 = 0.0f;
	matBill._43 = 0.0f;

	return &matView;
}

D3DXMATRIXA16 * Camera::RotateLocalX(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &vCross, angle);

	D3DXVECTOR3 vNewDst, vNewUp;
	D3DXVec3TransformCoord(&vNewDst, &vView, &matRot);		// view * rot로 새로운 dst vector를 구한다.
	vNewDst += vEye;										// 실제 dst position =  eye Position + dst vector

	return SetView(&vEye, &vNewDst, &vUp);
}

D3DXMATRIXA16 * Camera::RotateLocalY(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &vUp, angle);

	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord(&vNewDst, &vView, &matRot);		// view * rot로 새로운 dst vector를 구한다.
	vNewDst += vEye;										// 실제 dst position =  eye Position + dst vector

	return SetView(&vEye, &vNewDst, &vUp);
}

D3DXMATRIXA16 * Camera::MoveTo(D3DXVECTOR3 * pv)
{
	D3DXVECTOR3	dv = *pv - vEye;
	vEye = *pv;
	vLookat += dv;
	return SetView(&vEye, &vLookat, &vUp);
}

D3DXMATRIXA16 * Camera::MoveLocalX(float dist)
{
	D3DXVECTOR3 vNewEye = vEye;
	D3DXVECTOR3 vNewDst = vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &vCross);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &vUp);
}

D3DXMATRIXA16 * Camera::MoveLocalY(float dist)
{
	D3DXVECTOR3 vNewEye = vEye;
	D3DXVECTOR3 vNewDst = vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &vUp);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &vUp);
}

D3DXMATRIXA16 * Camera::MoveLocalZ(float dist)
{
	D3DXVECTOR3 vNewEye = vEye;
	D3DXVECTOR3 vNewDst = vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &vView);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &vUp);
}
