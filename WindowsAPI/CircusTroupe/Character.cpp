#include "Character.h"
#include "BitMapManager.h"

void Character::SetDirecton(MOVE_DIR newDir)
{
	moveDir = newDir;
}

void Character::UpdateAnim(MOVE_DIR dir)
{
	DWORD currentTick = GetTickCount();
	if (currentTick - lastChangeTime > 100)
	{
		if (dir == MOVE_DIR::FORWARD)
		{
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

		lastChangeTime = currentTick;
	}

	if (dir == MOVE_DIR::STOP)
	{
		animState = ANIM_STATE::IDLE;
		SetSprite(ANIM_STATE::IDLE);
	}
}

void Character::SetJumpTargetPos()
{
	if (moveDir == MOVE_DIR::FORWARD)
	{
		jumpTargetPos = { position.x + 50, position.y - 50 };
		landingPos = { position.x + 100, position.y };
	}
	else if (moveDir == MOVE_DIR::BACKWORD)
	{
		jumpTargetPos = { position.x - 50, position.y - 50 };
		landingPos = { position.x - 100, position.y };
	}
	else if (moveDir == MOVE_DIR::STOP)
	{
		jumpTargetPos = { position.x, position.y - 50 };
		landingPos = { position.x, position.y };
	}
}

void Character::Jump()
{
	if (!isJump)
		return;

	animState = ANIM_STATE::JUMP;
	SetSprite(animState);

	jumpHeight = jumpTime * jumpTime - jumpTime * jumpPower;
	jumpTime += 0.1f;
	position.x += 2;
	position.y += (LONG)jumpHeight;

	if (jumpTime >= jumpPower)
	{
		jumpTime = 0.f;
		jumpHeight = 0.f;
		isJump = false;
	}

	/*if (moveDir == MOVE_DIR::FORWARD)
	{
		if (jumpTargetPos.x >= position.x && jumpTargetPos.y <= position.y)
		{
			position.x++;
			position.y--;
		}
		else
		{
			position.x++;
			position.y++;
		}
	}
	else if (moveDir == MOVE_DIR::BACKWORD)
	{
		if (jumpTargetPos.x <= position.x && jumpTargetPos.y <= position.y)
		{
			position.x--;
			position.y--;
		}
		else
		{
			position.x--;
			position.y++;
		}
	}
	else if (moveDir == MOVE_DIR::STOP)
	{
		if (jumpTargetPos.y <= position.y)
		{
			position.y--;
		}
		else
		{
			position.y++;
		}
	}*/
}

void Character::ForceGravity()
{
	if (position.y < 305)
	{
		position.y += (LONG)3.f;
	}
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
	speed = 1;
	animState = ANIM_STATE::IDLE;
	moveDir = MOVE_DIR::STOP;
	lastChangeTime = 0;
	jumpTime = 0.f;
	jumpHeight = 0.f;
	jumpPower = 5.5f;
	jumpTargetPos = { 0, 0 };
	landingPos = { 0, 0 };

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
