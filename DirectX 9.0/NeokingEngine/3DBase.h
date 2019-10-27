#pragma once
#include <d3dx9.h>
#include "GlobalFunc.h"

#define USE_INDEX16
#define MAX_VB 1024
#define MAX_IB 1024

struct CUSTOMVERTEX
{
	D3DXVECTOR3	position;
	//D3DXVECTOR3	normal;
	//D3DXVECTOR3	texture;
	DWORD color;
};

//#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_DIFFUSE)
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CUSTOMINDEX
{
	WORD _0, _1, _2;
};

struct TERRAINVERTEX
{
	enum _FVF { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
};

struct TRIINDEX
{
#ifdef USE_INDEX16
	WORD _0, _1, _2;
#else
	DWORD	_0, _1, _2;
#endif
};