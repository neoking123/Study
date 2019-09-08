#include "Enemy.h"
#include "BitMapManager.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(POINT pos, int spriteNum)
{
	SceneObject::Init(pos, spriteNum);
	speed = 1;

	// 스프라이트 추가
	for (int i = 0; i < 9; i++)
	{
		SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::ENEMY + i));
	}
}	

void Enemy::Move()
{
	position.x -= speed;
}