#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Tank.h"
#include "Missile.h"

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

void PhysicsComponent::Update(GameObject & gameObject, float elapseTime)
{
	Move(gameObject, elapseTime);
}

void PhysicsComponent::SetColliderBox(SIZE boxSize)
{
	colliderSize = boxSize;
}

void PhysicsComponent::SetColliderBox(GameObject& gameObject, SIZE boxSize)
{
	colliderSize = boxSize;
	colliderBox = { gameObject.transform.position.x + 10, gameObject.transform.position.y + 10, gameObject.transform.position.x + colliderSize.cx, gameObject.transform.position.y + colliderSize.cy };
}

RECT PhysicsComponent::GetColliderBox()
{
	return colliderBox;
}

void PhysicsComponent::SyncClliderPos(GameObject & gameObject)
{
	colliderBox = { gameObject.transform.position.x + 33 - (colliderSize.cx / 2), gameObject.transform.position.y + 31 - (colliderSize.cy / 2), gameObject.transform.position.x + 33 + (colliderSize.cx / 2), gameObject.transform.position.y + 31 + (colliderSize.cy / 2) };
}
