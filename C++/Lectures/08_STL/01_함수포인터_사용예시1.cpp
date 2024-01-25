#include <iostream>
using namespace std;
#include <vector>
#include <queue>

int Add(int a, int b)
{
	return a + b;
}

using FuncPtrType = int(*)(int a, int b);

int DoSomething(int a, int b, FuncPtrType func)
{
	return func(a, b);
}

int main()
{
	DoSomething(10, 20, &Add);
}