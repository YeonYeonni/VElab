#include <iostream>
using namespace std;

void AddHp(int* hp, int value)
{
	*hp += value;
}

int main()
{
	int hp = 100;

	int* ptr = (int*)100;
	ptr += 1;

	cout << (int)ptr << endl; // ���� �ּ� ������ ��Ÿ��.
}