#include <iostream>
using namespace std;

// [리턴타입] [함수이름] ()

int Add(int a, int b);

int main()
{
	Add(10, 20);
}

int Add(int a, int b)
{
	cout << a + b << endl;

	return a + b;
}