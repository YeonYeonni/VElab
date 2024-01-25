#include <iostream>
using namespace std;
#include <vector>
#include <queue>

class Functor
{
public:
	void operator() ()
	{
		cout << "Functor Test" << endl;
		cout << _value << endl;
	}

	void operator()(int n)
	{
		cout << "Functor Test" << endl;
		_value += n;
		cout << _value << endl;
	}

public:
	int _value = 0;
};

struct AddStruct
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

template<typename T>
int DoSomething(int a, int b, T func)
{
	return func(a, b);
}

int main()
{
	AddStruct func;
	DoSomething(10, 20, func);

	priority_queue<int, vector<int>, greater<int>> pq;
}