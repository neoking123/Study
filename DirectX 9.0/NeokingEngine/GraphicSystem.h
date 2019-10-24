#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "System.h"
#include "..\..\Common\Macro.h"

class GraphicSystem : public System
{
private:
	static GraphicSystem* instance;

	LPDIRECT3D9 D3D = NULL;
	LPDIRECT3DDEVICE9 D3DDevice = NULL;

	GraphicSystem();

public:
	virtual ~GraphicSystem();

	void InitD3D(HWND hWnd);
	void Render();
	void Release();
	void SetupMareices();

	LPDIRECT3DDEVICE9 GetDevice()
	{
		return D3DDevice;
	}

	static GraphicSystem* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GraphicSystem();
		}
		return instance;
	}

	static void FreeInstance()
	{
		if (instance != nullptr)
		{
			SAFE_DELETE(instance);
		}
	}
};

