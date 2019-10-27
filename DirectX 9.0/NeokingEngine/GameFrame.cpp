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

	//	{ { -1 , 1 , 1 }, 0xffff0000 } ,
	//	{ { 1 , 1 , 1 }, 0xff00ff00 } ,
	//	{ { 1 ,   1 ,  -1 }, 0xff0000ff },
	//	{ { -1 , 1 ,  -1 }, 0xffffff00 },

	//	{ { -1 , -1 , 1 }, 0xff00ffff } ,
	//	{ { 1 , -1 , 1 }, 0xffff00ff } ,
	//	{ { 1 , -1 ,  -1 }, 0xff000000 },
	//	{ { -1 , -1 ,  -1 }, 0xffffffff },
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

	//p.InitVB(vertices, sizeof(vertices), 8);
	//p.InitIB(indeices, sizeof(indeices), 12);


	//tiger.InitGeometry("Models\\Ezreal.X");

	const char*	tex[256] = { "tile2.tga", "", "", "" };
	D3DXVECTOR3	vScale;

	vScale.x = vScale.z = 2.0f; vScale.y = 0.2f;
	terrain = new Terrain();
	terrain->Create(DXDEVICE, &vScale, 0.05f, BMP_HEIGHTMAP, tex);
}

void GameFrame::Update()
{

}

void GameFrame::Render()
{
	//GRAPHIC_SYSTEM->DrawMesh(p.GetVB(), p.GetIB(), 8 , 12);

	//GRAPHIC_SYSTEM->DrawMesh(tiger.GetMesh(), tiger.GetMeshMaterials(), tiger.GetMeshTextures(), tiger.GetNumMaterials());

	terrain->Draw(FRUSTUM);
	
}

void GameFrame::Release()
{
	SAFE_DELETE(terrain);
}
