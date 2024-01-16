#include <iostream>
using namespace std;

struct StatInfo
{
	int hp;
	int attack;
	int defence;
};

// OUT Å°¿öµå
#define OUT

void PrintByRef(OUT StatInfo& player)
{
	cout << "--------------------" << endl;
	cout << "HP : " << player.hp << endl;
	cout << "ATT : " << player.attack << endl;
	cout << "DEF : " << player.defence << endl;
	cout << "--------------------" << endl;
}

int main()
{
	StatInfo player = { 100, 10, 1 };

	StatInfo& ref = player;
	PrintByRef(OUT ref);
}