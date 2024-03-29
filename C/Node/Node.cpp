#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;

struct Node
{
	int data;
	Node* pNext;

	Node(int n = 0, Node* p = nullptr)
	{
		data = n;
		pNext = p;
	}
};

void deleteNode(Node* head, int nPlace)
{
	Node* scan = head->pNext;

	while (true)
	{
		if (scan == nullptr)
			break;
		else
		{
			for (int i = 0; i < nPlace; i++)
			{
				if (scan->pNext == nullptr)
					break;
				else
				{
					Node* remove = scan->pNext;
					scan->pNext = scan->pNext->pNext;
					delete remove;
				}
			}

			if (nPlace == 0)
			{
				head->pNext = scan->pNext;
				delete scan;
			}

			break;
		}
	}
}

void popFront(Node* head)
{
	Node* scan = head->pNext;

	while (true)
	{
		if (scan == nullptr)
			break;
		else
		{
			head->pNext = scan->pNext;
			delete scan;

			break;
		}
	}
}

void insertNode(Node* head, Node* insert, int nPlace)
{
	while (true)
	{
		if (head->pNext == nullptr)
		{
			head->pNext = insert;
			break;
		}
		else
		{
			for(int i = 0; i < nPlace; i++)
			{
				if (head->pNext->pNext == nullptr)
					break;
				else
					head->pNext = head->pNext->pNext;
			}

			head->pNext = insert;
			break;
		}
	}
}

void pushFront(Node* head, Node* insert)
{
	while (true)
	{
		if (head->pNext == nullptr)
		{
			head->pNext = insert;
			break;
		}
		else
		{
			insert->pNext = head->pNext;
			head->pNext = insert;
			break;
		}
	}
}

int main()
{
	int num = 0;

	Node* head = new Node();
	Node* scan = new Node();

	while (true)
	{
		cin >> num;
		if (num == 0)
			break;

		if (head->pNext == nullptr)
		{
			Node* insert = new Node();
			head->pNext = insert;
			insert->data = num;
		}
		else
		{
			scan = head->pNext;

			while (true)
			{
				if (scan->pNext == nullptr)
					break;
				else
					scan = scan->pNext;
			}

			Node* insert = new Node();
			scan->pNext = insert;
			insert->data = num;
		}
	}

	scan = head->pNext;
	while (true)
	{
		if (scan == nullptr)
			break;
		else
		{
			cout << scan->data << " ";
			scan = scan->pNext;
		}
	}

	// 노드 메모리 해제
	scan = head->pNext;
	while (true)
	{
		if (scan == nullptr)
			break;
		else
		{
			Node* temp = scan;
			scan = scan->pNext;
			delete temp;
		}
	}

	delete head;
	delete scan;

	return 0;
}