#include "Player.h"
#include <conio.h>

Player::Player()
{
	Node* playerNode = new Node();
	head = playerNode;
	tail = playerNode;
	nodeCount = 0;
}

Player::~Player()
{
	delete head;
}

// 플레이어 이동
void Player::MoveHead(Map& map)
{
	char input = getch(); // <conio.h>

	if (input == 'w' && map.arrMap[head->y][head->x] != mapState::WALL)
	{
		head->y--;
		map.arrMap[head->y - 1][head->x] == mapState::PLAYER;
		map.arrMap[head->y][head->x] == mapState::EMPTY;
		head->prevDirection = Direction::FORWARD;
	}
	else if (input == 's' && map.arrMap[head->y + 1][head->x] != mapState::WALL)
	{
		head->y++;
		map.arrMap[head->y + 1][head->x] == mapState::PLAYER;
		map.arrMap[head->y][head->x] == mapState::EMPTY;
		head->prevDirection = Direction::BACKWARD;
	}
	else if (input == 'a' && map.arrMap[head->y][head->x - 1] != mapState::WALL)
	{
		head->x - 1;
		map.arrMap[head->y][head->x - 1] == mapState::PLAYER;
		map.arrMap[head->y][head->x] == mapState::EMPTY;
		head->prevDirection = Direction::LEFT;
	}
	else if (input == 'd' && map.arrMap[head->y][head->x + 1] != mapState::WALL)
	{
		head->x + 1;
		map.arrMap[head->y][head->x + 1] == mapState::PLAYER;
		map.arrMap[head->y][head->x] == mapState::EMPTY;
		head->prevDirection = Direction::RIGHT;
	}
}

// 노드 이동
void Player::MoveNode(Map& map, Node* newNode, Direction direction)
{
	if (Direction::FORWARD)
	{
		map.arrMap[newNode->y][newNode->x] = mapState::EMPTY;
		map.arrMap[newNode->y - 1][newNode->x] = mapState::PLAYER;
		newNode->prevDirection = Direction::FORWARD;
	}
	else if (Direction::BACKWARD)
	{
		map.arrMap[newNode->y][newNode->x] = mapState::EMPTY;
		map.arrMap[newNode->y + 1][newNode->x] = mapState::PLAYER;
		newNode->prevDirection = Direction::BACKWARD;
	}
	else if (Direction::RIGHT)
	{
		map.arrMap[newNode->y][newNode->x] = mapState::EMPTY;
		map.arrMap[newNode->y][newNode->x + 1] = mapState::PLAYER;
		newNode->prevDirection = Direction::RIGHT;
	}
	else if (Direction::LEFT)
	{
		map.arrMap[newNode->y][newNode->x] = mapState::EMPTY;
		map.arrMap[newNode->y][newNode->x - 1] = mapState::PLAYER;
		newNode->prevDirection = Direction::RIGHT;
	}
}

// 맨 뒤에 노드 추가
void Player::InsertNode(Node * tail, Node * newNode, Map & map)
{
	tail->next = newNode;
	map.arrMap[tail->next->y][tail->next->x] = mapState::PLAYER;

	nodeCount++;
}

// 앞 노드들 따라가기
void Player::TrailNode(Map& map)
{
	Node* scan = head;

	for (int i = 0; i < nodeCount; i++)
	{
		// 모든 노드들 이동시키기
	}
}

