# include "Player.h"
# include "Map.h"
# include "Helper.h"

// 플레이어 이동 토글
bool canMove = true;

// 플레이어의 위치 초기화
int GPlayerX = 2;
int GPlayerY = 2;

// 플레이어 이동
void MovePlayer(int x, int y)
{
	// 범위 체크 (x축, y축 모두)
	if (x < 0 || x >= MAP_SIZE)
		return; // 범위를 넘어가면 종료
	if (y < 0 || y >= MAP_SIZE)
		return;

	// 벽 체크
	int index = y * MAP_SIZE + x; // 5칸을 점프하면 다음 줄로 넘어가는 규칙
	if (GMap1D[index] == 1)
		return; // 벽이면 종료

	// 기존 위치 정리
	{
		int Index = GPlayerY * MAP_SIZE + GPlayerX; // 원래 위치
		GMap1D[Index] = 0; // 원래 위치를 0으로 변경
	}

	// 새 위치로 이동
	{
		GPlayerX = x;
		GPlayerY = y;
		int Index = GPlayerY * MAP_SIZE + GPlayerX; // 새로운 위치
		GMap1D[Index] = 2; // 새로운 위치를 2로 변경
	}
}

// 플레이어 이동
void HandleMove()
{
	// 키를 누르고 있으면 계속 이동하기 때문에 키를 떼고 있으면 다음에 움직이도록 하자.
	if (GMoveDir == MD_NONE)
	{
		canMove = true; //키보드를 뗌 (토글 처리)
		return;
	}

	if (canMove == false) // 움직일 수 없는 상태
		return;

	canMove = false;

	switch (GMoveDir)
	{
	case MD_LEFT:
		MovePlayer(GPlayerX - 1, GPlayerY);
		break;
	case MD_RIGHT:
		MovePlayer(GPlayerX + 1, GPlayerY);
		break;
	case MD_UP:
		MovePlayer(GPlayerX, GPlayerY - 1);
		break;
	case MD_DOWN:
		MovePlayer(GPlayerX, GPlayerY + 1);
		break;
	}
}