#pragma once
#include "Tank.h"

/**
* @brief 적 탱크 클래스
* @author Dayeol Hyeon
*/

class Enemy : public Tank
{
public:
	Enemy();
	~Enemy();

	virtual void Init(InputComponent* input, int x, int y, string tag) override;
};

