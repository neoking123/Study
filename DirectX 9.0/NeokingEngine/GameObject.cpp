#include "GameObject.h"
#include "GraphicSystem.h"
#include "Macro.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::InitVB(CUSTOMVERTEX vertexes[], int size, int len)
{
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
