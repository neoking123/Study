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
	speed = 4;
	isFired = false;
	isCrash = false;
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
	graphics.UpdateAnim(*this, elapseTime);
	CheckBoundary();
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

void Missile::CheckBoundary()
{
	if (transform.position.x > 24 + 13 * 32 || transform.position.x < 24
		|| transform.position.y < 24 || transform.position.y > 24 + 13 * 32)
	{
		isCrash = true;
	}
}
