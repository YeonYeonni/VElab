#include <iostream>
using namespace std;

// 연산자 오버로딩
class Pos
{
public:
	Pos operator+(const Pos& b)
	{
		Pos pos;
		pos.x = x + b.x;
		pos.y = y + b.y;
		return pos;
	}

	int x = 0;
	int y = 0;
};

int main()
{
	Pos pos1;
	Pos pos2;

	Pos pos3 = pos1 + pos2;
	// pos3 = pos1.operator+(pos2); 와 같다.
}