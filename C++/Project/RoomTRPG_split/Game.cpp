#include "pch.h"
#include "RoomManager.h"
#include "Inventory.h"
#include "numlist.h"


// ���� ����
string playername; // �÷��̾� �̸�
int n; // ���� ������ ������ ������ ��
char trs;
string de;
char BA[] = "�ڻ��";
char MA[] = "�����";

// �κ��丮 ����
Inventory* inv_name = new Inventory(); // �̸�
Inventory* inv_num = new Inventory(); // ��ȣ

Inventory* Correction = new Inventory(); // ������
//vector<string> professor; // �κ��丮 (������ ��ƾ���)

// �ν��Ͻ� ����
RoomManager* GameRoom;

Numplay* num = new Numplay();
// �ּҷ� ����� ~
// :: RoomManager.cpp �� �� Room �Լ����� �Ʒ��� ���� ���
//num->_Play();
// ~�ּҷ� �����
// 
//Address* Address;


// �׽�Ʈ��
//Inventory* test = new Inventory();


int main()
{


	//GameRoom->Test1(test);
	//GameRoom->Test2(test);
	
	srand((unsigned int)time(0)); // random seed

	GameRoom->Start(Correction, num, inv_name, inv_num);
	GameRoom->ROOM1(Correction, num, inv_name, inv_num);
	GameRoom->ROOM2(Correction, num, inv_name, inv_num);
	GameRoom->ROOM3(Correction, num, inv_name, inv_num);

	if (Correction->_signCount > inv_name->_signCount)
	{
		GameRoom->ROOM2_1(Correction, num, inv_name, inv_num); // �ι�° ���������� ���ư���
		GameRoom->Ending(Correction, num, inv_name, inv_num); // ����
	}
	else
		GameRoom->Ending(Correction, num, inv_name, inv_num); // ����

	
}