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

	// Q) 홀수인 숫자 개수는?
	{
		int count = 0;

		// 1. 구현
		for (auto it = v.begin(); it != v.end(); it++)
		{
			if (*it % 2 != 0)
				count++;
		}

		// 2. 표준
		struct IsOdd
		{
			bool operator()(int n)
			{
				return n % 2 != 0;
			}
		};

		int n = std::count_if(v.begin(), v.end(), IsOdd());

		// Q) 모든 데이터가 홀수인가, 홀수인 데이터가 하나라도 있는지, 모든 데이터가 홀수가 아닌지
		// bool b1 = std::all_of(v.begin(), v.end(), IsOdd());
		// bool b2 = std::any_of(v.begin(), v.end(), IsOdd());
		// bool b3 = std::none_of(v.begin(), v.end(), IsOdd());
	}
}