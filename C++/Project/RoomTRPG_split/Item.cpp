#include "pch.h"
#include "Item.h"
#include <iostream>
using namespace std;

// ************************
//			Item
// ************************
Item::Item(SignType signType)
{
	if (signType == 1)
		_professor = "A";

	else if (signType == 2)
		_professor = "B";

	else
		_professor = "C";
}

Item::~Item()
{
}

int Item::itemSize(Item* list)
{
	int _size = 0;
	for (Item* i = list; i != nullptr; i++)
		_size++;
	return _size;
}