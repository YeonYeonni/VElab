#include <iostream>
using namespace std;

int hp;
int a;
int b;

int main()
{
	hp = 100;
	a = hp++;
	cout << a << endl; // 100
}