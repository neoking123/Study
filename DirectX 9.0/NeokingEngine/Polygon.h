#pragma once
#include "3DBase.h"

namespace Object3D
{
	class Polygon
	{
	private:
		LPDIRECT3DVERTEXBUFFER9 vertextBuffer = NULL;
		LPDIRECT3DINDEXBUFFER9	indexBuffer = NULL;
		CUSTOMVERTEX vertexes[MAX_VB];
		CUSTOMINDEX indexes[MAX_IB];

	public:
		Polygon();
		~Polygon();

		void InitVB(CUSTOMVERTEX vertexes[], int size, int len);
		void InitIB(CUSTOMINDEX indexes[], int size, int len);

		LPDIRECT3DVERTEXBUFFER9 GetVB()
		{
			return vertextBuffer;
		}

		LPDIRECT3DINDEXBUFFER9 GetIB()
		{
			return indexBuffer;
		}
	};
}



