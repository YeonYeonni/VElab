#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

enum class ItemType
{
	None,
	Armor,
	Weapon,
	Jewelry,
	Consumable,
};

enum class Rarity
{
	Common,
	Rare,
	Unique,
};

class Item
{
public:
	Item() {}
	Item(int itemId, Rarity rarity, ItemType type) : _itemId(itemId), _rarity(rarity), _type(type) {}

public:
	int _itemId = 0;
	Rarity _rarity = Rarity::Common;
	ItemType _type = ItemType::None;
};

int main()
{
	// lambda
	vector<Item> v;
	v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
	v.push_back(Item(2, Rarity::Common, ItemType::Armor));
	v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
	v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));

	{
		// 1. ���ٸ� �ٷ� ���
		std::find_if(v.begin(), v.end(), [](Item& item) {return item._rarity == Rarity::Unique; });

		// 2. ���ٸ� ��ü�� ��� ���
		auto isUniqueLambda = [](Item& item) {return item._rarity == Rarity::Unique; };
		std::find_if(v.begin(), v.end(), isUniqueLambda);
	}
}