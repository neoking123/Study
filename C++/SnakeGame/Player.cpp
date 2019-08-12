#include "Player.h"

int Player::nodeCount = 0;

Player::Player()
{
	head = new Node;
	tail = head;
}

Player::~Player()
{
	delete head;
}

// 초기화
void Player::Init(Map& map)
{
	head->x = WIDTH / 2;
	head->y = HEIGHT / 2;
	input = 'a';
	map.arrMap[head->y][head->x] = PLAYER;
	nodeCount = 1;
	death = false;
}

// 플레이어 이동
void Player::MoveHead(Map& map)
{
	//char input = _getch(); // <conio.h>

	if (input == 'w' && map.arrMap[head->y - 1][head->x] != WALL && map.arrMap[head->y - 1][head->x] != BODY)
	{
		if (map.arrMap[head->y - 1][head->x] == ENEMY)
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y--][head->x] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;

			InsertNode(map);
			TrailNode(map);
			map.SpawnEnemy();
		}
		else 
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y--][head->x] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;

			TrailNode(map);
		}
	}
	else if (input == 's' && map.arrMap[head->y + 1][head->x] != WALL && map.arrMap[head->y + 1][head->x] != BODY)
	{
		if (map.arrMap[head->y + 1][head->x] == ENEMY)
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y++][head->x] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;

			InsertNode(map);
			TrailNode(map);
			map.SpawnEnemy();
		}
		else
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y++][head->x] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;

			TrailNode(map);
		}
	}
	else if (input == 'a' && map.arrMap[head->y][head->x - 1] != WALL && map.arrMap[head->y][head->x - 1] != BODY)
	{
		if (map.arrMap[head->y][head->x - 1] == ENEMY)
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y][head->x--] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;	

			InsertNode(map);
			TrailNode(map);
			map.SpawnEnemy();
		}
		else
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y][head->x--] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;

			TrailNode(map);
		}
	}
	else if (input == 'd' && map.arrMap[head->y][head->x + 1] != WALL && map.arrMap[head->y][head->x + 1] != BODY)
	{
		if (map.arrMap[head->y][head->x + 1] == ENEMY)
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y][head->x++] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;

			InsertNode(map);
			TrailNode(map);
			map.SpawnEnemy();
		}
		else
		{
			head->prevX = head->x;
			head->prevY = head->y;
			map.arrMap[head->y][head->x++] = EMPTY;
			map.arrMap[head->y][head->x] = PLAYER;

			TrailNode(map);
		}
	}
}

// 자동이동
void Player::MoveDirection(Map& map)
{
	if (_kbhit())
	{
		char newInput = _getch();
		if (input == 'w' && newInput != 's')
		{
			input = newInput;
		}
		else if (input == 's' && newInput != 'w')
		{
			input = newInput;
		}
		else if (input == 'a' && newInput != 'd')
		{
			input = newInput;
		}
		else if (input == 'd' && newInput != 'a')
		{
			input = newInput;
		}
	}

	CheckColision(map);
	MoveHead(map);
}

// 노드 이동
void Player::MoveNode(Node* node, Map& map)
{
	map.arrMap[node->y][node->x] = EMPTY;
	node->prevX = node->x;
	node->prevY = node->y;
	node->x = node->prev->prevX;
	node->y = node->prev->prevY;
	map.arrMap[node->y][node->x] = BODY;
}

// 맨 뒤에 노드 추가
void Player::InsertNode(Map & map)
{
	Node* newNode = new Node;
	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;

	tail->x = tail->prev->prevX;
	tail->y = tail->prev->prevY;

	map.arrMap[tail->y][tail->x] = BODY;
	nodeCount++;
}

// 앞 노드들 따라가기
void Player::TrailNode(Map& map)
{
	Node* scan = head->next;

	while (scan != nullptr)
	{
		MoveNode(scan, map);
		scan = scan->next;
	}
}

// 충돌 체크
void Player::CheckColision(Map & map)
{
	if (input == 'w' && (map.arrMap[head->y - 1][head->x] == WALL || map.arrMap[head->y - 1][head->x] == BODY))
	{
		death = true;
	}
	else if (input == 's' && (map.arrMap[head->y + 1][head->x] == WALL || map.arrMap[head->y + 1][head->x] == BODY))
	{
		death = true;
	}
	else if (input == 'a' && (map.arrMap[head->y][head->x - 1] == WALL || map.arrMap[head->y][head->x - 1] == BODY))
	{
		death = true;
	}
	else if (input == 'd' && (map.arrMap[head->y][head->x + 1] == WALL || map.arrMap[head->y][head->x + 1] == BODY))
	{
		death = true;
	}
}

int Player::PrintNodeCount()
{
	return nodeCount;
}

