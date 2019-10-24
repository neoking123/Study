#pragma once
#include "3DBase.h"

namespace Object3D
{
	class Polygon
	{
	private:
		LPDIRECT3DVERTEXBUFFER9	vertextBuffer;
		LPDIRECT3DINDEXBUFFER9	indexBuffer;
		CUSTOMVERTEX vertexes[MAX_VB];
		CUSTOMINDEX indexes[MAX_IB];

	public:
		Polygon();
		~Polygon();

		void InitVB(CUSTOMVERTEX vertexes[]);
		void InitIB(CUSTOMINDEX indexes[]);
	};
}



