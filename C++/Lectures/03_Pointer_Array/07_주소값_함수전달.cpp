#include <iostream>
using namespace std;

void Swap(int* a, int* b) // �ּҰ��� �޸𸮿� �־��� ���̴�.
{
	int temp = *a; //������; �޸𸮸� Ÿ�� �̵�.
	*a = *b;
	*b = temp;
}

int main()
{
	int a = 10;
	int b = 20;
	Swap(&a, &b); // �Լ��� ���ڷ� �ּҰ��� ����.

	cout << a << endl;
	cout << b << endl;
}