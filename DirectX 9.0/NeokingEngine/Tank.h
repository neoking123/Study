#pragma once
#include "GameObject.h"
class Tank : public GameObject
{
public:
	LPDIRECT3DVERTEXBUFFER9		cannonVB = NULL;
	LPDIRECT3DINDEXBUFFER9		cannonIB = NULL;
	CUSTOMVERTEX				cannonvertexes[MAX_VB];
	CUSTOMINDEX					cannonIndexes[MAX_IB];

	D3DXMATRIXA16				matCannonTrans;
	D3DXMATRIXA16				matCannonRotation;			// ���� ȸ�� ���
	D3DXVECTOR3					vCannonRotation;			// ������ ���� ȸ����

	LPD3DXMESH					testMesh = NULL;
	LPDIRECT3DTEXTURE9			testTexture = NULL;
	DWORD						numMaterials = NULL;

public:
	Tank();
	virtual ~Tank();

	virtual void Init();
	virtual void Release();
	void Update(float height);
	void Render();
	void RenderShader();
	void RotateCannonX(float angle);
	virtual D3DXMATRIXA16*	SetPos(D3DXVECTOR3* vPos, D3DXVECTOR3* vLookat, D3DXVECTOR3* vUp);
	virtual void			MoveLocalX(float dist);
	virtual	void			MoveLocalY(float dist);
	virtual void			MoveLocalZ(float dist);

	LPDIRECT3DTEXTURE9* GetTexture() { return &testTexture; }
};

// ��ü�̵� ���� ó��
// http://dolphin.ivyro.net/file/mathematics/tutorial18.html
