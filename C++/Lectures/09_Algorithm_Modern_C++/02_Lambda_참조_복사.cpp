// 1. ���� ���
int wantedId = 2;

[=](Item& item)
	{
		return item._rarity == wantedId;
		// return item._rarity == 2; ����
	};

std::find_if(v.begin(), v.end(), isWantedItem);

// 2. ���� ���
int wantedId = 2;

[&](Item& item)
	{
		return item._rarity == wantedId;
	};

std::find_if(v.begin(), v.end(), isWantedItem);