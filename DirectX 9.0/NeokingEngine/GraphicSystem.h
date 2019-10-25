#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "System.h"
#include "Macro.h"
#include "Polygon.h"

#define	GRAPHIC_SYSTEM GraphicSystem::GetInstance()
#define	DXDEVICE GraphicSystem::GetInstance()->GetDevice()

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
	void DrawMesh(LPDIRECT3DVERTEXBUFFER9 vertextBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, int vertexNum, int primeCount);
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
		SAFE_DELETE(instance);
	}
};

