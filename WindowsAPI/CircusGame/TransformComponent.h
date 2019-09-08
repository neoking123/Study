#pragma once

enum DIRECTION
{
	LEFT = -1,
	RIGHT = 1,
	UP = -1,
	DOWN = 1,
	STOP = 0
};

struct Position
{
	int x = 0;
	int y = 0;
};

struct Size
{
	int width = 0;
	int height = 0;
};

class TransformComponent
{
public:
	Position position = {0, 0};
	Size size = {0, 0};
};

