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

	(*ptr).hp; // 100 ���� ������
	ptr->hp; // 100 ���� ��� ������
}