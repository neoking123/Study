#include "Polygon.h"
#include "GraphicSystem.h"
using namespace Object3D;

Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}

void Polygon::InitVB(CUSTOMVERTEX vertexes[])
{
	memcpy(this->vertexes, vertexes, sizeof(vertexes));

	GraphicSystem::GetInstance()->GetDevice()->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &vertextBuffer, NULL);

	void* pVertices;
	vertextBuffer->Lock(0, sizeof(vertexes), (void**)&pVertices, 0);

	memcpy(pVertices, vertexes, sizeof(vertexes));
	vertextBuffer->Unlock();
}

void Polygon::InitIB(CUSTOMINDEX indexes[])
{
	memcpy(this->indexes, indexes, sizeof(indexes));

	GraphicSystem::GetInstance()->GetDevice()->CreateIndexBuffer(12 * sizeof(CUSTOMINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL);

	void* pIndices;
	indexBuffer->Lock(0, sizeof(indexes), (void**)&pIndices, 0);

	memcpy(pIndices, indexes, sizeof(indexes));
	indexBuffer->Unlock();
}
