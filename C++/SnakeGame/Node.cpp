#include "Node.h"

Node::Node()
{
	x = 0;
	y = 0;
	prev = nullptr;
	next = nullptr;
}

Node::~Node()
{
}

void Node::SelfDelete()
{
	prev->next = next;
	next->prev = prev;
}
