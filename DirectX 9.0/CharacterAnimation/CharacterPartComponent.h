#pragma once
#include <d3dx9.h>

class CharacterPartCompoenent;

__interface CharacterPartInterface
{
	D3DXMATRIXA16 GetRotationTranslatation();
};

class CharacterPartCompoenent abstract : public CharacterPartInterface
{
protected:
	D3DXMATRIXA16	matTranslation;
	D3DXMATRIXA16	matRotation;

public:
	virtual ~CharacterPartCompoenent() {}
};

