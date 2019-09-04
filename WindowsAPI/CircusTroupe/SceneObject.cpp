#include "SceneObject.h"
#include "BitMap.h"


SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::Init(int index, POINT pos,int spriteNum)
{
	this->index = index;
	position = pos;
	sprites.reserve(spriteNum);
}

void SceneObject::Draw(HDC hdc)
{
	if (!sprites.empty())
	{
		sprites[0]->Draw(hdc, position.x, position.y);
	}
}

void SceneObject::AddSprite(BitMap * bitmap)
{
	sprites.push_back(bitmap);
}

POINT SceneObject::GetPosition()
{
	return position;
}
