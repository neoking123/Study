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
	speed = 2;
	fireElapseTime = 0.0f;
	fireDelayTime = 0.1f;
	isCollide = false;
	isDead = false;
	direction = DIRECTION::STOP;
	fireDirection = DIRECTION::UP;
	animState = TANK_ANIM_STATE::UP_00;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::TANK_UP_0));
	for (int i = BITMAP_RES::TANK_DOWN_0; i <= TANK_UP_1; i++)
	{
		graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(i));
	}

	phsics.SetColliderBox(*this, SIZE{ 32, 32 }, 2, 2, -2, -2);

	Missile* newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile_player");
	missilePool.push_back(newMissile);

	newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile_player");
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
			(*iter)->Update(elapseTime);
		}
	}

	fireElapseTime += elapseTime;
}

void Tank::Render(HDC hdc)
{
	phsics.RenderColliderBox(hdc);
	graphics.Render(*this, hdc);

	for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
	{
		if ((*iter)->isFired)
		{
			(*iter)->Render(hdc);
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

void Tank::SetSpeed(int newSpeed)
{
	speed = newSpeed;
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
	if (fireElapseTime < fireDelayTime)
		return;

	auto iter = missilePool.begin();
	for (; iter != missilePool.end(); iter++)
	{
		if (!(*iter)->isFired)
		{
			(*iter)->isFired = true;
			(*iter)->SetDirection(fireDirection);
			//(*iter)->SetPosition(transform.position.x + 12, transform.position.y + 12);
			(*iter)->SetFirePosition(transform.position.x, transform.position.y);
			fireElapseTime = 0.0f;
			return;
		}
	}

	if (iter == missilePool.end())
	{
		for (auto iter = missilePool.begin(); iter != missilePool.end(); iter++)
		{
			if ((*iter)->isCollide)
			{
				//(*iter)->Reset();
			}
		}
	}
}

void Tank::Die()
{
	isDead = true;
	phsics.SetColliderBox(*this, SIZE{ 0, 0 });
}
