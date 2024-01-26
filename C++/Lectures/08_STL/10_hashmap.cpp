#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

// 
int main()
{
	// hash_map
	unordered_map<int, int> um;

	// �߰�
	//um.insert(pair<int, int>);
	um.insert(make_pair(10, 100));
	um[2] = 200;

	// ã��
	auto findIt = um.find(100);
	if (findIt != um.end())
	{
		cout << "ã��" << endl;
	}
	else
	{
		cout << "����" << endl;
	}

	// ����
	um.erase(10);
	um.erase(findIt);

	// ��ȸ
	for (auto it = um.begin(); it != um.end(); it++)
	{
		int key = it->first;
		int value = it->second;
	}
}