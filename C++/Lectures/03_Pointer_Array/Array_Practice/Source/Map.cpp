# include "Map.h"
# include "Helper.h"
# include <iostream>
using namespace std;

// 1차원 배열로 Map을 관리하기
// 0: 이동가능, 1: 벽, 2: 플레이어

int GMap1D[MAP_SIZE * MAP_SIZE] =
{
	1, 1, 1, 1, 1,
	1, 0, 0, 0, 1,
	1, 0, 2, 0, 1,
	1, 0, 0, 0, 1,
	1, 1, 1, 1, 1,
};

int GMap2D[MAP_SIZE][MAP_SIZE] =
{
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 2, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1},
};

// 0, 1, 2로 초기화된 맵을 특수문자로 바꿔주기 (1D 맵 관리)
void PrintMap1D()
{
	SetCursorPosition(0, 0); // 초기 지점을 0, 0으로 지정

	// 모든 지점을 for loop으로 돌기
	for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
	{
		switch (GMap1D[i])
		{
		case 0:
			cout << "□";
			break;
		case 1:
			cout << "■";
			break;
		case 2:
			cout << "♨";
			break;
		}
		// 줄 넘김
		if ((i + 1) % MAP_SIZE == 0)
			cout << endl;
	}
}

// 2D 맵 관리
void PrintMap2D()
{
	SetCursorPosition(0, 0);

	for (int y = 0; y < MAP_SIZE; y++)
	{
		for (int x = 0; x < MAP_SIZE; x++)
		{
			switch (GMap2D[y][x])
			{
			case 0:
				cout << "□";
				break;
			case 1:
				cout << "■";
				break;
			case 2:
				cout << "♨";
				break;
			}
		}
		cout << endl;
	}
}