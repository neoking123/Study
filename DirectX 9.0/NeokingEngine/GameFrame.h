#pragma once
#include "..\..\Common\Macro.h"
#include "Polygon.h"
#include "GameObject.h"
#include "Terrain.h"
#include "Tank.h"

#define BMP_HEIGHTMAP	"map129.bmp"
#define GAME_FRAME GameFrame::GetInstance()

class GameFrame
{
private:
	static GameFrame* instance;
	//Object3D::Polygon p;
	//GameObject tiger;
	//GameObject tank;
	Terrain* terrain;
	Tank tank;

	GameFrame();

public:
	~GameFrame();
	void Init();
	void Update();
	void Render();
	void Release();

	static GameFrame* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameFrame();
		}
		return instance;
	}

	static void FreeInstacne()
	{
		SAFE_DELETE(instance);
	}

	GameObject* GetTank()
	{
		return &tank;
	}
};

