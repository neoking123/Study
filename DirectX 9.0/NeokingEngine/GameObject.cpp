#include "GameObject.h"
#include "GraphicSystem.h"
#include "Macro.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
	D3DXVECTOR3	pos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	lookat(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	up(0.0f, 1.0f, 0.0f);
	D3DXMatrixIdentity(&matTrans);
	SetPos(&pos, &lookat, &up);
}

void GameObject::InitVB(CUSTOMVERTEX vertexes[], int size, int len)
{
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matRotation);

	memcpy(this->vertexes, vertexes, size);

	DXDEVICE->CreateVertexBuffer(len * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vertextBuffer, NULL);

	void* pVertices;
	vertextBuffer->Lock(0, size, (void**)&pVertices, 0);

	memcpy(pVertices, vertexes, size);
	vertextBuffer->Unlock();
}

void GameObject::InitIB(CUSTOMINDEX indexes[], int size, int len)
{
	memcpy(this->indexes, indexes, size);

	DXDEVICE->CreateIndexBuffer(len * sizeof(CUSTOMINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL);

	void* pIndices;
	indexBuffer->Lock(0, size, (void**)&pIndices, 0);

	memcpy(pIndices, indexes, size);
	indexBuffer->Unlock();
}

void GameObject::InitGeometry(string fileName)
{
	LPD3DXBUFFER pD3dXMtrlBuffer;

	D3DXLoadMeshFromXA(fileName.c_str(), D3DXMESH_SYSTEMMEM, DXDEVICE, NULL, &pD3dXMtrlBuffer, NULL, &numMaterials, &mesh);

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3dXMtrlBuffer->GetBufferPointer();
	meshMaterials = new D3DMATERIAL9[numMaterials];
	meshTextures = new LPDIRECT3DTEXTURE9[numMaterials];

	for (int i = 0; i < numMaterials; i++)
	{
		meshMaterials[i] = d3dxMaterials[i].MatD3D;
		meshMaterials[i].Ambient = meshMaterials[i].Diffuse;
		meshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFile(DXDEVICE, d3dxMaterials[i].pTextureFilename, &meshTextures[i]);
		}
	}
	pD3dXMtrlBuffer->Release();
}

void GameObject::Release()
{
	SAFE_DELETE_ARRAY(meshMaterials);
	if (meshTextures)
	{
		for (int i = 0; i < numMaterials; i++)
		{
			SAFE_RELEASE(meshTextures[i]);
		}
	}

	SAFE_RELEASE(mesh);
}

D3DXMATRIXA16 * GameObject::SetPos(D3DXVECTOR3 * vPos, D3DXVECTOR3 * vLookat, D3DXVECTOR3 * vUp)
{
	this->vPos = *vPos;
	this->vLookat = *vLookat;
	this->vUp = *vUp;
	D3DXVec3Normalize(&vForward, &(this->vLookat - this->vPos));
	D3DXVec3Cross(&vCross, &this->vUp, &vForward);

	D3DXMatrixLookAtLH(&matTrans, &this->vPos, &this->vLookat, &this->vUp);

	D3DXMATRIXA16 matMove;
	D3DXMatrixTranslation(&matMove, this->vPos.x, this->vPos.y, this->vPos.z);
	matTrans = matMove;
	DXDEVICE->SetTransform(D3DTS_WORLD, &matTrans);

	/*D3DXMatrixInverse(&matBill, NULL, &matView);
	matBill._41 = 0.0f;
	matBill._42 = 0.0f;
	matBill._43 = 0.0f;*/

	return &matTrans;
}

void GameObject::MoveLocalX(float dist)
{
	/*D3DXVECTOR3 vNewPos = vPos;
	D3DXVECTOR3 vNewLootat = vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &vCross);
	vMove *= dist;
	vNewPos += vMove;
	vNewLootat += vMove;

	return SetPos(&vNewPos, &vNewLootat, &vUp);*/

	vPos.x += 1.0f * dist;

	D3DXMATRIXA16 matMove;
	D3DXMatrixTranslation(&matMove, vPos.x, vPos.y, vPos.z);

	matTrans = matMove;
	DXDEVICE->SetTransform(D3DTS_WORLD, &matTrans);
}

void GameObject::MoveLocalY(float dist)
{
	/*D3DXVECTOR3 vNewPos = vPos;
	D3DXVECTOR3 vNewLootat = vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &vUp);
	vMove *= dist;
	vNewPos += vMove;
	vNewLootat += vMove;

	return SetPos(&vNewPos, &vNewLootat, &vUp);*/

	vPos.y += 1.0f * dist;

	D3DXMATRIXA16 matMove;
	D3DXMatrixTranslation(&matMove, vPos.x, vPos.y, vPos.z);

	matTrans = matMove;
	DXDEVICE->SetTransform(D3DTS_WORLD, &matTrans);
}

void GameObject::MoveLocalZ(float dist)
{
	/*D3DXVECTOR3 vNewPos = vPos;
	D3DXVECTOR3 vNewLootat = vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &vForward);
	vMove *= dist;
	vNewPos += vMove;
	vNewLootat += vMove;

	return SetPos(&vNewPos, &vNewLootat, &vUp);*/

	vPos.z += 1.0f * dist;

	D3DXMATRIXA16 matMove;
	D3DXMatrixTranslation(&matMove, vPos.x, vPos.y, vPos.z);

	matTrans = matMove;
	DXDEVICE->SetTransform(D3DTS_WORLD, &matTrans);
}
