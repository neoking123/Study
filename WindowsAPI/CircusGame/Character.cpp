#include "Character.h"
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "BitMapManager.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Init(InputComponent * input, int x, int y)
{
	this->input = input;
	transform.position.x = x;
	transform.position.y = y;
	direction = 0;
	speed = 2;
	jumpPower = 5;
	isJump = false;
	isDead = false;
	tag = "player";
	animState = ANIM_STATE::IDLE;
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER0));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER0));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER1));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER2));
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::DEATH));

	physics.SetColliderBox(*this, SIZE{ 30, 30 });
}

void Character::Update(HDC hdc)
{
	input->Update(*this);
	physics.Update(*this);
	graphics.UpdateAnim(*this);
	graphics.Update(*this, hdc);
}

void Character::SetAnimState(ANIM_STATE newState)
{
	animState = newState;
}
