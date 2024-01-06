// 오버플로우 예시

#include <iostream>
using namespace std;

int hp;
short mp;

int main()
{
	mp = 30000;
	mp += 20000;

	cout << mp; // -15536
}