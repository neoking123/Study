#include "Character.h"
#include "BitMapManager.h"

void Character::SetDirecton(MOVE_DIR newDir)
{
	moveDir = newDir;
}

void Character::UpdateAnim(MOVE_DIR dir)
{
	DWORD currentTick = GetTickCount();
	
	if (dir == MOVE_DIR::FORWARD)
	{
		if (currentTick - lastChangeTime < 100)
			return;
		if (animState == ANIM_STATE::IDLE)
		{
			animState = ANIM_STATE::JUMP;
			SetSprite(ANIM_STATE::JUMP);
		}
		else if (animState == ANIM_STATE::JUMP)
		{
			animState = ANIM_STATE::BACKWARD;
			SetSprite(ANIM_STATE::BACKWARD);
		}
		else if (animState == ANIM_STATE::BACKWARD)
		{
			animState = ANIM_STATE::IDLE;
			SetSprite(ANIM_STATE::IDLE);
		}
	}
	else if (dir == MOVE_DIR::BACKWORD)
	{
		if (currentTick - lastChangeTime < 500)
			return;

		if (animState == ANIM_STATE::IDLE)
		{
			animState = ANIM_STATE::BACKWARD;
			SetSprite(ANIM_STATE::BACKWARD);
		}
		else if (animState == ANIM_STATE::BACKWARD)
		{
			animState = ANIM_STATE::IDLE;
			SetSprite(ANIM_STATE::IDLE);
		}
	}

	if (dir == MOVE_DIR::STOP)
	{
		animState = ANIM_STATE::IDLE;
		SetSprite(ANIM_STATE::IDLE);
	}

	lastChangeTime = currentTick;
}

void Character::Jump()
{
	if (!isJump)
		return;

	if (jumpAngle >= 360)
	{
		isJump = false;
		jumpAngle = 0;
		animState = ANIM_STATE::IDLE;
		SetSprite(animState);
		moveDir = MOVE_DIR::STOP;
	}

	if (moveDir == MOVE_DIR::FORWARD)
	{
		position.x += speed * 3 / speed;
	}
	else if (moveDir == MOVE_DIR::BACKWORD)
	{
		if (position.x > 100)
		{
			position.x -= speed * 3 / speed;
		}
	}


	position.y -= (LONG)roundf(sin(DegreesToRadians(jumpAngle))) * jumpPower;
	jumpAngle += jumpSpeed;

}

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
	isJump = false;
	isJumpUp = false;
	isJumpDown = false;
	speed = 1;
	jumpSpeed = 4;
	jumpPower = 3;
	jumpAngle = 0;
	animState = ANIM_STATE::IDLE;
	moveDir = MOVE_DIR::STOP;
	lastChangeTime = 0;

	// 스프라이트 추가
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER0));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER0));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER1));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::PLAYER2));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::DEATH));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::WIN));
	SceneObject::AddSprite(BitMapManager::GetInstance()->GetBitMap(BITMAP_RES::WIN2));
}

void Character::Input(WPARAM wParam, KEY_STATE keyState)
{
	MOVE_DIR newDir = MOVE_DIR::NONE;
	if (keyState == KEY_STATE::BUTTONDOWN)
	{
		switch (wParam)
		{
		case VK_LEFT:
			if (position.x > 100 && !isJump)
			{
				position.x -= speed;
				SetDirecton(MOVE_DIR::BACKWORD);
				newDir = MOVE_DIR::BACKWORD;
			}
			break;
		case VK_RIGHT:
			if (position.x < 5200 && !isJump)
			{
				position.x += speed;
				SetDirecton(MOVE_DIR::FORWARD);
				newDir = MOVE_DIR::FORWARD;
			}
			break;
		case 0x58: //x
		case 0x5A: //z
			if (!isJump)
			{
				isJump = true;
				isJumpUp = true;
				animState = ANIM_STATE::JUMP;
				SetSprite(animState);
			}
			break;
		default:
			newDir = MOVE_DIR::NONE;
			break;
		}
	}
	else if (keyState == KEY_STATE::BUTTONUP && !isJump)
	{
		SetDirecton(MOVE_DIR::STOP);
		newDir = MOVE_DIR::STOP;
	}

	if (newDir != MOVE_DIR::NONE)
	{
		UpdateAnim(newDir);
	}
}

void Character::SetSpeed(int newSpeed)
{
	speed = newSpeed;
}
