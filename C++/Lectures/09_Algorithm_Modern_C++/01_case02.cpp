#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	// 벡터 생성
	int div = 11;

	vector <int> v;
	for (int i = 0; i < 100; i++)
	{
		int n = rand() % 100;
		v.push_back(n);
	}

	// Q) 11로 나누어 떨어지는 숫자가 있는지
	// 1. 구현
	for (auto it = v.begin(); it != v.end(); it++)
	{
		int value = *it;
		if (value % div == 0)
		{
			break;
		}
	}
	// 2. 표준 (find if)
	struct CanDivideBy11
	{
		bool operator() (int n)
		{
			return n % 11 == 0;
		}
	};

	auto it = std::find_if(v.begin(), v.end(), CanDivideBy11()); // begin 포함, end 미포함

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