#include <iostream>
using namespace std;

int hp;

int main()
{
	hp = 100;
	hp -= 200;

	if (hp <= 0)
	{
		cout << "몬스터를 처치했습니다!" << endl;
	}
	else
	{
		if (hp <= 30)
		{
			cout << "몬스터가 도망갑니다!" << endl;
		}
		else
		{
			cout << "몬스터가 반격했습니다" << endl;
		}
	}
}