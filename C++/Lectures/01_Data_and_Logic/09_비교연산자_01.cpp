#include <iostream>
using namespace std;

int a;
int b;
bool result;

int main()
{
	//같은지 ==
	result = (a == b);
	cout << result << endl;

	//다른지 !=
	result = (a != b);
	cout << result << endl;
}