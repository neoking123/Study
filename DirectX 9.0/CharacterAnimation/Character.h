#pragma once
#include <vector>
#include "CharacterPart.h"
using namespace std;

class Character
{
private:
	vector<CharacterPart*> characterParts;

public:
	Character();
	~Character();

	void Init();
	void DrawMesh(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, DWORD fvf, int size);
};

