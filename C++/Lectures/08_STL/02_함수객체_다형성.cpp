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

class Job
{
public:
	Job() { }
	virtual ~Job() { }
};

class MoveJob
{
public:
	MoveJob(int x, int y) : x(x), y(y) { }

	void operator()()
	{
		cout << "Player move" << endl;
	}

public:
	int x;
	int y;
};

class AttackJob
{

};

int main()
{
	//MoveJob* job = new MoveJob(10, 20);
	//AttackJob* job2 = new AttackJob();

	//(*job)();

	queue<Job*>
}