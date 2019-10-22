#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
}

void Character::Init()
{
	CharacterPart* mainBody = new CharacterPart();
	mainBody->Init(nullptr, 0, 0, 0, 0, 45);
	characterParts.push_back(mainBody);

	CharacterPart* upBody = new CharacterPart();
	upBody->Init(mainBody, 0, 2, 0);
	characterParts.push_back(upBody);

	CharacterPart* neckBody = new CharacterPart();
	neckBody->Init(upBody, 0, 2, 0);
	characterParts.push_back(neckBody);

	CharacterPart* head = new CharacterPart();
	head->Init(neckBody, 0, 2, 0, 0, 45);
	characterParts.push_back(head);

	CharacterPart* shoulderL = new CharacterPart();
	shoulderL->Init(upBody, -2, 2, 0);
	characterParts.push_back(shoulderL);

	CharacterPart* armL = new CharacterPart();
	armL->Init(shoulderL, -2, 0, 0);
	characterParts.push_back(armL);

	CharacterPart* shoulderR = new CharacterPart();
	shoulderR->Init(upBody, 2, 2, 0);
	characterParts.push_back(shoulderR);

	CharacterPart* armR = new CharacterPart();
	armR->Init(shoulderR, 2, 0, 0);
	characterParts.push_back(armR);

	CharacterPart* legL = new CharacterPart();
	legL->Init(mainBody, -1.5f, -2, 0);
	characterParts.push_back(legL);

	CharacterPart* footL = new CharacterPart();
	footL->Init(legL, 0, -2, -1);
	characterParts.push_back(footL);

	CharacterPart* legR = new CharacterPart();
	legR->Init(mainBody, 1.5f, -2, 0);
	characterParts.push_back(legR);

	CharacterPart* footR = new CharacterPart();
	footR->Init(legR, 0, -2, -1);
	characterParts.push_back(footR);
}

void Character::DrawMesh(LPDIRECT3DDEVICE9 D3DDevice, LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DINDEXBUFFER9 indexBuffer, DWORD fvf, int size)
{
	for (auto iter = characterParts.begin(); iter != characterParts.end(); iter++)
	{
		(*iter)->DrawMesh(D3DDevice, vertexBuffer, indexBuffer, fvf, size);
	}
}
