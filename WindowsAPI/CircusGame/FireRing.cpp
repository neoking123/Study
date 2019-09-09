#include "FireRing.h"
#include "BitMapManager.h"

FireRing::FireRing()
{
}

FireRing::~FireRing()
{
}

void FireRing::Init(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
	speed = -1;
	tag = "FireRing";
	animState = FIRE_ANIM_STATE::FIRE_ANIM_STATE1;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ENEMY));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ENEMY + 4));

	for (int i = 0; i < 9; i++)
	{
		graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ENEMY + i));
	}

	physics.SetColliderBox(SIZE{ 24, 30 });
}

void FireRing::Update(HDC hdc)
{
	physics.Update(*this);
	graphics.Update(*this, hdc);
	graphics.UpdateAnim(*this);
}

void FireRing::SetAnimState(FIRE_ANIM_STATE newState)
{
	animState = newState;
}

void FireRing::DrawBack(HDC hdc)
{
	graphics.DrawBack(*this, hdc);
}

RECT FireRing::GetColliderBox()
{
	return physics.GetColliderBox();
}
