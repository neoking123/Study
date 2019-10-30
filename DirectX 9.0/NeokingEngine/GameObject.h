#pragma once
#include <string>
#include "3DBase.h"
using namespace std;

class GameObject
{
public:
	D3DXVECTOR3		vPos;			// ��ü�� ���� ��ġ
protected:
	D3DXVECTOR3		vLookat;		// ��ü�� �ü� ��ġ
	D3DXVECTOR3		vUp;			// ��ü�� ��溤��

	D3DXVECTOR3		vForward;		// ī�޶� ���ϴ� �������⺤��
	D3DXVECTOR3		vCross;			// ī������ ���麤�� cross( view, up )

	D3DXMATRIXA16	matScale;		// ��ü ũ�� ���
	D3DXMATRIXA16	matTrans;		// ��ü ��ġ ���
	D3DXMATRIXA16	matRotation;	// ��ü ȸ�� ���

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

