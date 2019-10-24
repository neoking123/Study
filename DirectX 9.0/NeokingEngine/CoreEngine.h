#pragma once
#include "WindowSystem.h"
#include "GraphicSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include "MessageManager.h"

class CoreEngine
{
private:
	WindowSystem windowSystem;
	GraphicSystem graphicSystem;
	InputSystem inputSystem;
	PhysicsSystem phsicsSystem;
	MessageManager messageManager;
	
public:
	CoreEngine();
	~CoreEngine();

	void Init();
	void Release();
};

// 윈도우 랩핑
//http://tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=2200 참고