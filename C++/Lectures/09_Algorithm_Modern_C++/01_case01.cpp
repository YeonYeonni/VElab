#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	// ���� ����
	int number = 50;
	vector <int> v;

	for (int i = 0; i < 100; i++)
	{
		int n = rand() % 100;
		v.push_back(n);
	}

	// Q) Ư�� ���ڰ� �ִ���?
	// 1. ����
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
	// 2. ǥ�� (find)
	auto it = std::find(v.begin(), v.end(), number);

	// Ȯ��
	if (it == v.end())
	{
		cout << "��ã��" << endl;
	}
	else
	{
		cout << "ã��" << endl;
	}
}