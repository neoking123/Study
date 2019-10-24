#include "GraphicSystem.h"

GraphicSystem::GraphicSystem()
{
}


GraphicSystem::~GraphicSystem()
{
}

HRESULT GraphicSystem::InitD3D(HWND hWnd)
{
	D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (D3D == NULL)
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3DDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void GraphicSystem::Render()
{
	if (D3DDevice == NULL)
		return;

	D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(D3DDevice->BeginScene()))
	{
		// Print

		D3DDevice->EndScene();
	}

	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void GraphicSystem::Release()
{
	SAFE_RELEASE(D3DDevice);
	SAFE_RELEASE(D3D);
}
