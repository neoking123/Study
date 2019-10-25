#include "Polygon.h"
#include "GraphicSystem.h"
using namespace Object3D;

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}

void Polygon::InitVB(CUSTOMVERTEX vertexes[], int size, int len)
{
	memcpy(this->vertexes, vertexes, size);

	DXDEVICE->CreateVertexBuffer(len * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vertextBuffer, NULL);

	void* pVertices;
	vertextBuffer->Lock(0, size, (void**)&pVertices, 0);

	memcpy(pVertices, vertexes, size);
	vertextBuffer->Unlock();
}

void Polygon::InitIB(CUSTOMINDEX indexes[], int size, int len)
{
	memcpy(this->indexes, indexes, size);

	DXDEVICE->CreateIndexBuffer(len * sizeof(CUSTOMINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL);

	void* pIndices;
	indexBuffer->Lock(0, size, (void**)&pIndices, 0);

	memcpy(pIndices, indexes, size);
	indexBuffer->Unlock();
}
