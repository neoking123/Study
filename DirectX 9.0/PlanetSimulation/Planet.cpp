#include "Planet.h"

Planet::Planet()
{
}


Planet::~Planet()
{
}

void Planet::Init(float x, float y, float z)
{
	rotationTime = 0.0f;
	D3DXMatrixTranslation(&matTranslation, x, y, z);
	D3DXMatrixRotationY(&matRotation, 0.0f);
}

void Planet::Rotate(int direction, float speed)
{
	if (direction > 0)
	{
		rotationTime += 0.001f * speed;
		D3DXMatrixRotationY(&matRotation, rotationTime);
	}
	else if (direction < 0)
	{
		rotationTime -= 0.001f * speed;
		D3DXMatrixRotationY(&matRotation, rotationTime);
	}
	else
	{
		rotationTime = 0.0f;
		D3DXMatrixRotationY(&matRotation, rotationTime);
	}
}

D3DXMATRIXA16 Planet::MultiplyToRT(D3DXMATRIXA16 matrix)
{
	D3DXMATRIXA16 newMat;
	newMat = GetRotationTranslation();
	return newMat * matrix;
}

// SRT ¼ø¼­
D3DXMATRIXA16 Planet::GetRotationTranslation()
{
	return matRotation * matTranslation;
}