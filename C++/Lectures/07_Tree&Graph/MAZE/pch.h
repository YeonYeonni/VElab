#pragma once

#include "Types.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Pos
{
	Pos()
	{
	}
	
	Pos(int y, int x) : y(y), x(x)
	{
	}

	bool operator == (const Pos& other)
	{
		return y == other.y && x == other.x;
	}

	bool operator != (const Pos& other)
	{
		return !(*this == other); // 자신의 주소와 비교
	}

	Pos operator+(const Pos& other)
	{
		Pos ret;
		ret.y = y + other.y;
		ret.x = x + other.x;
		return ret;
	}

	Pos& operator+=(const Pos& other)
	{
		y += other.y;
		x += other.x;
		return *this;
	}

	int32 y = 0;
	int32 x = 0;
};

enum Dir
{
	DIR_UP = 0,
	DIR_LEFT = 1,
	DIR_DOWN = 2,
	DIR_RIGHT = 3,
	DIR_COUNT = 4,
};