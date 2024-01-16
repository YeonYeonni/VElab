#include <iostream>
using namespace std;
#include <iomanip>

const int MAX = 100;
int board[MAX][MAX];
int N;

void PrintBoard()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << setfill('0') << setw(2) << board[y][x] << " ";
		}
		cout << endl;
	}
}

enum DIR
{
	RIGHT = 0,
	DOWN = 1,
	LEFT = 2,
	UP = 3,
};

// 갈 수 있는 칸을 판별
bool CanGo(int y, int x)
{
	if (y < 0 || y >= N)
		return false;
	if (x < 0 || x >= N)
		return false;
	if (board[y][x] != 0)
		return false;
	return true;
}

// 번호를 찍어주는 역할
void SetBoard()
{
	int dir = RIGHT;
	int num = 1;
	int y = 0;
	int x = 0;

	// 시계방향
	int dy[] = { 0, 1, 0, -1 };
	int dx[] = { 1, 0, -1, 0 };

	while (true)
	{
		// 번호 찍기
		board[y][x] = num;

		// 마지막 값이 n * n이면 return
		if (num == N * N)
			break;

		// 다음 칸으로 이동
		int nextY = y + dy[dir];
		int nextX = x + dx[dir];

		/*
		int nextY;
		int nextX;


		switch (dir)
		{
			case RIGHT:
				nextY = y;
				nextX = x + 1;
				break;
			case DOWN:
				nextY = y + 1;
				nextX = x;
				break;
			case LEFT:
				nextY = y;
				nextX = x - 1;
				break;
			case UP:
				nextY = y - 1;
				nextX = x;
				break;
		}
		*/

		// 앞으로 이동
		if (CanGo(nextY, nextX))
		{
			y = nextY;
			x = nextX;
			num++;
		}
		// 오른쪽으로 방향 전환
		else
		{
			dir = (dir + 1) % 4; // 4로 넘어갈 때만 0으로

			/*
			switch (dir)
			{
			case RIGHT:
				dir = DOWN;
				break;
			case DOWN:
				dir = LEFT;
				break;
			case LEFT:
				dir = UP;
				break;
			case UP:
				dir = RIGHT;
				break;
			}
			*/
		}
	}
}

// 방문했거나 벽을 만나면 오른쪽으로 틀기
// [ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ]
// [ ][ ][ ][ ][ ]

int main()
{
	cin >> N;

	PrintBoard();

	SetBoard();
}