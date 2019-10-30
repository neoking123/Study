#include "Tank.h"
#include "GraphicSystem.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

void Tank::Init()
{
	testMesh = GRAPHIC_SYSTEM->LoadModel("Models\\Ezreal.X", numMaterials);
	testTexture = GRAPHIC_SYSTEM->LoadTexture("Ezreal.bmp");

	D3DXVECTOR3	pos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	lookat(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	up(0.0f, 1.0f, 0.0f);
	vCannonRotation = { 0.0f, 0.0f, 0.0f };
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matCannonTrans);
	D3DXMatrixIdentity(&matCannonRotation);
	SetPos(&pos, &lookat, &up);

	CUSTOMVERTEX vertices[] =
	{
		{ { -1 , 1 , 1 }, 0x09fb300 } ,
		{ { 1 , 1 , 1 },0x09fb300 } ,
		{ { 1 ,   1 ,  -1 }, 0x09fb300 },
		{ { -1 , 1 ,  -1 }, 0x09fb300 },

		{ { -1 , -1 , 1 }, 0x038610b } ,
		{ { 1 , -1 , 1 }, 0x038610b } ,
		{ { 1 , -1 ,  -1 }, 0x038610b },
		{ { -1 , -1 ,  -1 }, 0x038610b },
	};

	CUSTOMINDEX indeices[] =
	{
		{0,1,2},{0,2,3},//À­¸é
		{4,6,5},{4,7,6},//¾Æ·§¸é
		{0,3,7},{0,7,4},//¿Þ¸é
		{1,5,6},{1,6,2},//¿À¸¥¸é
		{3,2,6},{3,6,7},//¾Õ¸é
		{0,4,5},{0,5,1}//µÞ¸é
	};

	CUSTOMVERTEX cannonVertices[] =
	{
		{ { -0.125f , 1.5f , 2 }, 0x09fb300 } ,
		{ { 0.125f , 1.5f , 2 },0x09fb300 } ,
		{ { 0.125f ,   1.5f ,  0 }, 0x09fb300 },
		{ { -0.125f , 1.5f ,  0 }, 0x09fb300 },

		{ { -0.125f , 1 , 2 }, 0x038610b } ,
		{ { 0.125f , 1 , 2 }, 0x038610b } ,
		{ { 0.125f , 1 ,  0 }, 0x038610b },
		{ { -0.125f , 1 ,  0 }, 0x038610b },
	};

	InitVB(vertices, sizeof(vertices), 8);
	InitIB(indeices, sizeof(indeices), 12);

	memcpy(cannonvertexes, cannonVertices, sizeof(cannonVertices));
	DXDEVICE->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &cannonVB, NULL);

	void* pVertices;
	cannonVB->Lock(0, sizeof(cannonVertices), (void**)&pVertices, 0);
	memcpy(pVertices, cannonVertices, sizeof(cannonVertices));
	cannonVB->Unlock();

	memcpy(cannonIndexes, indeices, sizeof(indeices));
	DXDEVICE->CreateIndexBuffer(12 * sizeof(CUSTOMINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &cannonIB, NULL);

	void* pIndices;
	cannonIB->Lock(0, sizeof(indeices), (void**)&pIndices, 0);
	memcpy(pIndices, indexes, sizeof(indeices));
	cannonIB->Unlock();
}

void Tank::Release()
{
	SAFE_RELEASE(testMesh);
	SAFE_RELEASE(testTexture);
}

void Tank::Update(float height)
{
	vPos = { vPos.x, height, vPos.z };
	SetPos(&vPos, &vLookat, &vUp);
}

void Tank::Render()
{
	//GRAPHIC_SYSTEM->DrawMesh(&matTrans, vertextBuffer, indexBuffer, 8, 12);
	//GRAPHIC_SYSTEM->DrawMesh(&matCannonTrans, cannonVB, cannonIB, 8, 12);
}

void Tank::RenderShader()
{
	for (int i = 0; i < numMaterials; i++)
	{
		testMesh->DrawSubset(i);
	}
}

void Tank::RotateCannonX(float angle)
{
	//D3DXMATRIXA16 matRotate;

	D3DXMatrixRotationX(&matCannonRotation, angle);
	matCannonTrans = matCannonRotation * matCannonTrans;
	//D3DXMatrixTranslation(&matRotate, vCannonRotation.x, vCannonRotation.y, vCannonRotation.z);
	//matTrans = matRotate;
	//DXDEVICE->SetTransform(D3DTS_WORLD, &matTrans);
}

D3DXMATRIXA16 * Tank::SetPos(D3DXVECTOR3 * vPos, D3DXVECTOR3 * vLookat, D3DXVECTOR3 * vUp)
{
	GameObject::SetPos(vPos, vLookat, vUp);
	matCannonTrans = matTrans;

	return &matTrans;
}

void Tank::MoveLocalX(float dist)
{
	GameObject::MoveLocalX(dist);
	matCannonTrans = matTrans;
}

void Tank::MoveLocalY(float dist)
{
	GameObject::MoveLocalY(dist);
	matCannonTrans = matTrans;
}

void Tank::MoveLocalZ(float dist)
{
	GameObject::MoveLocalZ(dist);
	matCannonTrans = matTrans;
}
