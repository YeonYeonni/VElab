#include <iostream>
using namespace std;
#include <vector>

class Iterator
{
public:
	Iterator() :_data(nullptr) { }
	Iterator(int* data) : _data(data) { }

	bool operator==(const Iterator& other)
	{
		return _data == other._data;
	}

	bool operator!=(const Iterator& other)
	{
		return _data != other._data;
	}

	void operator++()
	{
		_data++;
	}

	int operator*()
	{
		return *_data;
	}

public:
	int* _data;
};

class Inventory
{
public:

	using iterator = Iterator;

	iterator begin() { return iterator(&_items[0]); }
	iterator end() { return iterator(&_items[10]); }

	int _items[10] = { 1,2,3,4,5,6,7,8,9,10 };
};

int main()
{
	Inventory inventory;

	for (auto item : inventory) // error가 나지 않음
	{
		cout << item << endl;
	}

}