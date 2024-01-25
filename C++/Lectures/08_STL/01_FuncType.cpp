#include <iostream>
using namespace std;
#include <vector>
#include <queue>

void Print()
{
	cout << "Hello World" << endl;
}

int Add(int a, int b)
{
	return a + b;
}

int main()
{
	// typedef void Functype();
	//using FuncType = void();
	//FuncType* ptr = &Print;

	using FuncType = int(int, int);
	FuncType* ptr = &Add;
	int ret = ptr(10, 20);
}