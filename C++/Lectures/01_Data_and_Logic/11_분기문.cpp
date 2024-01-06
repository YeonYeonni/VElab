#include <iostream>
using namespace std;

int hp;

int main()
{
	// if (판별식) {실행 코드}
	// if-else
	// if-else if-else
	hp = 100;
	hp -= 200;

	if (hp > 0)
	{
		cout << "살았습니다" << endl;
	}

	else
	{
		// 죽는 코드
		cout << "죽었습니다" << endl;
	}
}