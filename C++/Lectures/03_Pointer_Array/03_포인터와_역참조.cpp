#include <iostream>
using namespace std;

void AddHp(int* hp, int value)
{
	*hp += value; // hp�� ��� �ִ� �ּҰ��� ���� hp���� ��ȭ
}

int main()
{
	int hp = 100; // ���� ����
	int* ptr = &hp;

	AddHp(ptr, 10);

	cout << hp << endl; // 110
}