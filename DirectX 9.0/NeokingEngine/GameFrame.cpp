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
	//CUSTOMVERTEX vertices[] =
	//{
	//	/*{ {150.0f, 250.0f, 0.5f}, 0x00000000 },
	//	{ {150.0f, 150.0f, 0.5f}, 0xffff0000 },
	//	{ {250.0f, 250.0f, 0.5f}, 0xffff0000 },

	//	{ {250.0f, 250.0f, 0.5f}, 0xffff0000 },
	//	{ {150.0f, 150.0f, 0.5f}, 0xffff0000 },
	//	{ {250.0f, 150.0f, 0.5f}, 0xffff0000 }*/

	//	{ { -1 , 1 , 1 }, 0x09fb300 } ,
	//	{ { 1 , 1 , 1 },0x09fb300 } ,
	//	{ { 1 ,   1 ,  -1 }, 0x09fb300 },
	//	{ { -1 , 1 ,  -1 }, 0x09fb300 },

	//	{ { -1 , -1 , 1 }, 0x09fb300 } ,
	//	{ { 1 , -1 , 1 }, 0x09fb300 } ,
	//	{ { 1 , -1 ,  -1 }, 0x09fb300 },
	//	{ { -1 , -1 ,  -1 }, 0x09fb300 },
	//};

	//CUSTOMINDEX indeices[] =
	//{
	//	{0,1,2},{0,2,3},//À­¸é
	//	{4,6,5},{4,7,6},//¾Æ·§¸é
	//	{0,3,7},{0,7,4},//¿Þ¸é
	//	{1,5,6},{1,6,2},//¿À¸¥¸é
	//	{3,2,6},{3,6,7},//¾Õ¸é
	//	{0,4,5},{0,5,1}//µÞ¸é
	//};

	//tank.Init();
	//tank.InitVB(cannonVertices, sizeof(vertices), 8);
	//tank.InitIB(indeices, sizeof(indeices), 12);
	tank.Init();
	D3DXVECTOR3 vPos(30.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vLookatPt(1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
	tank.SetPos(&vPos, &vLookatPt, &vUp);

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

}

void GameFrame::Render()
{
	terrain->Draw(FRUSTUM);
	GRAPHIC_SYSTEM->DrawMesh(tank.GetMatTrans() ,tank.GetVB(), tank.GetIB(), 8 , 12);
	//GRAPHIC_SYSTEM->DrawMesh(tank.GetMatTrans() ,tank.cannonVB, tank.cannonIB, 8 , 12);

	//GRAPHIC_SYSTEM->DrawMesh(tiger.GetMesh(), tiger.GetMeshMaterials(), tiger.GetMeshTextures(), tiger.GetNumMaterials());	
}

void GameFrame::Release()
{
	SAFE_DELETE(terrain);
}
