#include <iostream>
using namespace std;

struct StatInfo
{
	int hp;
	int attack;
	int defence;
};

int main()
{
	StatInfo monster;
	monster.hp = 100;
	monster.attack = 10;
	monster.defence = 1;

	StatInfo* ptr = &monster;

	(*ptr).hp; // 100 간접 연산자
	ptr->hp; // 100 간접 멤버 연산자
}