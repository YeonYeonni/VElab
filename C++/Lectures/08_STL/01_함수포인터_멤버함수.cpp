#include <iostream>
using namespace std;
#include <vector>
#include <queue>

class Test
{
public:
	void PrintTest() { }
};

int main()
{
	// ��� �Լ� ������
	using MemFuncPtrType = void(Test::*)();;
	MemFuncPtrType funcPtr = &Test::PrintTest;

	Test t;
	(t.*funcPtr)();

	Test* t2 = &t;
	(t2->*funcPtr)();
}