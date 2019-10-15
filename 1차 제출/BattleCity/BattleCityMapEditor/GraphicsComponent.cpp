#include "GraphicsComponent.h"
#include "BitMap.h"
#include "GameObject.h"

void GraphicsComponent::Update(GameObject& gameObject, HDC hdc)
{
	Sprites[0]->Draw(hdc, gameObject.transform.position.x, gameObject.transform.position.y);
}

void GraphicsComponent::AddSprite(BitMap & bitmap)
{
	Sprites.push_back(&bitmap);
}

void GraphicsComponent::UpdateAnim(GameObject& gameObject)
{
	
}
