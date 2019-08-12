#pragma once
enum Direction
{
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT
};

class Node
{
public:
	int x;
	int y;
	Node* prev;
	Node* next;
	int prevDirection; // 이전에 움직인 방향

	Node();
	~Node();

	void SelfDelete();

public:
	Node();
	~Node();
};

