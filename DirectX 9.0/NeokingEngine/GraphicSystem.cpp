#include "GraphicSystem.h"
#include "GameFrame.h"

GraphicSystem* GraphicSystem::instance = nullptr;

GraphicSystem::GraphicSystem()
{
}


GraphicSystem::~GraphicSystem()
{
}

void GraphicSystem::InitD3D(HWND hWnd)
{
	D3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3DDevice);
	
	D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void GraphicSystem::Render()
{
	if (D3DDevice == NULL)
		return;

	D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(D3DDevice->BeginScene()))
	{
		SetupMareices();

		// Print
		GameFrame::GetInstance()->Render();

		D3DDevice->EndScene();
	}

	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void GraphicSystem::Release()
{
	SAFE_RELEASE(D3DDevice);
	SAFE_RELEASE(D3D);
}

void GraphicSystem::DrawMesh(LPDIRECT3DVERTEXBUFFER9 vertextBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, int vertexNum, int primeCount)
{
	//D3DXMATRIXA16 mat;
	//D3DXMatrixIdentity(&mat);
	//D3DDevice->SetTransform(D3DTS_WORLD, &mat);

	D3DDevice->SetStreamSource(0, vertextBuffer, 0, sizeof(CUSTOMVERTEX));
	D3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	D3DDevice->SetIndices(indexBuffer);
	D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNum, 0, primeCount);
	//D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void GraphicSystem::SetupMareices()
{
	D3DXMATRIXA16 matWorld;
	UINT iTime = timeGetTime() % 1000;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	D3DXMatrixRotationY(&matWorld, fAngle);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//wasd
	D3DXVECTOR3 vEyept(0.0f, 3.0f, -50.0f);
	D3DXVECTOR3 vLootatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyept, &vLootatPt, &vUpVec);
	D3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);

	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}