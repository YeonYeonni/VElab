#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	// 벡터 생성
	int number = 50;
	vector <int> v;

	for (int i = 0; i < 100; i++)
	{
		int n = rand() % 100;
		v.push_back(n);
	}

	// Q) 특정 숫자가 있는지?
	// 1. 구현
	{
		int number = 50;
		vector<int>::iterator it;

		for (auto it = v.begin(); it != v.end(); it++)
		{
			int value = *it;
			if (value == number)
			{
				break;
			}
		}
	}
	// 2. 표준 (find)
	auto it = std::find(v.begin(), v.end(), number);

	// 확인
	if (it == v.end())
	{
		cout << "못찾음" << endl;
	}
	else
	{
		cout << "찾음" << endl;
	}
}