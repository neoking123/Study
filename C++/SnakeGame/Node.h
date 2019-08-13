#pragma once

class Node
{
public:
	int x;
	int y;
	int prevX;
	int prevY;
	Node* prev;
	Node* next;

	Node();
	~Node();
};

