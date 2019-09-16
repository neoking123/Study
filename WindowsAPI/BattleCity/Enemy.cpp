#include "Enemy.h"
#include "BitMapManager.h"
#include "InputComponent.h"
#include "Missile.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(InputComponent * input, int x, int y, string tag)
{
	this->input = input;
	transform.position.x = x;
	transform.position.y = y;
	this->tag = tag;
	speed = 2;
	fireElapseTime = 0.0f;
	fireDelayTime = 0.5f;
	isCollide = false;
	isDead = false;
	direction = DIRECTION::STOP;
	fireDirection = DIRECTION::DOWN;
	animState = TANK_ANIM_STATE::DOWN_00;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::E_DOWN_0));
	for (int i = BITMAP_RES::E_DOWN_0; i <= E_UP_1; i++)
	{
		graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(i));
	}

	phsics.SetColliderBox(*this, SIZE{ 32, 32 }, 2, 2, -2, -2);

	Missile* newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile_enemy");
	missilePool.push_back(newMissile);

	/*newMissile = new Missile();
	newMissile->Init(nullptr, 0, 0, "missile");
	missilePool.push_back(newMissile);*/
}

void Enemy::Update(float elapseTime)
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

void Enemy::Render(HDC hdc)
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

void Enemy::SetPosition(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
}