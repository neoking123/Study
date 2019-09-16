#include "PhysicsComponent.h"
#include "BattleCity.h"
#include "GameObject.h"
#include "Tank.h"
#include "Missile.h"
#include "Tile.h"
#include "Enemy.h"

void PhysicsComponent::Move(GameObject & gameObject, float elapseTime)
{
	int elapseTimeInt = ceil(elapseTime);
	if (gameObject.tag == "player")
	{
		Tank* player = static_cast<Tank*>(&gameObject);

		if (player->direction == DIRECTION::LEFT)
		{
			player->transform.position.x -= player->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				player->transform.position.x += player->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
		else if (player->direction == DIRECTION::RIGHT)
		{
			player->transform.position.x += player->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				player->transform.position.x -= player->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
		else if (player->direction == DIRECTION::UP)
		{
			player->transform.position.y -= player->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				player->transform.position.y += player->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
		else if (player->direction == DIRECTION::DOWN)
		{
			player->transform.position.y += player->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				player->transform.position.y -= player->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
	}
	else if(gameObject.tag == "missile_player" || gameObject.tag == "missile_enemy")
	{
		Missile* missile = static_cast<Missile*>(&gameObject);
		if (missile->direction == DIRECTION::LEFT)
		{
			missile->transform.position.x -= missile->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject)
				|| missile->transform.position.x < MAP_MARGINE_WIDTH)
			{
				missile->Reset();
				SyncClliderPos(gameObject);
			}
			
		}
		else if (missile->direction == DIRECTION::RIGHT)
		{
			missile->transform.position.x += missile->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject)
				|| missile->transform.position.x > MAP_MARGINE_WIDTH + TILE_WIDTH_NUM * TILE_SIZE)
			{
				missile->Reset();
				SyncClliderPos(gameObject);
			}
		}
		else if (missile->direction == DIRECTION::UP)
		{
			missile->transform.position.y -= missile->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject)
				|| missile->transform.position.y < MAP_MARGINE_HEIGHT)
			{
				missile->Reset();
				SyncClliderPos(gameObject);
			}
		}
		else if (missile->direction == DIRECTION::DOWN)
		{
			missile->transform.position.y += missile->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject)
				|| missile->transform.position.y > MAP_MARGINE_HEIGHT + TILE_HEIGHT_NUM * TILE_SIZE)
			{
				missile->Reset();
				SyncClliderPos(gameObject);
			}
		}
	}
	else if (gameObject.tag == "enemy")
	{
		Enemy* enemy = static_cast<Enemy*>(&gameObject);

		if (enemy->direction == DIRECTION::LEFT)
		{
			enemy->transform.position.x -= enemy->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				enemy->transform.position.x += enemy->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
		else if (enemy->direction == DIRECTION::RIGHT)
		{
			enemy->transform.position.x += enemy->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				enemy->transform.position.x -= enemy->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
		else if (enemy->direction == DIRECTION::UP)
		{
			enemy->transform.position.y -= enemy->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				enemy->transform.position.y += enemy->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
		else if (enemy->direction == DIRECTION::DOWN)
		{
			enemy->transform.position.y += enemy->speed * elapseTimeInt;
			SyncClliderPos(gameObject);
			if (CheckBlockCollision(gameObject) || CheckTankCollision(gameObject))
			{
				enemy->transform.position.y -= enemy->speed * elapseTimeInt;
				SyncClliderPos(gameObject);
			}
		}
	}
}

bool PhysicsComponent::CheckBlockCollision(GameObject& gameObject)
{
	vector<Tile*> tiles = BattleCity::GetInstance()->GetTiles();
	RECT rcTemp;
	bool isCollide = false;

	for (auto iter = tiles.begin(); iter != tiles.end(); iter++)
	{
		if ( IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics1.GetColliderBox()) )
		{
			if (gameObject.tag == "player")
			{
				Tank* player = static_cast<Tank*>(&gameObject);
				player->isCollide = true;
			}
			else if (gameObject.tag == "enemy")
			{
				Enemy* enemy = static_cast<Enemy*>(&gameObject);
				enemy->isCollide = true;
			}
			else if (gameObject.tag == "missile_player" || gameObject.tag == "missile_enemy")
			{
				Missile* missile = static_cast<Missile*>(&gameObject);
				missile->isCollide = true;

				RECT rt = (*iter)->phsics1.GetColliderBox();
				SIZE sz = (*iter)->phsics1.colliderSize;
				if (missile->direction == DIRECTION::RIGHT)
				{
					(*iter)->phsics1.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics1.left + 8, (*iter)->phsics1.top, (*iter)->phsics1.right + 8, (*iter)->phsics1.bottom);
				}
				else if (missile->direction == DIRECTION::LEFT)
				{
					(*iter)->phsics1.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics1.left, (*iter)->phsics1.top, (*iter)->phsics1.right, (*iter)->phsics1.bottom);
				}
				else if (missile->direction == DIRECTION::UP)
				{
					(*iter)->phsics1.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics1.left, (*iter)->phsics1.top, (*iter)->phsics1.right, (*iter)->phsics1.bottom);
				}
				else if (missile->direction == DIRECTION::DOWN)
				{
					(*iter)->phsics1.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics1.left, (*iter)->phsics1.top + 8, (*iter)->phsics1.right, (*iter)->phsics1.bottom + 8);
				}
			}
			isCollide = true;
		}

		if (IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics2.GetColliderBox()))
		{
			if (gameObject.tag == "player")
			{
				Tank* player = static_cast<Tank*>(&gameObject);
				player->isCollide = true;
			}
			else if (gameObject.tag == "enemy")
			{
				Enemy* enemy = static_cast<Enemy*>(&gameObject);
				enemy->isCollide = true;
			}
			else if (gameObject.tag == "missile_player" || gameObject.tag == "missile_enemy")
			{
				Missile* missile = static_cast<Missile*>(&gameObject);
				missile->isCollide = true;

				RECT rt = (*iter)->phsics2.GetColliderBox();
				SIZE sz = (*iter)->phsics2.colliderSize;
				if (missile->direction == DIRECTION::RIGHT)
				{
					(*iter)->phsics2.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics2.left + 8, (*iter)->phsics2.top, (*iter)->phsics2.right + 8, (*iter)->phsics2.bottom);
				}
				else if (missile->direction == DIRECTION::LEFT)
				{
					(*iter)->phsics2.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics2.left, (*iter)->phsics2.top, (*iter)->phsics2.right, (*iter)->phsics2.bottom);
				}
				else if (missile->direction == DIRECTION::UP)
				{
					(*iter)->phsics2.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics2.left, (*iter)->phsics2.top, (*iter)->phsics2.right, (*iter)->phsics2.bottom);
				}
				else if (missile->direction == DIRECTION::DOWN)
				{
					(*iter)->phsics2.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics2.left, (*iter)->phsics2.top + 8, (*iter)->phsics2.right, (*iter)->phsics2.bottom + 8);
				}
			}
			isCollide = true;
		}

		if (IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics3.GetColliderBox()))
		{
			if (gameObject.tag == "player")
			{
				Tank* player = static_cast<Tank*>(&gameObject);
				player->isCollide = true;
			}
			else if (gameObject.tag == "enemy")
			{
				Enemy* enemy = static_cast<Enemy*>(&gameObject);
				enemy->isCollide = true;
			}
			else if (gameObject.tag == "missile_player" || gameObject.tag == "missile_enemy")
			{
				Missile* missile = static_cast<Missile*>(&gameObject);
				missile->isCollide = true;

				RECT rt = (*iter)->phsics3.GetColliderBox();
				SIZE sz = (*iter)->phsics3.colliderSize;
				if (missile->direction == DIRECTION::RIGHT)
				{
					(*iter)->phsics3.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics3.left + 8, (*iter)->phsics3.top, (*iter)->phsics3.right + 8, (*iter)->phsics3.bottom);
				}
				else if (missile->direction == DIRECTION::LEFT)
				{
					(*iter)->phsics3.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics3.left, (*iter)->phsics3.top, (*iter)->phsics3.right, (*iter)->phsics3.bottom);
				}
				else if (missile->direction == DIRECTION::UP)
				{
					(*iter)->phsics3.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics3.left, (*iter)->phsics3.top, (*iter)->phsics3.right, (*iter)->phsics3.bottom);
				}
				else if (missile->direction == DIRECTION::DOWN)
				{
					(*iter)->phsics3.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics3.left, (*iter)->phsics3.top + 8, (*iter)->phsics3.right, (*iter)->phsics3.bottom + 8);
				}
			}
			isCollide = true;
		}

		if (IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics4.GetColliderBox()))
		{
			if (gameObject.tag == "player")
			{
				Tank* player = static_cast<Tank*>(&gameObject);
				player->isCollide = true;
			}
			else if (gameObject.tag == "enemy")
			{
				Enemy* enemy = static_cast<Enemy*>(&gameObject);
				enemy->isCollide = true;
			}
			else if (gameObject.tag == "missile_player" || gameObject.tag == "missile_enemy")
			{
				Missile* missile = static_cast<Missile*>(&gameObject);
				missile->isCollide = true;

				RECT rt = (*iter)->phsics4.GetColliderBox();
				SIZE sz = (*iter)->phsics4.colliderSize;
				if (missile->direction == DIRECTION::RIGHT)
				{
					(*iter)->phsics4.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics4.left + 8, (*iter)->phsics4.top, (*iter)->phsics4.right + 8, (*iter)->phsics4.bottom);
				}
				else if (missile->direction == DIRECTION::LEFT)
				{
					(*iter)->phsics4.SetColliderBox(**iter, SIZE{ sz.cx - 8, sz.cy }, (*iter)->phsics4.left, (*iter)->phsics4.top, (*iter)->phsics4.right, (*iter)->phsics4.bottom);
				}
				else if (missile->direction == DIRECTION::UP)
				{
					(*iter)->phsics4.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics4.left, (*iter)->phsics4.top, (*iter)->phsics4.right, (*iter)->phsics4.bottom);
				}
				else if (missile->direction == DIRECTION::DOWN)
				{
					(*iter)->phsics4.SetColliderBox(**iter, SIZE{ sz.cx, sz.cy - 8 }, (*iter)->phsics4.left, (*iter)->phsics4.top + 8, (*iter)->phsics4.right, (*iter)->phsics4.bottom + 8);
				}
			}
			isCollide = true;
		}
	}

	return isCollide;
}

