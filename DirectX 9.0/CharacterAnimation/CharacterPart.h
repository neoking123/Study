#pragma once
#include "CharacterPartComponent.h"

class CharacterPart : public CharacterPartCompoenent
{
private:
	CharacterPart* supperPart;

public:
	CharacterPart();
	virtual ~CharacterPart();
	void Init(CharacterPart* part, float x = 0.0f, float y = 0.0f, float z = 0.0f, float rX = 0.0f, float rY = 0.0f, float rZ = 0.0f);
	void DrawMesh(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, DWORD fvf, int size);
	virtual D3DXMATRIXA16 GetRotationTranslatation();
};

