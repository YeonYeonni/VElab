#pragma once
#include "Enums.h"

// ************************
//			Item
// ************************

class Item
{
public:
	Item(SignType signType);
	virtual ~Item();

public:
	//virtual void PrintInfo();
	ItemType GetItemType() { return _itemType; }
	int itemSize(Item* list) { return _itemSize; }

public:
	int _itemId = 0;
	int _itemCount = 0;
	int _itemSize = 0;
	string _professor;
	SignType _signType = ST_None; // ������ Ÿ��
	ItemType _itemType = IT_None; // �̸�/��ȭ��ȣ
};
