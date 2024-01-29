// 1. 복사 방식
int wantedId = 2;

[=](Item& item)
	{
		return item._rarity == wantedId;
		// return item._rarity == 2; 느낌
	};

std::find_if(v.begin(), v.end(), isWantedItem);

// 2. 참조 방식
int wantedId = 2;

[&](Item& item)
	{
		return item._rarity == wantedId;
	};

std::find_if(v.begin(), v.end(), isWantedItem);