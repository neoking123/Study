#include "GraphicsComponent.h"
#include "BitMap.h"
#include "GameObject.h"
#include "Tank.h"
#include "Missile.h"
#include "Tile.h"

void GraphicsComponent::Render(GameObject & gameObject, HDC hdc)
{
	if (gameObject.tag == "tile")
	{
		Tile* tile = static_cast<Tile*>(&gameObject);
		Sprites[0]->DrawFourDivisions(hdc, gameObject.transform.position.x, gameObject.transform.position.y, 
			tile->phsics1.GetColliderSize(), tile->phsics2.GetColliderSize(), 
			tile->phsics3.GetColliderSize(), tile->phsics4.GetColliderSize(),
			tile->phsics1.left, tile->phsics1.top, tile->phsics2.left, tile->phsics2.top,
			tile->phsics3.left, tile->phsics3.top, tile->phsics4.left, tile->phsics4.top);
		
	}
	else
	{
		Sprites[0]->Draw(hdc, gameObject.transform.position.x, gameObject.transform.position.y);
	}
}

void GraphicsComponent::AddSprite(BitMap & bitmap)
{
	Sprites.push_back(&bitmap);
}

void GraphicsComponent::UpdateAnim(GameObject& gameObject, float elapseTime)
{
	/*if (elapseTime < (1 / 60.f))
		return;*/
	
	if (gameObject.tag == "player")
	{
		Tank* player = static_cast<Tank*>(&gameObject);

		if (player->direction == DIRECTION::RIGHT)
		{
			if (player->animState != TANK_ANIM_STATE::RIGHT_00 && player->animState != TANK_ANIM_STATE::RIGHT_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::RIGHT_00);
			}

			if (player->animState == TANK_ANIM_STATE::RIGHT_00)
			{
				player->SetAnimState(TANK_ANIM_STATE::RIGHT_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::RIGHT_01 + 1];
			}
			else if (player->animState == TANK_ANIM_STATE::RIGHT_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::RIGHT_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::RIGHT_00 + 1];
			}
		}
		else if (player->direction == DIRECTION::LEFT)
		{
			if (player->animState != TANK_ANIM_STATE::LEFT_00 && player->animState != TANK_ANIM_STATE::LEFT_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::LEFT_00);
			}

			if (player->animState == TANK_ANIM_STATE::LEFT_00)
			{
				player->SetAnimState(TANK_ANIM_STATE::LEFT_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::LEFT_01 + 1];
			}
			else if (player->animState == TANK_ANIM_STATE::LEFT_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::LEFT_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::LEFT_00 + 1];
			}
		}
		else if (player->direction == DIRECTION::UP)
		{
			if (player->animState != TANK_ANIM_STATE::UP_00 && player->animState != TANK_ANIM_STATE::UP_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::UP_00);
			}

			if (player->animState == TANK_ANIM_STATE::UP_00)
			{
				player->SetAnimState(TANK_ANIM_STATE::UP_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::UP_01 + 1];
			}
			else if (player->animState == TANK_ANIM_STATE::UP_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::UP_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::UP_00 + 1];
			}
		}
		else if (player->direction == DIRECTION::DOWN)
		{
			if (player->animState != TANK_ANIM_STATE::DOWN_00 && player->animState != TANK_ANIM_STATE::DOWN_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::DOWN_00);
			}

			if (player->animState == TANK_ANIM_STATE::DOWN_00)
			{
				player->SetAnimState(TANK_ANIM_STATE::DOWN_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::DOWN_01 + 1];
			}
			else if (player->animState == TANK_ANIM_STATE::DOWN_01)
			{
				player->SetAnimState(TANK_ANIM_STATE::DOWN_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::DOWN_00 + 1];
			}
		}
	}
	else if (gameObject.tag == "missile")
	{
		Missile* missile = static_cast<Missile*>(&gameObject);

		if (missile->direction == DIRECTION::RIGHT)
		{
			if (missile->animState != MISSILE_ANIM_STATE::FIRE_RIGHT)
			{
				missile->SetAnimState(MISSILE_ANIM_STATE::FIRE_RIGHT);
				Sprites[0] = Sprites[MISSILE_ANIM_STATE::FIRE_RIGHT + 1];
			}
		}
		else if (missile->direction == DIRECTION::LEFT)
		{
			if (missile->animState != MISSILE_ANIM_STATE::FIRE_LEFT)
			{
				missile->SetAnimState(MISSILE_ANIM_STATE::FIRE_LEFT);
				Sprites[0] = Sprites[MISSILE_ANIM_STATE::FIRE_LEFT + 1];
			}
		}
		else if (missile->direction == DIRECTION::UP)
		{
			if (missile->animState != MISSILE_ANIM_STATE::FIRE_UP)
			{
				missile->SetAnimState(MISSILE_ANIM_STATE::FIRE_UP);
				Sprites[0] = Sprites[MISSILE_ANIM_STATE::FIRE_UP + 1];
			}
		}
		else if (missile->direction == DIRECTION::DOWN)
		{
			if (missile->animState != MISSILE_ANIM_STATE::FIRE_DOWN)
			{
				missile->SetAnimState(MISSILE_ANIM_STATE::FIRE_DOWN);
				Sprites[0] = Sprites[MISSILE_ANIM_STATE::FIRE_DOWN + 1];
			}
		}
	}
}
