#include <iostream>
using namespace std;

int cnt;

int main()
{
	// for
	for (int i = 0; i < 100; i++)
	{
		cout << "Hello World" << endl;

		if (i == 50)
			continue;
	}
}