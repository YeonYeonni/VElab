#include <iostream>
using namespace std;

// ����Լ�
void Func(int a)
{
	if (a == 0)
		return;
	cout << a << endl;
	Func(a - 1);
}

// ���丮��
int Factorial(int n)
{
	if (n <= 1)
		return 1;
	return n * Factorial(n - 1);
}

// ��Ŭ���� ȣ����
int Gcd(int a, int b)
{
	if (b == 0)
		return a;

	return Gcd(b, a % b);
}

int main()
{
	
}