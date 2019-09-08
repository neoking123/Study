#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Character.h"
#include "FireRing.h"
#include "CircusGame.h"

void PhysicsComponent::Update(Character & character)
{
	if (!character.isJump && !character.isDead)
	{
		Move(character);
	}
	else if (character.isJump && !character.isDead)
	{
		Jump(character);
	}

	CheckCollision(character);
	SyncClliderPos(character);
}

void PhysicsComponent::Update(FireRing & firering)
{
	Move(firering);
	SyncClliderPos(firering);
}

void PhysicsComponent::SetColliderBox(SIZE boxSize)
{
	colliderSize = boxSize;
}

RECT PhysicsComponent::GetColliderBox()
{
	return colliderBox;
}

void PhysicsComponent::SyncClliderPos(GameObject & gameObject)
{
	colliderBox = { gameObject.transform.position.x + 33 - (colliderSize.cx / 2), gameObject.transform.position.y + 31 - (colliderSize.cy / 2), gameObject.transform.position.x + 33 + (colliderSize.cx / 2), gameObject.transform.position.y + 31 + (colliderSize.cy / 2) };
}

void PhysicsComponent::SyncClliderPos(FireRing& fireRing)
{
	colliderBox = { fireRing.transform.position.x + 24 - (colliderSize.cx / 2), fireRing.transform.position.y + 160 - (colliderSize.cy / 2), fireRing.transform.position.x + 24 + (colliderSize.cx / 2), fireRing.transform.position.y + 160 + (colliderSize.cy / 2) };
}

void PhysicsComponent::Move(Character & character)
{
	character.transform.position.x += character.speed * character.direction;
}

void PhysicsComponent::Move(FireRing & fireRing)
{
	fireRing.transform.position.x += fireRing.speed;
}

void PhysicsComponent::Jump(Character & character)
{
	if (character.direction == DIRECTION::RIGHT)
	{
		if (character.transform.position.x < 4470)
		{
			character.transform.position.x += character.speed;
		}
	}
	else if (character.direction == DIRECTION::LEFT)
	{
		if (character.transform.position.x > 100)
		{
			character.transform.position.x -= character.speed;
		}
	}

	jumpTime += 5;
	character.transform.position.y -= round(sin(DegreesToRadians(jumpTime))) * character.jumpPower;

	if (jumpTime > 360)
	{
		jumpTime = 0;
		character.isJump = false;
	}
}

void PhysicsComponent::CheckCollision(Character& character)
{
	vector<GameObject*> colliders = CircusGame::GetInstance()->GetAllColliders();
	RECT rcTemp;

	for (auto iter = colliders.begin(); iter != colliders.end(); iter++)
	{
		FireRing* fireRing = static_cast<FireRing*>(*iter);
		if ( IntersectRect(&rcTemp, &colliderBox, &fireRing->GetColliderBox()) )
		{
			character.isDead = true;

			for (auto iter = colliders.begin(); iter != colliders.end(); iter++)
			{
				FireRing* fireRing = static_cast<FireRing*>(*iter);
				fireRing->speed = 0;
			}
		}
	}
}
