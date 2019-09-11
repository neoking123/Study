#include "Tank.h"
#include "BitMapManager.h"
#include "InputComponent.h"
#include "Missile.h"
#include "Macro.h"

Tank::Tank()
{
}

Tank::~Tank()
{
}

void Tank::Init(InputComponent* input, int x, int y, string tag)
{
	this->input = input;
	transform.position.x = x;
	transform.position.y = y;
	this->tag = tag;
	speed = 1;
	direction = DIRECTION::STOP;
	fireDirection = DIRECTION::UP;
	animState = TANK_ANIM_STATE::UP_00;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::TANK_UP_0));
	for (int i = BITMAP_RES::TANK_DOWN_0; i <= TANK_UP_1; i++)
	{
		graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(i));
	}

	Missile* newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile");
	missilePool.push_back(newMissile);

	newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile");
	missilePool.push_back(newMissile);
}

void Tank::Update(float elapseTime)
{
	input->Update(*this);
	phsics.Update(*this, elapseTime);
	graphics.UpdateAnim(*this, elapseTime);

	for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
	{
		if ((*iter)->isFired)
		{
			(*iter)->phsics.Update(**iter, elapseTime);
			(*iter)->graphics.UpdateAnim(**iter, elapseTime);
		}
	}
}

void Tank::Render(HDC hdc)
{
	graphics.Render(*this, hdc);

	for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
	{
		if ((*iter)->isFired)
		{
			(*iter)->graphics.Render(**iter, hdc);
		}
	}
	
}

void Tank::SetPosition(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
}

void Tank::SetDirection(DIRECTION newDirection)
{
	direction = newDirection;
}

void Tank::Release()
{
	for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}

void Tank::SetAnimState(TANK_ANIM_STATE newAnimState)
{
	animState = newAnimState;
}

void Tank::Fire()
{
	auto iter = missilePool.begin();
	for (; iter != missilePool.end(); iter++)
	{
		if (!(*iter)->isFired)
		{
			(*iter)->isFired = true;
			(*iter)->SetDirection(fireDirection);
			(*iter)->SetPosition(transform.position.x + 12, transform.position.y + 12);
			return;
		}
	}

	if (iter == missilePool.end())
	{
		for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
		{
			if ((*iter)->isFired)
			{
				(*iter)->isFired = false;
				(*iter)->SetDirection(DIRECTION::STOP);
				(*iter)->SetPosition(0, 0);
			}
		}
	}
}