bool PhysicsComponent::CheckTankCollision(GameObject & gameObject)
{
	vector<Tank*> tanks = BattleCity::GetInstance()->GetTanks();
	RECT rcTemp;
	bool isCollide = false;

	for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
	{
		if (IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics.GetColliderBox()))
		{
			if (gameObject.tag == "player" && (*iter)->tag != "player")
			{
				Tank* player = static_cast<Tank*>(&gameObject);
				player->isCollide = true;
				isCollide = true;
			}
			else if (gameObject.tag == "enemy")
			{
				Tank* tank = static_cast<Tank*>(&gameObject);
				if (tank != *iter)
				{
					Enemy* enemy = static_cast<Enemy*>(&gameObject);
					enemy->isCollide = true;
					isCollide = true;
				}
			}
			else if (gameObject.tag == "missile_player" && (*iter)->tag == "enemy")
			{
				Missile* missile = static_cast<Missile*>(&gameObject);
				missile->isCollide = true;
				isCollide = true;
				(*iter)->Die();
			}
			else if (gameObject.tag == "missile_enemy" && (*iter)->tag == "player")
			{
				Missile* missile = static_cast<Missile*>(&gameObject);
				missile->isCollide = true;
				isCollide = true;
				(*iter)->Die();
			}
		}
	}


	return isCollide;
}

