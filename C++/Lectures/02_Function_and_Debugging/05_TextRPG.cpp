#include <iostream>
using namespace std;

// 플레이어 종류를 저장하는 enum
enum PlayerType
{
	PT_None = 0,
	PT_Knight = 1,
	PT_Archer = 2,
	PT_Mage = 3,
};

// 몬스터 타입
enum MonsterType
{
	MT_None = 0,
	MT_Slime = 1,
	MT_Orc = 2,
	MT_Skeleton = 3,
};

// Struct 문법으로 비슷한 변수를 관리
struct StatInfo // StatInfo 타입이 됨
{
	int hp; // 뒤 코드에서 playerStat.hp 로 접근
	int attack;
	int defence;
};

PlayerType playerType; // c++에서 enum은 int로 저장됨
StatInfo playerStat;

MonsterType monsterType;
StatInfo monsterStat;

void EnterLobby(); // 로비 입장
void SelectPlayer(); // 플레이어 직업 선택
void EnterField(); // 필드 입장
void CreateRandomMonster(); // 몬스터를 랜덤으로 생성
void EnterBattle(); // 전투
void WaitForNextKey(); //버튼을 눌러야 다음으로 넘어가게

int main()
{
	srand(time(0)); // 랜덤 시드값을 시간에 따라 달라지게 함
	EnterLobby();
}

void EnterLobby()
{
	while (true)
	{
		cout << "---------------------" << endl;
		cout << "로비에 입장했습니다!" << endl;
		cout << "---------------------" << endl;

		// 플레이어 직업 선택
		SelectPlayer();

		cout << "---------------------" << endl;
		cout << "(1) 필드 입장 (2) 게임 종료" << endl;
		cout << "---------------------" << endl;

		int input;
		cin >> input;

		if (input == 1)
		{
			EnterField();
		}
		else
		{
			return;
		}

	}
}

void SelectPlayer()
{
	// 잘못 입력했을 경우 무한 루프
	while (true)
	{
		cout << "---------------------" << endl;
		cout << "직업을 골라주세요!" << endl;
		cout << "(1) 기사 (2) 궁수 (3) 법사" << endl;
		cout << "> ";

		int choice;
		cin >> choice;

		if (choice == PT_Knight)
		{
			cout << "기사 생성중..." << endl;
			playerStat.hp = 150;
			playerStat.attack = 10;
			playerStat.defence = 5;
			playerType = PT_Knight;
			break;
		}
		else if (choice == PT_Archer)
		{
			cout << "궁수 생성중..." << endl;
			playerStat.hp = 100;
			playerStat.attack = 15;
			playerStat.defence = 3;
			playerType = PT_Archer;
;			break;
		}
		else if (choice == PT_Mage)
		{
			cout << "법사 생성중..." << endl;
			playerStat.hp = 80;
			playerStat.attack = 25;
			playerStat.defence = 0;
			playerType = PT_Mage;
			break;
		}
	}
}

void EnterField()
{
	while (true) // 필드에 있는 동안은 무한 반복
	{
		cout << "---------------------" << endl;
		cout << "필드에 입장했습니다!" << endl;
		cout << "---------------------" << endl;

		cout << "[Player] HP : " << playerStat.hp << " / ATT : " << playerStat.attack << " / DEF : " << playerStat.defence << endl;

		// 몬스터 스폰
		CreateRandomMonster();

		cout << "---------------------" << endl;
		cout << "(1) 전투 (2) 도주" << endl;
		cout << "> ";

		int input;
		cin >> input;

		if (input == 1)
		{
			EnterBattle();

			if (playerStat.hp == 0)
				return;
		}
		else
		{
			return;
		}
	}
}

void CreateRandomMonster()
{
	int randomChoice = 1 + (rand() % 3); // 0, 1, 2 사이 숫자 + 1

	switch (randomChoice)
	{
		case MT_Slime:
			cout << "슬라임 생성중...! (HP:30 / ATT:2 / DEF:0)" << endl;
			monsterStat.hp = 30;
			monsterStat.attack = 2;
			monsterStat.defence = 0;
			monsterType = MT_Slime;
			break;
		case MT_Orc:
			cout << "오크 생성중...! (HP:40 / ATT:10 / DEF:3)" << endl;
			monsterStat.hp = 40;
			monsterStat.attack = 10;
			monsterStat.defence = 3;
			monsterType = MT_Orc;
			break;
		case MT_Skeleton:
			cout << "해골 생성중...! (HP:80 / ATT:15 / DEF:5)" << endl;
			monsterStat.hp = 80;
			monsterStat.attack = 15;
			monsterStat.defence = 5;
			monsterType = MT_Skeleton;
			break;
	}
}

void EnterBattle()
{
	while (true)
	{
		int damage = playerStat.attack - monsterStat.defence;
		if (damage < 0)
			damage = 0;

		// 선빵
		monsterStat.hp -= damage;
		if (monsterStat.hp < 0)
			monsterStat.hp = 0;

		cout << "몬스터 남은 체력 : " << monsterStat.hp << endl;

		if (monsterStat.hp == 0)
		{
			cout << "몬스터를 처치했습니다!" << endl;
			WaitForNextKey();
			return;
		}

		// 반격
		damage = monsterStat.attack - playerStat.defence; // 위에서 만든 damage 재사용
		if (damage < 0)
			damage = 0;

		playerStat.hp -= damage;
		if (playerStat.hp < 0)
			playerStat.hp = 0;

		cout << "플레이어 남은 체력 : " << playerStat.hp << endl;

		if (playerStat.hp == 0)
		{
			cout << "당신은 사망했습니다... GAME OVER" << endl;
			WaitForNextKey();
			return;
		}
	}
}

void WaitForNextKey()
{
	cout << "계속하려면 1을 눌러주세요" << endl;
	cout << "> ";

	int input;
	cin >> input;

	system("cls"); // console clear 기능
}
