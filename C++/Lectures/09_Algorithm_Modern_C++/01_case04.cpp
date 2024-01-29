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

	// Q) ��� ���ڵ鿡 3�� ���ϱ�
	{
		// 1. ����
		for (int i = 0; i < v.size(); i++)
		{
			v[i] *= 3;
		}

		// 2. ǥ��
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