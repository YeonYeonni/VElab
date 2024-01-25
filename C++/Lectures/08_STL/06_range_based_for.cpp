#include <iostream>
using namespace std;
#include <vector>

int main()
{
	vector<int> v{ 1, 2, 3, 4, 5 };

	// ��� 1
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = 100;
		cout << v[i] << endl;
	}

	// ��� 2
	for (auto it = v.begin(); it != v.end(); it++)
	{
		*it = 100;
		cout << *it << endl;
	}

	// range based for
	for (int& data : v)
	{
		data = 100;
	}
}