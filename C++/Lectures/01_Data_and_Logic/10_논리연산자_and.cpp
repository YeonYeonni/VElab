#include <iostream>
using namespace std;

bool isRich;
bool isTall;

int main()
{
	isRich = true;
	isTall = true;

	// && and : �� �� �ϳ��� false�̸� false. �� ��� true�̸� true.
	isRich&& isTall; // Ű�� ũ�� ����

	isRich && (isTall == false);// Ű�� �۰� ����
}