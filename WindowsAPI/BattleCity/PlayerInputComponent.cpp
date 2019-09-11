#include "PlayerInputComponent.h"
#include "Tank.h"

void PlayerInputComponent::Update(GameObject & gameObject)
{
	if (gameObject.tag == "player")
	{
		Tank* player = static_cast<Tank*>(&gameObject);

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (player->transform.position.x < 24 + 12 * 32)
			{
				player->SetDirection(DIRECTION::RIGHT);
				player->fireDirection = DIRECTION::RIGHT;
			}
			else
				player->SetDirection(DIRECTION::STOP);
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (player->transform.position.x > 24)
			{
				player->SetDirection(DIRECTION::LEFT);
				player->fireDirection = DIRECTION::LEFT;
			}
			else
				player->SetDirection(DIRECTION::STOP);
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (player->transform.position.y > 24)
			{
				player->SetDirection(DIRECTION::UP);
				player->fireDirection = DIRECTION::UP;
			}
			else
				player->SetDirection(DIRECTION::STOP);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (player->transform.position.y < 24 + 12 * 32)
			{
				player->SetDirection(DIRECTION::DOWN);
				player->fireDirection = DIRECTION::DOWN;
			}
			else
				player->SetDirection(DIRECTION::STOP);
		}
		else
			player->SetDirection(DIRECTION::STOP);

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			player->Fire();
		}
	}
	
}
