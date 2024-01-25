#include <iostream>
using namespace std;
#include <vector>
#include <queue>

using ItemSelectorType = bool(*)(Item* item);

Item* FindItem(Item items[], int itemCount, ItemSelectorType selector)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		if (selector(item))
			return item;
	}
}

// �������� rare���� ����
bool IsRare(Item* item)
{
	return item->_rarity == 1;
}

// main
int main()
{
	Item items[10];
	items[3]._rarity = 1; // RARE
	FindItem(items, 10, IsRare);
}