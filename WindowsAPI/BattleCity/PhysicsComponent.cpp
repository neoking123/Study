#include "PhysicsComponent.h"
#include "BattleCity.h"
#include "GameObject.h"
#include "Tank.h"
#include "Missile.h"
#include "Tile.h"

void PhysicsComponent::Move(GameObject & gameObject, float elapseTime)
{
	int elapseTimeInt = ceil(elapseTime);
	if (gameObject.tag == "player")
	{
		Tank* player = static_cast<Tank*>(&gameObject);

		if (player->direction == DIRECTION::LEFT)
		{
			player->transform.position.x -= player->speed * elapseTimeInt;
		}
		else if (player->direction == DIRECTION::RIGHT)
		{
			player->transform.position.x += player->speed * elapseTimeInt;
		}
		else if (player->direction == DIRECTION::UP)
		{
			player->transform.position.y -= player->speed * elapseTimeInt;
		}
		else if (player->direction == DIRECTION::DOWN)
		{
			player->transform.position.y += player->speed * elapseTimeInt;
		}
	}
	else if(gameObject.tag == "missile")
	{
		Missile* missile = static_cast<Missile*>(&gameObject);
		if (missile->direction == DIRECTION::LEFT)
		{
			missile->transform.position.x -= missile->speed * elapseTimeInt;
		}
		else if (missile->direction == DIRECTION::RIGHT)
		{
			missile->transform.position.x += missile->speed * elapseTimeInt;
		}
		else if (missile->direction == DIRECTION::UP)
		{
			missile->transform.position.y -= missile->speed * elapseTimeInt;
		}
		else if (missile->direction == DIRECTION::DOWN)
		{
			missile->transform.position.y += missile->speed * elapseTimeInt;
		}
	}
}

void PhysicsComponent::CheckBlockCollision(GameObject& gameObject)
{
	vector<Tile*> tiles = BattleCity::GetInstance()->GetTiles();
	RECT rcTemp;

	for (auto iter = tiles.begin(); iter != tiles.end(); iter++)
	{
		if ( IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics1.GetColliderBox()) )
		{
			if (gameObject.tag == "player")
			{
				Tank* player = static_cast<Tank*>(&gameObject);
				player->SetSpeed(0);
			}
			else if (gameObject.tag == "missile")
			{
				Missile* missile = static_cast<Missile*>(&gameObject);
				missile->SetSpeed(0);
			}
		}

		if (IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics2.GetColliderBox()))
		{
			Tank* player = static_cast<Tank*>(&gameObject);
			player->SetSpeed(0);
		}

		if (IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics3.GetColliderBox()))
		{
			Tank* player = static_cast<Tank*>(&gameObject);
			player->SetSpeed(0);
		}

		if (IntersectRect(&rcTemp, &colliderBox, &(*iter)->phsics4.GetColliderBox()))
		{
			Tank* player = static_cast<Tank*>(&gameObject);
			player->SetSpeed(0);
		}
	}
}

void PhysicsComponent::Update(GameObject & gameObject, float elapseTime)
{
	Move(gameObject, elapseTime);
	CheckBlockCollision(gameObject);
	SyncClliderPos(gameObject);
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
