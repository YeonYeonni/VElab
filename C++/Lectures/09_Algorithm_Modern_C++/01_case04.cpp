#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	vector <int> v;
	for (int i = 0; i < 100; i++)
	{
		int n = rand() % 100;
		v.push_back(n);
	}

	// Q) 모든 숫자들에 3을 곱하기
	{
		// 1. 구현
		for (int i = 0; i < v.size(); i++)
		{
			v[i] *= 3;
		}

		// 2. 표준
		struct MultiplyBy3
		{
			void operator()(int& n)
			{
				n *= 3;
			}
		};
		std::for_each(v.begin(), v.end(), MultiplyBy3());
	}
}