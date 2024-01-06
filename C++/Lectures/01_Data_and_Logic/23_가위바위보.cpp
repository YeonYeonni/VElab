#include <iostream>
using namespace std;

const int SCISSORS = 0;
const int ROCK = 1;
const int PAPER = 2;

int main()
{
	srand(time(0)); // seed

	// 가위 바위 보
	while (true)
	{
		cout << "가위(0) 바위(1) 보(2) 골라주세요!" << endl;
		cout << "> ";

		// 사용자
		int value;
		cin >> value;

		// 컴퓨터
		int computerValue = rand() % 3;

		if (value == SCISSORS) // 가위
		{
			switch (computerValue)
			{
			case SCISSORS: // 컴퓨터 가위
				cout << "가위(Player) vs 가위(Computer) : 비겼습니다!" << endl;
				break;
			case ROCK: // 컴퓨터 바위
				cout << "가위(Player) vs 바위(Computer) : 졌습니다!" << endl;
				break;
			case PAPER: // 컴퓨터 보
				cout << "가위(Player) vs 보(Computer) : 이겼습니다!" << endl;
				break;
			default:
				break;
			}
		}
		else if (value == ROCK) // 바위
		{
			switch (computerValue)
			{
			case SCISSORS: // 컴퓨터 가위
				cout << "바위(Player) vs 가위(Computer) : 이겼습니다!" << endl;
				break;
			case ROCK: // 컴퓨터 바위
				cout << "바위(Player) vs 바위(Computer) : 비겼습니다!" << endl;
				break;
			case PAPER: // 컴퓨터 보
				cout << "바위(Player) vs 보(Computer) : 졌습니다!" << endl;
				break;
			default:
				break;
			}
		}
		else // 보
		{
			switch (computerValue)
			{
			case SCISSORS: // 컴퓨터 가위
				cout << "보(Player) vs 가위(Computer) : 졌습니다!" << endl;
				break;
			case ROCK: // 컴퓨터 바위
				cout << "보(Player) vs 바위(Computer) : 이겼습니다!" << endl;
				break;
			case PAPER: // 컴퓨터 보
				cout << "보(Player) vs 보(Computer) : 비겼습니다!" << endl;
				break;
			default:
				break;
			}
		}
	}
}