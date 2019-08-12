#pragma once
#include "Node.h"
#include "Map.h"
#include <conio.h>

class Node;

class Player
{
	Node* head;
	Node* tail;
	static int nodeCount;
	char input;

public:
	bool death;

	Player();
	~Player();

	void Init(Map& map);
	void MoveHead(Map& map);
	void MoveDirection(Map& map);
	void MoveNode(Node* node, Map& map);
	void InsertNode(Map& map);
	void TrailNode(Map& map);
	void CheckColision(Map& map);
	static int PrintNodeCount(); // 정적멤버함수
};

