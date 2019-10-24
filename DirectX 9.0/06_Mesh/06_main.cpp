#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include "..\..\Common\Camera.h"
#include "..\..\Common\ZCamera.h"
#include "..\..\Common\Macro.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

HWND hWnd = NULL;
LPDIRECT3D9					g_pD3D = NULL;
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;
LPD3DXMESH					g_pMesh = NULL;
D3DMATERIAL9*				g_pMeshMaterials = NULL;
LPDIRECT3DTEXTURE9*			g_pMeshTextures = NULL;
DWORD						g_dwNumMaterials = 0;
DWORD						g_cxHeight = 0;
DWORD						g_czHeight = 0;
DWORD						g_dwMouseX = 0;
DWORD						g_dwMouseY = 0;

//Camera camera;

HRESULT InitD3D(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		return E_FAIL;
	}

	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//camera.Init(g_pD3DDevice);

	return S_OK;
}

HRESULT InitGeometry()
{
	LPD3DXBUFFER pD3dXMtrlBuffer;

	// http://telnet.or.kr/directx/graphics/reference/d3dx/functions/mesh/d3dxloadmeshfromx.htm 참조
	if (FAILED(D3DXLoadMeshFromXA("Tiger.x", D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL, &pD3dXMtrlBuffer,
		NULL, &g_dwNumMaterials, &g_pMesh)))
	{
		MessageBox(NULL, "Could not find tiger.x", "ERROR", MB_OK);
	}

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3dXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];

	for (int i = 0; i < g_dwNumMaterials; i++)
	{
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
		g_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL && strlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, d3dxMaterials[i].pTextureFilename, &g_pMeshTextures[i])))
			{
				MessageBox(NULL, "Could not find texture map", "Textrue", MB_OK);
				return E_FAIL;
			}
		}
	}
	pD3dXMtrlBuffer->Release();
	return S_OK;
}

void CleanUp()
{
	SAFE_DELETE_ARRAY(g_pMeshMaterials);
	if (g_pMeshTextures)
	{
		for (int i = 0; i < g_dwNumMaterials; i++)
		{
			SAFE_RELEASE(g_pMeshTextures[i]);
		}
	}

	SAFE_RELEASE(g_pMesh);
	SAFE_RELEASE(g_pD3DDevice);
	SAFE_RELEASE(g_pD3D);
}

void SetupMareices()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyept(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3 vLootatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyept, &vLootatPt, &vUpVec);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void ProcessMouse()
{
	POINT pt;
	float fDelta = 0.001f;
	GetCursorPos(&pt);
	int dx = pt.x - g_dwMouseX;
	int dy = pt.y - g_dwMouseY;

	ZCamera::GetInstance()->RotateLocalX(dy * fDelta);
	ZCamera::GetInstance()->RotateLocalY(dx * fDelta);
	D3DXMATRIXA16* pmatView = ZCamera::GetInstance()->GetViewMatrix();
	g_pD3DDevice->SetTransform(D3DTS_VIEW, pmatView);

	RECT	rc;
	GetClientRect(hWnd, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
}

void ProcessKey()
{
	if (GetAsyncKeyState('A'))
		ZCamera::GetInstance()->MoveLocalZ(0.5f);

	if (GetAsyncKeyState('Z'))
		ZCamera::GetInstance()->MoveLocalZ(-0.5f);

	if (GetAsyncKeyState(VK_ESCAPE))
		PostMessage(hWnd, WM_DESTROY, 0, 0);

	if (GetAsyncKeyState(VK_LBUTTON))
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (GetAsyncKeyState(VK_RBUTTON))
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void ProcessInputs(void)
{
	ProcessMouse();
	ProcessKey();
}

VOID Animate()
{
	/// 0 ~ 2PI 까지(0~360도) 값을 변화시킴 Fixed Point기법 사용
	DWORD d = GetTickCount() % ((int)((D3DX_PI * 2) * 1000));
	/// Y축 회전행렬
	//	D3DXMatrixRotationY( &g_matAni, d / 1000.0f );

	ProcessInputs();
}

void DrawBillBoard()
{
	D3DXMATRIXA16 matBillboard;
	D3DXMatrixIdentity(&matBillboard);

	// Y축 회전행렬은 _11, _13, _31, _33번 행렬에 회전값이 들어간다
		// 카메라의 Y축 회전행렬값을 읽어서 역행렬을 만들면 X,Z축이 고정된
		// Y축 회전 빌보드 행렬을 만들수 있다
	matBillboard._11 = ZCamera::GetInstance()->GetViewMatrix()->_11;
	matBillboard._13 = ZCamera::GetInstance()->GetViewMatrix()->_13;
	matBillboard._31 = ZCamera::GetInstance()->GetViewMatrix()->_31;
	matBillboard._33 = ZCamera::GetInstance()->GetViewMatrix()->_33;
	D3DXMatrixInverse(&matBillboard, NULL, &matBillboard);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matBillboard);
	/*g_pD3DDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pD3DDevice->SetFVF(D3DFVF_CUSTOMVVERTEX);
	g_pD3DDevice->SetIndices(g_pIB);*/
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_cxHeight * g_czHeight, 0,
		(g_cxHeight - 1) * (g_czHeight - 1) * 2);

}

void Render()
{
	if (g_pD3DDevice == NULL)
		return;

	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	Animate();

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//SetupMareices();
		//camera.View();

		for (int i = 0; i < g_dwNumMaterials; i++)
		{
			g_pD3DDevice->SetMaterial(&g_pMeshMaterials[i]);
			g_pD3DDevice->SetTexture(0, g_pMeshTextures[i]);

			g_pMesh->DrawSubset(i);
		}
		//DrawBillBoard();
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);


	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitGeometry()))
		{
			ShowWindow(hWnd, nCmdShow);
			UpdateWindow(hWnd);

			ZeroMemory(&Message, sizeof(Message));
			while (Message.message != WM_QUIT)
			{
				if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
					Render();
			}
		}

	}

	CleanUp();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostMessage(hWnd, WM_DESTROY, 0, 0);
		return 0;
	case WM_DESTROY:
		CleanUp();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

