#include "FirePot.h"
#include "BitMapManager.h"

FirePot::FirePot()
{
}


FirePot::~FirePot()
{
}

void FirePot::Init(int x, int y)
{
	transform.position.x = x;
	transform.position.y = y;
	tag = "FirePot";
	animState = FIREPOT_ANIM_STATE::FIREPOT_ANIM_STATE1;

	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::FRONT));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::FRONT));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::FRONT2));

	physics.SetColliderBox(*this, SIZE{ 30, 30 });
}

void FirePot::Update(HDC hdc)
{
	graphics.Update(*this, hdc);
	graphics.UpdateAnim(*this);
}

void FirePot::SetAnimState(FIREPOT_ANIM_STATE newState)
{
	animState = newState;
}

RECT FirePot::GetColliderBox()
{
	return physics.GetColliderBox();
}
