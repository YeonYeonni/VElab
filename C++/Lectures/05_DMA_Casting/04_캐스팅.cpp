#include <iostream>
using namespace std;

class Player
{
public:
	Player() {};
	virtual ~Player() {};
};

class Knight : public Player
{
public:
	Knight() {};
	virtual ~Knight() {};
};

class Dog
{
};

int main()
{
	Knight* k = new Knight();
	Player* p = k;

	// static cast
	Knight* k2 = static_cast<Knight*>(p);

	// dynamic cast
	Knight* k2 = dynamic_cast<Knight*>(p);

	// const cast
	const char* name = "Yeno";
	char* name2 = const_cast<char*>(name);

	// reinterpret cast
	Dog* dog = (Dog*)k;
}