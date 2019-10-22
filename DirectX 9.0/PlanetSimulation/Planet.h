#pragma once
#include <d3dx9.h>

class Planet
{
private:
	D3DXMATRIXA16	matTranslation;
	D3DXMATRIXA16	matRotation;

	float rotationTime;

public:
	Planet();
	~Planet();

	void Init(float x, float y, float z);
	void Rotate(int direction, float speed);
	D3DXMATRIXA16 MultiplyToRT(D3DXMATRIXA16 matrix);
	D3DXMATRIXA16 GetRotationTranslation();
	
	inline D3DXMATRIXA16 GetMatrixTranslation()
	{
		return matTranslation;
	}

	inline D3DXMATRIXA16 GetMatrixRotation()
	{
		return matRotation;
	}
};

