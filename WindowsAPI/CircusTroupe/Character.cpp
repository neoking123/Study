#include "Character.h"
#include "BitMapManager.h"

Character::Character()
{
}


Character::~Character()
{
}

void Character::Init(POINT pos, int spriteNum)
{
	SceneObject::Init(pos, spriteNum);
	isCharacter = true;
	speed = 1;

	// 스프라이트 추가
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER0));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER0));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER1));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER2));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::DEATH));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::WIN));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::WIN2));
}

void Character::Input(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		position.x -= speed;
		break;
	case VK_RIGHT:
		position.x += speed;
		break;
	default:
		break;
	}
}

void Character::SetSpeed(int newSpeed)
{
	speed = newSpeed;
}
