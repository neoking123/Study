#pragma once
#define PI 3.141592

enum DIRECTION
{
	LEFT = -1,
	RIGHT = 1,
	UP = -2,
	DOWN = 2,
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

/**
* @brief 위치, 크기 데이터를 가진 컴포넌트 클래스
* @author Dayeol Hyeon
*/

class TransformComponent
{
public:
	Position position = {0, 0};
	Size size = {0, 0};
};

template <typename T>
T DegreesToRadians(T degree)
{
	return degree * 2 * PI / 360.0f;
}