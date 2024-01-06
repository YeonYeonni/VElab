#include <iostream>
using namespace std;

bool isRich;
bool isTall;

int main()
{
	isRich = true;
	isTall = true;

	// || or : 둘 중 하나라도 true이면 true. 둘 모두 거짓일 때만 false.
	isRich || isTall;
}