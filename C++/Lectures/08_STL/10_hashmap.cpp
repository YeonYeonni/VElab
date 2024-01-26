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

	// 추가
	//um.insert(pair<int, int>);
	um.insert(make_pair(10, 100));
	um[2] = 200;

	// 찾기
	auto findIt = um.find(100);
	if (findIt != um.end())
	{
		cout << "찾음" << endl;
	}
	else
	{
		cout << "없음" << endl;
	}

	// 삭제
	um.erase(10);
	um.erase(findIt);

	// 순회
	for (auto it = um.begin(); it != um.end(); it++)
	{
		int key = it->first;
		int value = it->second;
	}
}