#include "GraphicsComponent.h"
#include "BitMap.h"
#include "TransformComponent.h"
#include "Character.h"
#include "FireRing.h"
#include "FirePot.h"

void GraphicsComponent::Update(GameObject& gameObject, HDC hdc)
{
	Sprites[0]->Draw(hdc, gameObject.transform.position.x, gameObject.transform.position.y);
}

void GraphicsComponent::AddSprite(BitMap & bitmap)
{
	Sprites.push_back(&bitmap);
}

void GraphicsComponent::UpdateAnim(Character & character)
{
	DWORD currentTick = GetTickCount();

	if (character.direction == DIRECTION::RIGHT)
	{
		if (currentTick - lastChangeTime < 100)
			return;

		if (character.animState == ANIM_STATE::IDLE)
		{
			character.SetAnimState(ANIM_STATE::JUMP);
			Sprites[0] = Sprites[3];
		}
		else if (character.animState == ANIM_STATE::JUMP)
		{
			character.SetAnimState(ANIM_STATE::BACKWARD);
			Sprites[0] = Sprites[2];
		}
		else if (character.animState == ANIM_STATE::BACKWARD)
		{
			character.SetAnimState(ANIM_STATE::IDLE);
			Sprites[0] = Sprites[1];
		}
	}
	else if (character.direction == DIRECTION::LEFT)
	{
		if (currentTick - lastChangeTime < 300)
			return;
		if (character.animState == ANIM_STATE::IDLE)
		{
			character.SetAnimState(ANIM_STATE::BACKWARD);
			Sprites[0] = Sprites[2];
		}
		else if (character.animState == ANIM_STATE::BACKWARD)
		{
			character.SetAnimState(ANIM_STATE::IDLE);
			Sprites[0] = Sprites[1];
		}
		else if (character.animState == ANIM_STATE::JUMP)
		{
			character.SetAnimState(ANIM_STATE::IDLE);
			Sprites[0] = Sprites[1];
		}
	}
	else if (character.direction == DIRECTION::STOP)
	{
		character.SetAnimState(ANIM_STATE::IDLE);
		Sprites[0] = Sprites[1];
	}

	if (character.isJump)
	{
		character.SetAnimState(ANIM_STATE::JUMP);
		Sprites[0] = Sprites[3];
	}

	if (character.isDead)
	{
		character.SetAnimState(ANIM_STATE::DEAD);
		Sprites[0] = Sprites[4];
	}

	lastChangeTime = currentTick;
}

void GraphicsComponent::UpdateAnim(FireRing & fireRing)
{
	DWORD currentTick = GetTickCount();

	if (currentTick - lastChangeTime < 200)
		return;

	if (fireRing.animState == FIRE_ANIM_STATE::FIRE_ANIM_STATE1)
	{
		fireRing.SetAnimState(FIRE_ANIM_STATE::FIRE_ANIM_STATE2);
		Sprites[0] = Sprites[10];
		Sprites[1] = Sprites[4];
	}
	else if (fireRing.animState == FIRE_ANIM_STATE::FIRE_ANIM_STATE2)
	{
		fireRing.SetAnimState(FIRE_ANIM_STATE::FIRE_ANIM_STATE1);
		Sprites[0] = Sprites[2];
		Sprites[1] = Sprites[6];
	}

	lastChangeTime = currentTick;
}

void GraphicsComponent::UpdateAnim(FirePot & firePot)
{
	DWORD currentTick = GetTickCount();

	if (currentTick - lastChangeTime < 200)
		return;

	if (firePot.animState == FIREPOT_ANIM_STATE::FIREPOT_ANIM_STATE1)
	{
		firePot.SetAnimState(FIREPOT_ANIM_STATE::FIREPOT_ANIM_STATE2);
		Sprites[0] = Sprites[1];
	}
	else if (firePot.animState == FIREPOT_ANIM_STATE::FIREPOT_ANIM_STATE2)
	{
		firePot.SetAnimState(FIREPOT_ANIM_STATE::FIREPOT_ANIM_STATE1);
		Sprites[0] = Sprites[2];
	}

	lastChangeTime = currentTick;
}

void GraphicsComponent::DrawBack(FireRing & fireRing, HDC hdc)
{
	Sprites[1]->Draw(hdc, fireRing.transform.position.x + 24, fireRing.transform.position.y);
}
