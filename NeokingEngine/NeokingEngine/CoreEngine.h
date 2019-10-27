#pragma once
#include "Macro.h"
#include "PhysicsSystem.h"
#include "MessageManager.h"

#define CORE_ENGINE CoreEngine::GetInstance()

class CoreEngine
{
private:
	static CoreEngine* instance;

	CoreEngine();

public:
	//WindowSystem windowSystem;
	//InputSystem inputSystem;
	PhysicsSystem phsicsSystem;
	MessageManager messageManager;

public:
	~CoreEngine();

	void Init(HINSTANCE hInstance);
	void Update();
	void Release();

	static CoreEngine* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CoreEngine();
		}
		return instance;
	}

	static void FreeInstance()
	{
		SAFE_DELETE(instance);
	}
};

// 윈도우 랩핑
//http://tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=2200 참고