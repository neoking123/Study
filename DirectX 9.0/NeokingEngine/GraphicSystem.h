#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "System.h"
#include "..\..\Common\Macro.h"

class GraphicSystem : public System
{
private:
	LPDIRECT3D9 D3D = NULL;
	LPDIRECT3DDEVICE9 D3DDevice = NULL;

public:
	GraphicSystem();
	virtual ~GraphicSystem();

	HRESULT InitD3D(HWND hWnd);
	void Render();
	void Release();
};

