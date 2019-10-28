#pragma once
#include "GameObject.h"
class Tank : public GameObject
{
public:
	LPDIRECT3DVERTEXBUFFER9		cannonVB = NULL;
	LPDIRECT3DINDEXBUFFER9		cannonIB = NULL;
	CUSTOMVERTEX				cannonvertexes[MAX_VB];
	CUSTOMINDEX					cannonIndexes[MAX_IB];

public:
	Tank();
	virtual ~Tank();

	virtual void Init();
};

