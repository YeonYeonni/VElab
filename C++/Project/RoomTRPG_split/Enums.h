#pragma once

// 진행할 플레이어 타입 (석사, 박사)
enum PlayerType
{
	PT_BACHELOR = 1,
	PT_MASTER = 2,
};

// 교수님 타입
enum SignType
{
	ST_None,
	ST_Main, // 교수님 1
	ST_Sub, // 교수님 2
	ST_New,  // 교수님 3
};

enum ItemType
{
	IT_None,
	IT_Name,
	IT_Number,
};

struct SignInfo
{
	/*
	char Name [10] = "검정";
	char Emad [10];
	char Pnum [10];
	char Tag1 [10];
	char Tag2 [10];
	*/

	//string Name;
	//string Emad;
	//string Pnum;
	//string Tag1;
	//string Tag2;

};

