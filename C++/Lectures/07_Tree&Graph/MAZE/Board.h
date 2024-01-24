#pragma once
#include "ConsoleHelper.h"

enum
{
	BOARD_MAX_SIZE = 100
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Player; // 전방 선언

class Board
{
public:
	Board();
	~Board();

	void Init(int32 size, Player* player); // 맵 초기화
	void Render(); // 갈 수 있는/없는 영역 렌더링

	void GenerateMap(); // 미로 생성
	TileType GetTileType(Pos pos); // 해당 좌표 타일의 타입
	ConsoleColor GetTileColor(Pos pos);

	Pos GetEnterPos() { return Pos(1, 1); }
	Pos GetExitPos() { return Pos(_size - 2, _size - 2); }
	int32 GetSize() { return _size; }

private:
	TileType _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE]; // 전체 맵 크기
	int32 _size = 0; // 맵의 일부만 사용할 경우
	Player* _player = nullptr;;
};