#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	vector <int> v = { 1, 4, 3, 5, 8, 2 };

	// Q) Ȧ�� ������ �ϰ� ����
	{
		// 1. ����
		for (auto it = v.begin(); it != v.end(); it++)
		{
			if (*it % 2 != 0)
				it = v.erase(it);
			else
				it++;
		}

		// 2. ǥ��
		struct IsOdd
		{
			bool operator()(int n)
			{
				return n % 2 != 0;
			}
		};

		auto it = std::remove_if(v.begin(), v.end(), IsOdd()); // 4 8 2 5 8 2
		v.erase(it, v.end()); // 4 8 2
	}
}