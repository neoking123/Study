#pragma once
#include "..\..\Common\Macro.h"
#include "CoreEngine.h"

#define GAME_FRAME GameFrame::GetInstance()

class GameFrame
{
private:
	static GameFrame* instance;
	Object3D::Polygon p;

	GameFrame();

public:
	~GameFrame();
	void Init();
	void Update();
	void Render();

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
};

