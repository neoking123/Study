#include "SceneObject.h"
#include "BitMap.h"


SceneObject::SceneObject()
{
}

SceneObject::~SceneObject()
{
}

void SceneObject::Init(POINT pos,int spriteNum)
{
	position = pos;
	sprites.reserve(spriteNum);
	isCharacter = false;
}

void SceneObject::Draw(HDC hdc)
{
	if (!sprites.empty())
	{
		sprites[0]->Draw(hdc, position.x, position.y);
	}
}

void SceneObject::DrawFixedPosition(HDC hdc, int x)
{
	if (!sprites.empty())
	{
		sprites[0]->Draw(hdc, x, position.y);
	}
}

bool SceneObject::IsCharacter()
{
	return isCharacter;
}

void SceneObject::AddSprite(BitMap * bitmap)
{
	sprites.push_back(bitmap);
}

void SceneObject::SetSprite(int index)
{
	sprites.at(0) = sprites.at(index);
}

POINT SceneObject::GetPosition()
{
	return position;
}
