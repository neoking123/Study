#include "pch.h"
#include <iostream>
using namespace std;

struct Node
{
	int data = 0;
	Node* pNext = nullptr;

	Node(int n, Node* p)
	{
		data = n;
		pNext = p;
	}
};

class List
{
	Node* head;
	Node* tail;
	int size;

	List(int data);
	void PushBack(int data);
};

List::List(int data)
{
	head = tail = new Node(data, nullptr);
	size = 1;
}

// 리스트 맨 앞 삽입
void List::PushBack(int data)
{

}


void deleteNode(Node* head, int nPlace)
{
	Node* pTemp = head;
	for (int i = 0; i < nPlace; i++)
	{
		if (pTemp->pNext != nullptr)
		{
			pTemp = pTemp->pNext;
		}
	}

	pTemp = pTemp->pNext->pNext;
	delete pTemp->pNext;
}

void insertNode(Node* head, Node* insert, int nPlace)
{
	Node* pTemp = head;

	for (int i = 0; i < nPlace; i++)
	{
		if (pTemp->pNext != nullptr)
		{
			pTemp = pTemp->pNext;
		}
	}

	insert = pTemp->pNext;
	pTemp->pNext = insert;
}

int main()
{
	

	Node* insert = nullptr;

	insertNode(head, insert, 1);

	cout << head;

	return 0;
}