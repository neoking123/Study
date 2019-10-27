#pragma once
#include <string>
#include "3DBase.h"
using namespace std;

class GameObject
{
private:
	LPDIRECT3DVERTEXBUFFER9		vertextBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9		indexBuffer = NULL;
	CUSTOMVERTEX				vertexes[MAX_VB];
	CUSTOMINDEX					indexes[MAX_IB];

	LPD3DXMESH					mesh = NULL;
	D3DMATERIAL9*				meshMaterials = NULL;
	LPDIRECT3DTEXTURE9*			meshTextures = NULL;
	DWORD						numMaterials = 0;

public:
	GameObject();
	virtual ~GameObject();

	void InitVB(CUSTOMVERTEX vertexes[], int size, int len);
	void InitIB(CUSTOMINDEX indexes[], int size, int len);
	void InitGeometry(string fileName);
	void Release();

	LPDIRECT3DVERTEXBUFFER9 GetVB()
	{
		return vertextBuffer;
	}

	LPDIRECT3DINDEXBUFFER9 GetIB()
	{
		return indexBuffer;
	}

	LPD3DXMESH GetMesh()
	{
		return mesh;
	}

	D3DMATERIAL9* GetMeshMaterials()
	{
		return meshMaterials;
	}

	LPDIRECT3DTEXTURE9* GetMeshTextures()
	{
		return meshTextures;
	}

	DWORD GetNumMaterials()
	{
		return numMaterials;
	}
};