void PhysicsComponent::Update(GameObject & gameObject, float elapseTime)
{
	Move(gameObject, elapseTime);
}

void PhysicsComponent::SetColliderBox(SIZE boxSize)
{
	colliderSize = boxSize;
}

void PhysicsComponent::SetColliderBox(GameObject& gameObject, SIZE boxSize, int left, int top, int right, int bottom)
{
	colliderSize = boxSize;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	colliderBox = { gameObject.transform.position.x + this->left, gameObject.transform.position.y + this->top, gameObject.transform.position.x + colliderSize.cx + this->right, gameObject.transform.position.y + colliderSize.cy + this->bottom };
}

RECT PhysicsComponent::GetColliderBox()
{
	return colliderBox;
}

SIZE PhysicsComponent::GetColliderSize()
{
	return colliderSize;
}

void PhysicsComponent::SyncClliderPos(GameObject & gameObject)
{
	colliderBox = { gameObject.transform.position.x + this->left, gameObject.transform.position.y + this->top, gameObject.transform.position.x + colliderSize.cx + this->right, gameObject.transform.position.y + colliderSize.cy + this->bottom };
}

void PhysicsComponent::RenderColliderBox(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);

	Rectangle(hdc, colliderBox.left, colliderBox.top, colliderBox.right, colliderBox.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}
