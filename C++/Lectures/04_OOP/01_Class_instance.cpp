#include <iostream>
using namespace std;

// 객체지향 (Object Oriented Programming)
// 설계도
class Knight
{
public:
	// 멤버 함수
	void Attack() { cout << "Attack" << endl; }
	void Die() { cout << "Die" << endl; }
	void HealME(int value)
	{
		hp += 10; // 매개변수가 아닌 멤버 변수를 사용할 수 있다.
		// thisPtr -> hp += value; 가 숨겨져 있다.
	}

public:
	// 멤버 변수 : class가 가지고 있어야 할 변수. Convention을 따로 해주기.
	int hp;
	int attack;
	int defence;
};

int main()
{
	// 객체 (instance)
	Knight k1;

	k1.hp = 100;
	k1.attack = 10;

	k1.Attack();
	k1.Die();
	k1.HealME(10);
}