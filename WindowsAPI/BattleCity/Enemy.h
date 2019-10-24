#pragma once
#include "Tank.h"

/**
* @brief �� ��ũ Ŭ����
* @author Dayeol Hyeon
*/

class Enemy : public Tank
{
public:
	Enemy();
	~Enemy();

	virtual void Init(InputComponent* input, int x, int y, string tag) override;
};

