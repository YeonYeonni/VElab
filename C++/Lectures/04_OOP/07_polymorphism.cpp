#include <iostream>
using namespace std;

class Player
{
public:
	void Move() { cout << "Player Move()" << endl; }

public:
	int _hp;
};

class Knight : public Player
{
public:
	void Move() { cout << "Knight Move()" << endl; }

public:

};

void MovePlayer(Player* player)
{
	player->Move();
}

int main()
{
	Knight k1;
	MovePlayer(&k1);
}