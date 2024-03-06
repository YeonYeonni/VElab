#pragma once

class PhNumAndName
{
	//개인정보 private 화
private:
	char* Name;
	char* Num;

public:

	//저장, 삭제 시에만 개인정보에 접근하기 위한 코드
public:
	void input(char* bufname = 0, char* bufnum = 0);
	void erase(char* bufname, char* bufnum);
	char* GetnameAnum();
	char* Getname();
	char* Getnum();
};

class NumListApp
{
private:
	PhNumAndName index[100] = {};
	PhNumAndName recindex[100] = {};
	char shortcuts[100] = {};
	int count;
	int reccount;

public:
	NumListApp();
	~NumListApp();

	void InputNumAndName();
	void RecentMenu();
	void ShowAlllisT();
	void Search();
	void Delete();
	void Deletehip();
};

char MainMenu();

char MainMenu_1();

char MainMenu_3();



char Str_numMenu();


class Numplay
{
public:
	NumListApp _nPlay;
	bool run;

public:
	Numplay();

	void _Play();
	void _App();
};