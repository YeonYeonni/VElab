#include <iostream>
using namespace std;

// ��ü���� (Object Oriented Programming)
// ���赵
class Knight
{
public:
	// ��� �Լ�
	void Attack() { cout << "Attack" << endl; }
	void Die() { cout << "Die" << endl; }
	void HealME(int value)
	{
		hp += 10; // �Ű������� �ƴ� ��� ������ ����� �� �ִ�.
		// thisPtr -> hp += value; �� ������ �ִ�.
	}

public:
	// ��� ���� : class�� ������ �־�� �� ����. Convention�� ���� ���ֱ�.
	int hp;
	int attack;
	int defence;
};

int main()
{
	// ��ü (instance)
	Knight k1;

	k1.hp = 100;
	k1.attack = 10;

	k1.Attack();
	k1.Die();
	k1.HealME(10);
}