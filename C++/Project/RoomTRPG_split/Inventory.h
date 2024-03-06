#pragma once

enum
{
	MAX_SLOT = 5,
};

class Inventory
{
public:
	Inventory();
	virtual ~Inventory();

	bool AddInven(string* sign);

	bool RemoveInven(string* sign);
	bool SortInven();
	void Clear();

	int FindEmptySlot();
	int FindItemSlot(string* sign);

public:
	string* _signs[MAX_SLOT];
	int _signCount = 0;
};
