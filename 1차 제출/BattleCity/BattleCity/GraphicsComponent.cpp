#include "GraphicsComponent.h"
#include "BitMap.h"
#include "GameObject.h"
#include "Tank.h"
#include "Missile.h"
#include "Tile.h"
#include "Enemy.h"

void GraphicsComponent::Render(GameObject & gameObject, HDC hdc)
{
	if (gameObject.tag == "tile_brick" || gameObject.tag == "tile_iron")
	{
		Tile* tile = dynamic_cast<Tile*>(&gameObject);
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
		Tank* player = dynamic_cast<Tank*>(&gameObject);

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

		if (bombTime < 0.025f)
		{
			bombTime += elapseTime;
			return;
		}
		bombTime = 0.0f;

		if (player->animState == TANK_ANIM_STATE::EXPLOSION_START)
		{
			player->SetAnimState(TANK_ANIM_STATE::BOMB_00);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_00 + 1];
		}
		else if (player->animState == TANK_ANIM_STATE::BOMB_00)
		{
			player->SetAnimState(TANK_ANIM_STATE::BOMB_01);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_01 + 1];
		}
		else if (player->animState == TANK_ANIM_STATE::BOMB_01)
		{
			player->SetAnimState(TANK_ANIM_STATE::BOMB_02);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_02 + 1];
		}
		else if (player->animState == TANK_ANIM_STATE::BOMB_02)
		{
			player->SetPosition(player->transform.position.x - 16, player->transform.position.y - 16);
			player->SetAnimState(TANK_ANIM_STATE::BOMB_03);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_03 + 1];
		}
		else if (player->animState == TANK_ANIM_STATE::BOMB_03 && !player->isEndBomb)
		{
			player->SetAnimState(TANK_ANIM_STATE::BOMB_04);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_04 + 1];
		}
		else if (player->animState == TANK_ANIM_STATE::BOMB_04)
		{
			player->SetAnimState(TANK_ANIM_STATE::BOMB_03);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_03 + 1];
			player->isEndBomb = true;
		}
		else if (player->animState == TANK_ANIM_STATE::BOMB_03 && player->isEndBomb)
		{
			player->SetPosition(player->transform.position.x + 16, player->transform.position.y + 16);
			player->SetAnimState(TANK_ANIM_STATE::UP_00);
			Sprites[0] = Sprites[TANK_ANIM_STATE::UP_00 + 1];
			player->isEndAnim = true;
		}
	}
	else if (gameObject.tag == "missile_player" || gameObject.tag == "missile_enemy")
	{
		Missile* missile = dynamic_cast<Missile*>(&gameObject);

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

		if (bombTime < 0.025f)
		{
			bombTime += elapseTime;
			return;
		}
		bombTime = 0.0f;

		if (missile->animState == MISSILE_ANIM_STATE::BOMB_START)
		{
			missile->SetPosition(missile->transform.position.x - 12, missile->transform.position.y - 12);
			missile->SetAnimState(MISSILE_ANIM_STATE::BOMB_0);
			Sprites[0] = Sprites[MISSILE_ANIM_STATE::BOMB_0 + 1];
		}
		else if (missile->animState == MISSILE_ANIM_STATE::BOMB_0)
		{
			missile->SetAnimState(MISSILE_ANIM_STATE::BOMB_1);
			Sprites[0] = Sprites[MISSILE_ANIM_STATE::BOMB_1 + 1];
		}
		else if (missile->animState == MISSILE_ANIM_STATE::BOMB_1)
		{
			missile->SetAnimState(MISSILE_ANIM_STATE::BOMB_2);
			Sprites[0] = Sprites[MISSILE_ANIM_STATE::BOMB_2 + 1];
			missile->SetPosition(0, 0);
			missile->isFired = false;
		}
	}
	else if (gameObject.tag == "enemy")
	{
		Enemy* enemy = dynamic_cast<Enemy*>(&gameObject);

		if (enemy->direction == DIRECTION::RIGHT)
		{
			if (enemy->animState != TANK_ANIM_STATE::RIGHT_00 && enemy->animState != TANK_ANIM_STATE::RIGHT_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::RIGHT_00);
			}

			if (enemy->animState == TANK_ANIM_STATE::RIGHT_00)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::RIGHT_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::RIGHT_01 + 1];
			}
			else if (enemy->animState == TANK_ANIM_STATE::RIGHT_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::RIGHT_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::RIGHT_00 + 1];
			}
		}
		else if (enemy->direction == DIRECTION::LEFT)
		{
			if (enemy->animState != TANK_ANIM_STATE::LEFT_00 && enemy->animState != TANK_ANIM_STATE::LEFT_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::LEFT_00);
			}

			if (enemy->animState == TANK_ANIM_STATE::LEFT_00)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::LEFT_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::LEFT_01 + 1];
			}
			else if (enemy->animState == TANK_ANIM_STATE::LEFT_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::LEFT_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::LEFT_00 + 1];
			}
		}
		else if (enemy->direction == DIRECTION::UP)
		{
			if (enemy->animState != TANK_ANIM_STATE::UP_00 && enemy->animState != TANK_ANIM_STATE::UP_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::UP_00);
			}

			if (enemy->animState == TANK_ANIM_STATE::UP_00)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::UP_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::UP_01 + 1];
			}
			else if (enemy->animState == TANK_ANIM_STATE::UP_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::UP_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::UP_00 + 1];
			}
		}
		else if (enemy->direction == DIRECTION::DOWN)
		{
			if (enemy->animState != TANK_ANIM_STATE::DOWN_00 && enemy->animState != TANK_ANIM_STATE::DOWN_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::DOWN_00);
			}

			if (enemy->animState == TANK_ANIM_STATE::DOWN_00)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::DOWN_01);
				Sprites[0] = Sprites[TANK_ANIM_STATE::DOWN_01 + 1];
			}
			else if (enemy->animState == TANK_ANIM_STATE::DOWN_01)
			{
				enemy->SetAnimState(TANK_ANIM_STATE::DOWN_00);
				Sprites[0] = Sprites[TANK_ANIM_STATE::DOWN_00 + 1];
			}
		}

		if (bombTime < 0.025f)
		{
			bombTime += elapseTime;
			return;
		}
		bombTime = 0.0f;

		if (enemy->animState == TANK_ANIM_STATE::EXPLOSION_START)
		{
			enemy->SetAnimState(TANK_ANIM_STATE::BOMB_00);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_00 + 1];
		}
		else if (enemy->animState == TANK_ANIM_STATE::BOMB_00)
		{
			enemy->SetAnimState(TANK_ANIM_STATE::BOMB_01);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_01 + 1];
		}
		else if (enemy->animState == TANK_ANIM_STATE::BOMB_01)
		{
			enemy->SetAnimState(TANK_ANIM_STATE::BOMB_02);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_02 + 1];
		}
		else if (enemy->animState == TANK_ANIM_STATE::BOMB_02)
		{
			enemy->SetPosition(enemy->transform.position.x - 16, enemy->transform.position.y - 16);
			enemy->SetAnimState(TANK_ANIM_STATE::BOMB_03);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_03 + 1];
		}
		else if (enemy->animState == TANK_ANIM_STATE::BOMB_03)
		{
			enemy->SetAnimState(TANK_ANIM_STATE::BOMB_04);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_04 + 1];
		}
		else if (enemy->animState == TANK_ANIM_STATE::BOMB_04)
		{
			enemy->SetPosition(enemy->transform.position.x + 16, enemy->transform.position.y + 16);
			enemy->SetAnimState(TANK_ANIM_STATE::BOMB_03);
			Sprites[0] = Sprites[TANK_ANIM_STATE::BOMB_03 + 1];
			enemy->isEndAnim = true;
		}
	}
	else if (gameObject.tag == "tile_egle")
	{
		if (bombTime < 0.025f)
		{
			bombTime += elapseTime;
			return;
		}
		bombTime = 0.0f;

		Tile* egle = dynamic_cast<Tile*>(&gameObject);
		if (egle->animState == TILE_ANIM_STATE::EGLE_BOMB_START)
		{
			egle->SetAnimState(TILE_ANIM_STATE::EGLE_BOMB_0);
			Sprites[0] = Sprites[TILE_ANIM_STATE::EGLE_BOMB_0 + 1];
		}
		else if (egle->animState == TILE_ANIM_STATE::EGLE_BOMB_0)
		{
			egle->SetAnimState(TILE_ANIM_STATE::EGLE_BOMB_1);
			Sprites[0] = Sprites[TILE_ANIM_STATE::EGLE_BOMB_1 + 1];
		}
		else if (egle->animState == TILE_ANIM_STATE::EGLE_BOMB_1)
		{
			egle->SetAnimState(TILE_ANIM_STATE::EGLE_BOMB_2);
			Sprites[0] = Sprites[TILE_ANIM_STATE::EGLE_BOMB_2 + 1];
		}
		else if (egle->animState == TILE_ANIM_STATE::EGLE_BOMB_2)
		{
			egle->SetPosition(egle->transform.position.x - 16, egle->transform.position.y - 16);
			egle->SetAnimState(TILE_ANIM_STATE::EGLE_BOMB_3);
			Sprites[0] = Sprites[TILE_ANIM_STATE::EGLE_BOMB_3 + 1];
		}
		else if (egle->animState == TILE_ANIM_STATE::EGLE_BOMB_3)
		{
			egle->SetAnimState(TILE_ANIM_STATE::EGLE_BOMB_4);
			Sprites[0] = Sprites[TILE_ANIM_STATE::EGLE_BOMB_4 + 1];
		}
		else if (egle->animState == TILE_ANIM_STATE::EGLE_BOMB_4)
		{
			egle->SetPosition(egle->transform.position.x + 16, egle->transform.position.y + 16);
			egle->SetAnimState(TILE_ANIM_STATE::EGLE_FLAG);
			Sprites[0] = Sprites[TILE_ANIM_STATE::EGLE_FLAG + 1];

			egle->phsics1.SetColliderBox(*egle, SIZE{ 0, 0 });
			egle->phsics2.SetColliderBox(*egle, SIZE{ 0, 0 });
			egle->phsics3.SetColliderBox(*egle, SIZE{ 0, 0 });
			egle->phsics4.SetColliderBox(*egle, SIZE{ 0, 0 });
		}
		
	}

}
