#include <iostream>
using namespace std;

int main()
{
	// 간단한 전투

	int round = 1; // 라운드
	int hp = 100; // 몬스터 HP
	int damage = 10; //플레이어 데미지

	// 5라운드 이내에 게임을 클리어 해야 함

	while (true)
	{
		// 전투 진행
		hp -= damage;

		// hp가 음수가 되지 않게
		if (hp < 0)
			hp = 0;

		// 매 라운드의 상황
		cout << "Round: " << round << " 몬스터 체력: " << hp << endl;

		// hp가 0일 경우
		if (hp == 0)
		{
			cout << "몬스터 처치!" << endl;
			break;
		}

		// 5라운드 안에 클리어하지 못했을 경우
		if (round == 5)
		{
			cout << "제한 라운드 종료" << endl;
			break;
		}
		round++;
	}
}