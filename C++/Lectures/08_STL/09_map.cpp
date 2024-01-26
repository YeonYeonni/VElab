#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <set>

class Player
{
public:
	Player() : _id(0) { }
	Player(int id) : _id(id) {}

	int _id = 0;
};

template<typename T, typename U>
struct Pair
{
	T first;
	U second;
};

template<typename T, typename U>
auto MakePair(T first, U second)
{
	return std::pair<T, U>(first, second);
}

int main()
{
	vector<Player*> v;
	v.push_back(new Player(100));
	v.push_back(new Player(200));
	v.push_back(new Player(300));
	v.push_back(new Player(400));
	v.push_back(new Player(500));

	// (key, value)
	map<int, Player*> m;

	// 1. 추가
	Pair<int, Player*> p;

	for (Player* player : v)
	{
		int key = player->_id;
		Player* data = player;

		m.insert(pair<int, Player*>(key, data));
		// m.insert(make_pair(player->id, player));
		// m[player->_id] = player;
	}

	// 2. 찾기
	// map<int, Player*>::iterator it = m.find(300);
	//auto it = m.find(300);
	//auto whoami = *it;
	//whoami.first; // key
	//whoami.second; // value

	// 한번에
	/*
	auto it = m.find(300);
	int key  = (*it).first; // key
	Player* value = (*it).second; // value
	*/

	// ->
	/*
	auto it = m.find(300);
	int key = it->first;
	Player* value = it->second;
	*/

	auto it = m.find(300);
	if (it != m.end())
	{
		int key = it->first;
		Player* value = it->second;
		cout << "데이터 찾음" << endl;
	}
	else
	{
		cout << "데이터 없음" << endl;
	}

	// 3. 순회
	for (auto it = m.begin(); it != m.end(); it++)
	{
		int key = it->first;
		Player* p = it->second;
	}
}