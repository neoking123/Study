#pragma once
#define PI 3.141592

enum KEY_STATE
{
	BUTTONDOWN,
	BUTTONUP
};

template <typename T>
T DegreesToRadians(T degree)
{
	return degree * 2 * PI / 360.0f;
}