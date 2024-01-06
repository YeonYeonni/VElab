#include <iostream>
using namespace std;

bool isRich;
bool isTall;

int main()
{
	isRich = true;
	isTall = true;

	// && and : 둘 중 하나라도 false이면 false. 둘 모두 true이면 true.
	isRich&& isTall; // 키가 크고 부자

	isRich && (isTall == false);// 키가 작고 부자
}