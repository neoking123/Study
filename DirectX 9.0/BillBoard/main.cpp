#include <d3d9.h>
#include <d3dx9.h>
#include "..\..\Common\ZFLog.h"
#include "..\..\Common\ZCamera.h"
#include "..\..\Common\Macro.h"

#define MAINBODY

#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	"HeightMap-TList"
#define BMP_HEIGHTMAP	"map128.bmp"
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

HWND						g_hWnd = NULL;
LPDIRECT3D9					g_pD3D = NULL;
LPDIRECT3DDEVICE9			g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9		g_pVB = NULL;
LPDIRECT3DINDEXBUFFER9		g_pIB = NULL;
LPDIRECT3DTEXTURE9			g_pTexHeight = NULL;
LPDIRECT3DTEXTURE9			g_pTexDiffuse = NULL;
D3DXMATRIXA16				g_matAni;
DWORD						g_cxHeight = 0;
DWORD						g_czHeight = 0;
DWORD						g_dwMouseX = 0;
DWORD						g_dwMouseY = 0;

//struct CUSTOMVERTEX
//{
//	D3DXVECTOR3	p;
//	D3DXVECTOR3	n;
//	D3DXVECTOR3	t;
//};

struct CUSTOMVERTEX
{
	float x, y, z;
	DWORD color;
};

#define D3DFVF_CUSTOMVVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

struct MYINDEX
{
	WORD _0, _1, _2;
};

HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
		return E_FAIL;

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

HRESULT InitTexture()
{
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, BMP_HEIGHTMAP, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL,
		&g_pTexHeight)))
		return E_FAIL;

	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, "tile2.tga", &g_pTexDiffuse)))
		return E_FAIL;

	return S_OK;
}

HRESULT InitVB()
{
	CUSTOMVERTEX vertices[] =
	{
		{ -1 , 1 , 1 , 0xffff0000 } ,
		{ 1 , 1 , 1 , 0xff00ff00 } ,
		{ 1 ,   1 ,  -1 , 0xff0000ff },
		{ -1 , 1 ,  -1 , 0xffffff00 },

		{ -1 , -1 , 1 , 0xff00ffff } ,
		{ 1 , -1 , 1 , 0xffff00ff } ,
		{ 1 , -1 ,  -1 , 0xff000000 },
		{ -1 , -1 ,  -1 , 0xffffffff },
	};

	if (FAILED(g_pd3dDevice->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0,
		D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &g_pVB, NULL)))
		return E_FAIL;

	void* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));
	g_pVB->Unlock();

	return S_OK;
}

HRESULT InitIB()
{
	MYINDEX indeices[] =
	{
		{0,1,2},{0,2,3},//윗면
		{4,6,5},{4,7,6},//아랫면
		{0,3,7},{0,7,4},//왼면
		{1,5,6},{1,6,2},//오른면
		{3,2,6},{3,6,7},//앞면
		{0,4,5},{0,5,1}//뒷면
	};

	if (FAILED(g_pd3dDevice->CreateIndexBuffer(12 * sizeof(MYINDEX), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	void* pIndices;
	if (FAILED(g_pIB->Lock(0, sizeof(indeices), (void**)&pIndices, 0)))
		return E_FAIL;
	memcpy(pIndices, indeices, sizeof(indeices));
	g_pIB->Unlock();
}

void SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 100.0f, -(float)g_czHeight);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	ZCamera::GetInstance()->SetView(&vEyePt, &vLookatPt, &vUpVec);
}


HRESULT InitGeometry()
{
	if (FAILED(InitTexture()))
		return E_FAIL;

	if (FAILED(InitVB()))
		return E_FAIL;

	if (FAILED(InitIB()))
		return E_FAIL;

	SetupCamera();
	// 최초의 마우스 위치 보관
	POINT	pt;
	GetCursorPos(&pt);
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;

	return S_OK;
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
	g_pd3dDevice->SetTransform(D3DTS_VIEW, pmatView);

	RECT	rc;
	GetClientRect(g_hWnd, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(g_hWnd, &pt);
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
		PostMessage(g_hWnd, WM_DESTROY, 0, 0);

	if (GetAsyncKeyState(VK_LBUTTON))
		g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (GetAsyncKeyState(VK_RBUTTON))
		g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void ProcessInputs(void)
{
	ProcessMouse();
	ProcessKey();
}

VOID SetupLights()
{
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial(&mtrl);

	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 0.0f;
	//vecDir = D3DXVECTOR3(1, 1, 1);
	vecDir = D3DXVECTOR3(cosf(GetTickCount() / 350.0f), 1.0f, sinf(GetTickCount() / 350.0f));
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
	light.Range = 1000.0f;

	g_pd3dDevice->SetLight(0, &light);
	g_pd3dDevice->LightEnable(0, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00909090);
}

void LogFPS(void)
{
	static DWORD nTick = 0;
	static DWORD nFPS = 0;

	if (GetTickCount() - nTick > 1000)
	{
		nTick = GetTickCount();
		ZFLog::GetInstance()->Log("FPS : %d", nFPS);
		nFPS = 0;

		return;
	}

	nFPS++;
}

VOID Animate()
{
	/// 0 ~ 2PI 까지(0~360도) 값을 변화시킴 Fixed Point기법 사용
	DWORD d = GetTickCount() % ((int)((D3DX_PI * 2) * 1000));
	/// Y축 회전행렬
	//	D3DXMatrixRotationY( &g_matAni, d / 1000.0f );
	D3DXMatrixIdentity(&g_matAni);

	LogFPS();

	SetupLights();
	ProcessInputs();
}

void CleanUp()
{
	SAFE_RELEASE(g_pTexHeight);
	SAFE_RELEASE(g_pTexDiffuse);
	SAFE_RELEASE(g_pIB);
	SAFE_RELEASE(g_pVB);
	SAFE_RELEASE(g_pd3dDevice);
	SAFE_RELEASE(g_pD3D);
}

void DrawMesh(D3DXMATRIXA16* pMat)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, pMat);
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVVERTEX);
	g_pd3dDevice->SetIndices(g_pIB);
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_cxHeight * g_czHeight, 0,
		(g_cxHeight - 1) * (g_czHeight - 1) * 2);
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

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matBillboard);
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVVERTEX);
	g_pd3dDevice->SetIndices(g_pIB);
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_cxHeight * g_czHeight, 0,
		(g_cxHeight - 1) * (g_czHeight - 1) * 2);

}

void Render()
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	Animate();

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->SetTexture(0, g_pTexDiffuse);
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		DrawBillBoard();

		//D3DXMatrixTranslation(&g_matAni, 200, 0, 0);
		//DrawMesh(&g_matAni);

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_DESTROY:
		CleanUp();
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostMessage(hWnd, WM_DESTROY, 0, 0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
char g_szClassName[256] = "BasicFrame";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;

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

	g_hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	if (FAILED(InitD3D(g_hWnd)))
		return -1;

	if (FAILED(InitGeometry()))
		return -1;

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	while (true)
	{
		/// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			Render();
		}
	}

	ZFLog::Release();

	UnregisterClass(g_szClassName, hInstance);

	return (int)Message.wParam;
}