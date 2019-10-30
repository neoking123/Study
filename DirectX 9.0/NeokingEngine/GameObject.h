#pragma once
#include <string>
#include "3DBase.h"
using namespace std;

class GameObject
{
public:
	D3DXVECTOR3		vPos;			// 물체의 현재 위치
protected:
	D3DXVECTOR3		vLookat;		// 물체의 시선 위치
	D3DXVECTOR3		vUp;			// 물체의 상방벡터

	D3DXVECTOR3		vForward;		// 카메라가 향하는 단위방향벡터
	D3DXVECTOR3		vCross;			// 카마레의 측면벡터 cross( view, up )

	D3DXMATRIXA16	matScale;		// 물체 크기 행렬
	D3DXMATRIXA16	matTrans;		// 물체 위치 행렬
	D3DXMATRIXA16	matRotation;	// 물체 회전 행렬

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

	virtual void Init();
	void InitVB(CUSTOMVERTEX vertexes[], int size, int len);
	void InitIB(CUSTOMINDEX indexes[], int size, int len);
	void InitGeometry(string fileName);
	virtual void Release();

	virtual D3DXMATRIXA16*	SetPos(D3DXVECTOR3* vPos, D3DXVECTOR3* vLookat, D3DXVECTOR3* vUp);
	virtual void			MoveLocalX(float dist);
	virtual	void			MoveLocalY(float dist);
	virtual void			MoveLocalZ(float dist);

	D3DXMATRIXA16* GetMatTrans()
	{
		return &matTrans;
	}

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

