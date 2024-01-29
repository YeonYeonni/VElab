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

	// Q) Ȧ���� ���� ������?
	{
		int count = 0;

		// 1. ����
		for (auto it = v.begin(); it != v.end(); it++)
		{
			if (*it % 2 != 0)
				count++;
		}

		// 2. ǥ��
		struct IsOdd
		{
			bool operator()(int n)
			{
				return n % 2 != 0;
			}
		};

		int n = std::count_if(v.begin(), v.end(), IsOdd());

		// Q) ��� �����Ͱ� Ȧ���ΰ�, Ȧ���� �����Ͱ� �ϳ��� �ִ���, ��� �����Ͱ� Ȧ���� �ƴ���
		// bool b1 = std::all_of(v.begin(), v.end(), IsOdd());
		// bool b2 = std::any_of(v.begin(), v.end(), IsOdd());
		// bool b3 = std::none_of(v.begin(), v.end(), IsOdd());
	}
}