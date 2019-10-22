#include "CharacterPart.h"

CharacterPart::CharacterPart()
{
}


CharacterPart::~CharacterPart()
{
}

void CharacterPart::Init(CharacterPart* part, float x, float y, float z, float rX, float rY, float rZ)
{
	supperPart = part;
	D3DXMatrixTranslation(&matTranslation, x, y, z);

	if (rX != 0)
	{
		D3DXMatrixRotationX(&matRotation, rX);
	}

	if (rY != 0)
	{
		D3DXMatrixRotationY(&matRotation, rY);
	}

	if (rZ != 0)
	{
		D3DXMatrixRotationZ(&matRotation, rZ);
	}

	if (rX == 0 && rY == 0 && rZ == 0)
	{
		D3DXMatrixRotationY(&matRotation, 0.0f);
	}
}

void CharacterPart::DrawMesh(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, DWORD fvf, int size)
{
	D3DDevice->SetTransform(D3DTS_WORLD, &GetRotationTranslatation());
	D3DDevice->SetStreamSource(0, vertexBuffer, 0, size);
	D3DDevice->SetFVF(fvf);
	D3DDevice->SetIndices(indexBuffer);
	D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

D3DXMATRIXA16 CharacterPart::GetRotationTranslatation()
{
	D3DXMATRIXA16 mat;
	mat = matRotation * matTranslation;

	CharacterPart* tempSupper = supperPart;

	while (tempSupper)
	{
		mat = mat * tempSupper->matTranslation * tempSupper->matRotation;
		tempSupper = tempSupper->supperPart;
	}

	return mat;
}
