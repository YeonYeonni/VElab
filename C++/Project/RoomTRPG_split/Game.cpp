#include "pch.h"
#include "RoomManager.h"
#include "Inventory.h"
#include "numlist.h"


// 전역 변수
string playername; // 플레이어 이름
int n; // 싸인 받으러 가야할 교수님 수
char trs;
string de;
char BA[] = "박사생";
char MA[] = "석사생";

// 인벤토리 생성
Inventory* inv_name = new Inventory(); // 이름
Inventory* inv_num = new Inventory(); // 번호

Inventory* Correction = new Inventory(); // 정답지
//vector<string> professor; // 인벤토리 (앞으로 모아야함)

// 인스턴스 생성
RoomManager* GameRoom;

Numplay* num = new Numplay();
// 주소록 시행부 ~
// :: RoomManager.cpp 내 각 Room 함수에서 아래와 같이 사용
//num->_Play();
// ~주소록 시행부
// 
//Address* Address;


// 테스트용
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
		GameRoom->ROOM2_1(Correction, num, inv_name, inv_num); // 두번째 교수님으로 돌아가기
		GameRoom->Ending(Correction, num, inv_name, inv_num); // 엔딩
	}
	else
		GameRoom->Ending(Correction, num, inv_name, inv_num); // 엔딩

	
}