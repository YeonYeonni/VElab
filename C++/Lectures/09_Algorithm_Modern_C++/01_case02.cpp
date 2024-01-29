#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	// ���� ����
	int div = 11;

	vector <int> v;
	for (int i = 0; i < 100; i++)
	{
		int n = rand() % 100;
		v.push_back(n);
	}

	// Q) 11�� ������ �������� ���ڰ� �ִ���
	// 1. ����
	for (auto it = v.begin(); it != v.end(); it++)
	{
		int value = *it;
		if (value % div == 0)
		{
			break;
		}
	}
	// 2. ǥ�� (find if)
	struct CanDivideBy11
	{
		bool operator() (int n)
		{
			return n % 11 == 0;
		}
	};

	auto it = std::find_if(v.begin(), v.end(), CanDivideBy11()); // begin ����, end ������

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