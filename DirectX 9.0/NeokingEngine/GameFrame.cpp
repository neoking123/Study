#include "GameFrame.h"
#include "GraphicSystem.h"
#include "Camera.h"

GameFrame* GameFrame::instance = nullptr;

GameFrame::GameFrame()
{
}

GameFrame::~GameFrame()
{
}

void GameFrame::Init()
{
	tank.Init();
	D3DXVECTOR3 vPos(30.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vLookatPt(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
	tank.SetPos(&vPos, &vLookatPt, &vUp);

	//ez.InitGeometry("Models\\Ezreal.X");
	//tiger.InitGeometry("Models\\Ezreal.X");

	//const char*	tex[256] = { "Stone_wall_tile_B_diffuse.tga", "lightmap.tga", "", "" };
	const char*	tex[256] = { "Stone_wall_tile_B_diffuse.tga", "", "", "" };
	D3DXVECTOR3	vScale;

	vScale.x = vScale.z = 1.0f; vScale.y = 0.1f;
	terrain = new Terrain();
	terrain->Create(DXDEVICE, &vScale, 0.05f, BMP_HEIGHTMAP, tex);
}

void GameFrame::Update()
{
	//tank.Update(terrain->GetHeight((int)tank.vPos.x, (int)tank.vPos.z));
}

void GameFrame::Render()
{
	RECT rc = { 100, 100, 0, 0 };
	D3DXCOLOR color = { 1, 0, 0, 1 };
	DrawText(NULL, "test", strlen("test"), &rc, DT_NOCLIP);

	terrain->Draw(FRUSTUM);
	tank.Render();

	//GRAPHIC_SYSTEM->DrawMesh(ez.GetMesh(), ez.GetMeshMaterials(), ez.GetMeshTextures(), ez.GetNumMaterials());	
}

void GameFrame::Release()
{
	SAFE_DELETE(terrain);
}
