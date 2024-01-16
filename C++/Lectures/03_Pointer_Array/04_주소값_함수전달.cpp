#include <iostream>
using namespace std;

void AddHp(int* hp, int value)
{
	*hp += value; // hp를 담고 있는 주소값을 통해 hp값을 변화
}

int main()
{
	int hp = 100; // 지역 변수
	int* ptr = &hp;

	AddHp(ptr, 10);

	cout << hp << endl; // 110
}