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
	speed = 8;
	isFired = false;
	isCollide = false;
	isCollide = false;
	animState = MISSILE_ANIM_STATE::NOT_FIRED;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_0));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_0));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_1));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_2));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::MISSILE_3));

	phsics.SetColliderBox(*this, SIZE{ 8, 8 }, 0, 0, 0, 0);
}

void Missile::Update(float elapseTime)
{
 	phsics.Update(*this, elapseTime);
	graphics.UpdateAnim(*this, elapseTime);
	//CheckBoundary();
}

void Missile::Render(HDC hdc)
{
	phsics.RenderColliderBox(hdc);
	graphics.Render(*this, hdc);
}

void Missile::SetPosition(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
}

void Missile::SetFirePosition(int x, int y)
{
	if (direction == DIRECTION::UP)
	{
		transform.position.x = x + 12;
		transform.position.y = y;
	}
	else if (direction == DIRECTION::DOWN)
	{
		transform.position.x = x + 12;
		transform.position.y = y + 24;
	}
	else if (direction == DIRECTION::LEFT)
	{
		transform.position.x = x;
		transform.position.y = y + 12;
	}
	else if (direction == DIRECTION::RIGHT)
	{
		transform.position.x = x + 24;
		transform.position.y = y + 12;
	}
}

void Missile::SetDirection(DIRECTION newDirection)
{
	direction = newDirection;
}

void Missile::SetSpeed(int newSpeed)
{
	speed = newSpeed;
}

void Missile::Reset()
{
	isFired = false;
	isCollide = false;
	SetDirection(DIRECTION::STOP);
	SetPosition(0, 0);
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
		isCollide = true;
	}
}
