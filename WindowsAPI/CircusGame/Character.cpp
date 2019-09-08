#include "Character.h"
#include "InputComponent.h"
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
	graphics.AddSprite(*BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER0));
}

void Character::Update(HDC hdc)
{
	input->Update(*this);
	physics.Update(*this);
	graphics.Update(*this, hdc);
}
