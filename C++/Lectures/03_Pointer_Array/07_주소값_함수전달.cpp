#include <iostream>
using namespace std;

void Swap(int* a, int* b) // 주소값을 메모리에 넣어준 것이다.
{
	int temp = *a; //역참조; 메모리를 타고 이동.
	*a = *b;
	*b = temp;
}

int main()
{
	int a = 10;
	int b = 20;
	Swap(&a, &b); // 함수의 인자로 주소값을 전달.

	cout << a << endl;
	cout << b << endl;
}