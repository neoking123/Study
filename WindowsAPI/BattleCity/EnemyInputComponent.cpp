#include "EnemyInputComponent.h"
#include "Enemy.h"

void EnemyInputComponent::Update(GameObject & gameObject)
{
	if (gameObject.tag == "enemy")
	{
		Enemy* enemy = dynamic_cast<Enemy*>(&gameObject);

		if (enemy->isDead)
			return;

		if (directionChangeCount > randomDirectionChangeDelayCount)
		{
			randomDirection = rand() % 5;
			randomDirectionChangeDelayCount = rand() % 50 + 20;
			directionChangeCount = 0;
		}
		else
		{
			directionChangeCount++;
		}

		if (randomDirection == 0)
		{
			if (enemy->transform.position.x < 24 + 12 * 32)
			{
				enemy->SetDirection(DIRECTION::RIGHT);
				enemy->fireDirection = DIRECTION::RIGHT;
			}
			else
				enemy->SetDirection(DIRECTION::STOP);
		}
		else if (randomDirection == 1)
		{
			if (enemy->transform.position.x > 24)
			{
				enemy->SetDirection(DIRECTION::LEFT);
				enemy->fireDirection = DIRECTION::LEFT;
			}
			else
				enemy->SetDirection(DIRECTION::STOP);
		}
		else if (randomDirection == 2)
		{
			if (enemy->transform.position.y > 24)
			{
				enemy->SetDirection(DIRECTION::UP);
				enemy->fireDirection = DIRECTION::UP;
			}
			else
				enemy->SetDirection(DIRECTION::STOP);
		}
		else if (randomDirection == 3)
		{
			if (enemy->transform.position.y < 24 + 12 * 32)
			{
				enemy->SetDirection(DIRECTION::DOWN);
				enemy->fireDirection = DIRECTION::DOWN;
			}
			else
				enemy->SetDirection(DIRECTION::STOP);
		}
		else
			enemy->SetDirection(DIRECTION::STOP);

		enemy->Fire();
	}
}
