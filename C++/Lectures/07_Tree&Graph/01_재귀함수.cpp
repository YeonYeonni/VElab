#include <iostream>
using namespace std;

// 재귀함수
void Func(int a)
{
	if (a == 0)
		return;
	cout << a << endl;
	Func(a - 1);
}

// 팩토리얼
int Factorial(int n)
{
	if (n <= 1)
		return 1;
	return n * Factorial(n - 1);
}

// 유클리드 호제법
int Gcd(int a, int b)
{
	if (b == 0)
		return a;

	return Gcd(b, a % b);
}

int main()
{
	
}