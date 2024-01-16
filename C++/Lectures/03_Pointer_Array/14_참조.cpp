#include <iostream>
using namespace std;

struct StatInfo
{
	int hp;
	int attack;
	int defence;
};

// 1) �� (����) ���� ���
void PrintByCopy(StatInfo player)
{
	cout << "--------------------" << endl;
	cout << "HP : " << player.hp << endl;
	cout << "ATT : " << player.attack << endl;
	cout << "DEF : " << player.defence << endl;
	cout << "--------------------" << endl;
}

// 2) �ּ� ���� ���
void PrintByPointer(StatInfo* player)
{
	cout << "--------------------" << endl;
	cout << "HP : " << (*player).hp << endl; // player -> hp
	cout << "ATT : " << (*player).attack << endl; // player -> attack
	cout << "DEF : " << (*player).defence << endl; // player -> defence
	cout << "--------------------" << endl;
}

// 3) ���� ���� ���
void PrintByRef(StatInfo& player)
{
	cout << "--------------------" << endl;
	cout << "HP : " << player.hp << endl;
	cout << "ATT : " << player.attack << endl;
	cout << "DEF : " << player.defence << endl;
	cout << "--------------------" << endl;
}

int main()
{
	// 1) �� ����
	PrintByCopy(player);

	// 2) ������
	StatInfo player = { 100, 10, 1 };
	PrintByPointer(&player);

	// 3) ����
	StatInfo& ref = player;
	PrintByRef(ref);
}