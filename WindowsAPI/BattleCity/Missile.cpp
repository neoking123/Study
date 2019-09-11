#include "Missile.h"
#include "BitMapManager.h"

Missile::Missile()
{
}


Missile::~Missile()
{
}

void Missile::Init(InputComponent * input, int x, int y, string tag)
{
	this->tag = tag;
	transform.position.x = x;
	transform.position.y = y;
	direction = DIRECTION::STOP;
	speed = 1;
	isFired = false;
	animState = MISSILE_ANIM_STATE::NOT_FIRED;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_0));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_0));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_1));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_2));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_3));
}

void Missile::Update(float elapseTime)
{
	phsics.Update(*this, elapseTime);

}

void Missile::Render(HDC hdc)
{
	graphics.Render(*this, hdc);
}

void Missile::SetPosition(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
}

void Missile::SetDirection(DIRECTION newDirection)
{
	direction = newDirection;
}

void Missile::SetAnimState(MISSILE_ANIM_STATE newAnimState)
{
	animState = newAnimState;
}
