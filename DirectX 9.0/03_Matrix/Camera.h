#pragma once
#include <d3dx9.h>
#include <Windows.h>

class Camera
{
private:
	D3DXVECTOR3 vEyept;
	D3DXVECTOR3 vLootatPt;
	D3DXVECTOR3 vUpVec;
	FLOAT fAngleX;
	FLOAT fAngleY;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;
	LPDIRECT3DDEVICE9 D3DDevice;
	D3DXMATRIXA16 matWorld;

	POINT prePos;

public:
	Camera();
	~Camera();

	void Init(LPDIRECT3DDEVICE9 D3DDevice);
	void View();
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Rotation(int x, int y);
	void RotationX(int y);
	void RotationY(int x);
};

