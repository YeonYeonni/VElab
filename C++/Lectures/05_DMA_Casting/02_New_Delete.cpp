#include <iostream>
using namespace std;

class Monster
{

};

int main()
{
	Monster monsters[100];

	// new
	Monster* m1 = new Monster();

	// delete
	delete m1;
}