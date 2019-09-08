#include "PhysicsComponent.h"
#include "Character.h"

void PhysicsComponent::Update(Character & character)
{
	character.transform.position.x += character.speed * character.direction;
}
