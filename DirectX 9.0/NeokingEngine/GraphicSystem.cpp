#include "GraphicSystem.h"
#include "GameFrame.h"
#include "Camera.h"

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

	// ���� ���� ����
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3DDevice);
	
	// �⺻�ø�, CCW
	D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// Z���۱���� �Ҵ�.
	D3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	//D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void GraphicSystem::InitMatrix()
{
	// ���� ��� ����
	D3DXMatrixIdentity(&matWorld);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// �� ����� ����
	D3DXVECTOR3 vEyePt(0.0f, 50.0f, -50.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	D3DDevice->SetTransform(D3DTS_VIEW, &matView);

	// ���� �������� ���
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	// �������� �ø��� �������� ���
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 200.0f);

	// ī�޶� �ʱ�ȭ
	CAMERA->Init();
	CAMERA->SetView(&vEyePt, &vLookatPt, &vUpVec);
}

void GraphicSystem::Render()
{
	if (D3DDevice == NULL)
		return;

	// �ĸ���ۿ� Z���� �ʱ�ȭ
	D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	D3DDevice->SetRenderState(D3DRS_FILLMODE, bWireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	SetupLight();

	D3DXMATRIXA16	m;
	D3DXMATRIXA16	*pView;
	pView = CAMERA->GetViewMatrix();	// ī�޶� Ŭ�����κ��� ��������� ��´�.
	m = *pView * matProj;				// World��ǥ�� ������ؼ� View * Proj����� ����Ѵ�.
	if (!bLockFrustum)
		FRUSTUM->Make(&m);				// View*Proj��ķ� Frustum�� �����.

	// ������ ����
	if (SUCCEEDED(D3DDevice->BeginScene()))
	{
		//SetupMareices();

		// Print
		GameFrame::GetInstance()->Render();

		// �������� �ø�
		if (!bHideFrustum)
			FRUSTUM->Draw(DXDEVICE);

		// ������ ����
		D3DDevice->EndScene();
	}

	// �ĸ���۸� ���̴� ȭ������!
	D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void GraphicSystem::Release()
{
	SAFE_RELEASE(D3DDevice);
	SAFE_RELEASE(D3D);
}

void GraphicSystem::DrawMesh(D3DXMATRIXA16*	matTrans, LPDIRECT3DVERTEXBUFFER9 vertextBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, int vertexNum, int primeCount)
{
	D3DDevice->SetTransform(D3DTS_WORLD, matTrans);
	D3DDevice->SetStreamSource(0, vertextBuffer, 0, sizeof(CUSTOMVERTEX));
	D3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	D3DDevice->SetIndices(indexBuffer);
	D3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexNum, 0, primeCount);
	//D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void GraphicSystem::DrawMesh(LPD3DXMESH	mesh, D3DMATERIAL9*	meshMaterials, LPDIRECT3DTEXTURE9* meshTextures, int numMaterials)
{
	for (int i = 0; i < numMaterials; i++)
	{
		D3DDevice->SetMaterial(&meshMaterials[i]);
		D3DDevice->SetTexture(0, meshTextures[i]);

		mesh->DrawSubset(i);
	}
}

void GraphicSystem::SetupMareices()
{
	D3DXMATRIXA16 matWorld;
	UINT iTime = timeGetTime() % 1000;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
	D3DXMatrixRotationY(&matWorld, fAngle);
	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//wasd
	D3DXVECTOR3 vEyept(0.0f, 0.0f, -30.0f);
	D3DXVECTOR3 vLootatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyept, &vLootatPt, &vUpVec);
	D3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);

	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void GraphicSystem::SetupLight()
{
	// ����(material)����
	// ������ ����̽��� �� �ϳ��� ������ �� �ִ�.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	D3DDevice->SetMaterial(&mtrl);

	D3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			// ���������� �Ҵ�

	D3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);		// ȯ�汤��(ambient light)�� �� ����
}
