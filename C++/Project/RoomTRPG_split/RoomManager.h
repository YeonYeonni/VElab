#pragma once

class Inventory;
class Numplay;

class RoomManager
{
	// SINGLETON
	DECLARE_SINGLE(RoomManager);

	// ��� ����
public:
	bool gameClear = false;

	// ��� �Լ�
public:
	// �� ����
	void Start(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM1(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM2(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM2_1(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM3(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void Ending(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
};

//111