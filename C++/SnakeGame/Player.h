#pragma once
#include "Node.h"
#include "Map.h"

class Node;

int nodeCount;

class Player
{
	Node* head;
	Node* tail;
	static int nodeCount;


public:
	Player();
	~Player();

	void MoveHead(Map& map);
	void MoveNode(Map& map, Node* newNode, Direction direction);
	void InsertNode(Node* tail, Node* newNode, Map& map);
	void TrailNode(Map& map);
};

