#include "Character.h"
#include "BitMapManager.h"

Character::Character()
{
}


Character::~Character()
{
}

void Character::Init(int index, POINT pos, int spriteNum)
{
	SceneObject::Init(index, pos, spriteNum);

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
		position.x -= 8;
		break;
	case VK_RIGHT:
		position.x += 8;
		break;
	default:
		break;
	}
}
