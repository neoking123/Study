#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "System.h"
#include "Polygon.h"

#define	GRAPHIC_SYSTEM GraphicSystem::GetInstance()
#define	DXDEVICE GraphicSystem::GetInstance()->GetDevice()

class GraphicSystem : public System
{
private:
	static GraphicSystem* instance;

	LPDIRECT3D9 D3D = NULL;
	LPDIRECT3DDEVICE9 D3DDevice = NULL;

	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;

	GraphicSystem();

public:
	BOOL bWireframe = FALSE;	// 와이어프레임으로 그릴것인가?
	BOOL bHideFrustum = TRUE;	// Frustum을 안그릴 것인가?
	BOOL bLockFrustum = FALSE;	// Frustum을 고정할 것인가?

public:
	virtual ~GraphicSystem();

	void InitD3D(HWND hWnd);
	void InitMatrix();
	void Render();
	void Release();
	void DrawMesh(LPDIRECT3DVERTEXBUFFER9 vertextBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, int vertexNum, int primeCount);
	void DrawMesh(LPD3DXMESH mesh, D3DMATERIAL9* meshMaterials, LPDIRECT3DTEXTURE9* meshTextures, int numMaterials);
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

