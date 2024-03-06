#pragma once

class Inventory;
class Numplay;

class RoomManager
{
	// SINGLETON
	DECLARE_SINGLE(RoomManager);

	// 멤버 변수
public:
	bool gameClear = false;

	// 멤버 함수
public:
	// 방 정보
	void Start(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM1(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM2(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM2_1(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void ROOM3(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
	void Ending(Inventory* correction, Numplay* num, Inventory* name, Inventory* number);
};

//111