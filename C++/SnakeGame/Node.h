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
	int prevDirection; // ������ ������ ����

	Node();
	~Node();

	void SelfDelete();

public:
	Node();
	~Node();
};

