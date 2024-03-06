#include "pch.h"
#include "numlist.h"

void PhNumAndName::input(char* bufname, char* bufnum)
{
	Name = bufname;
	Num = bufnum;
}


void PhNumAndName::erase(char* bufname, char* bufnum)
{
	void input(char* bufname = 0, char* bufnum = 0);

	void erase(char* bufname, char* bufnum);
}

char* PhNumAndName::GetnameAnum()
{
	return Name, Num;
}

char* PhNumAndName::Getname()
{
	return Name;
}

char* PhNumAndName::Getnum()
{
	return Num;
}

NumListApp::NumListApp()
{
	count = 0;

	const char* initialName = "채교수";
	const char* initialNum = "01011112222";

	const char* initialName2 = "김교수";
	const char* initialNum2 = "01033334444";

	const char* initialName3 = "박교수";
	const char* initialNum3 = "01055556666";

	char* name = const_cast<char*>(initialName);
	char* num = const_cast<char*>(initialNum);
	index[count++].input(name, num);

	char* name1 = const_cast<char*>(initialName2);
	char* num1 = const_cast<char*>(initialNum2);
	index[count++].input(name1, num1);

	char* name2 = const_cast<char*>(initialName3);
	char* num2 = const_cast<char*>(initialNum3);
	index[count++].input(name2, num2);

	const char* initialName4 = "정교수";
	const char* initialNum4 = "01066667777";

	const char* initialName5 = "부교수";
	const char* initialNum5 = "01077778888";

	const char* initialName6 = "길교수";
	const char* initialNum6 = "01099990000";

	char* name3 = const_cast<char*>(initialName);
	char* num3 = const_cast<char*>(initialNum);
	index[count++].input(name3, num3);

	char* name4 = const_cast<char*>(initialName2);
	char* num4 = const_cast<char*>(initialNum2);
	index[count++].input(name4, num4);

	char* name5 = const_cast<char*>(initialName3);
	char* num5 = const_cast<char*>(initialNum3);
	index[count++].input(name5, num5);







}

NumListApp::~NumListApp()
{
}




void NumListApp::InputNumAndName()
{
	// 1일때 키패드로 접근 -> 번호 입력

	cout << "번호를 입력하세요" << endl;


	char _bufnum[100] = {};

	cout << ">" << endl;

	char* bufnum = new char[strlen(_bufnum) + 1];

	cin >> bufnum;

	cout << "해당 번호에 저장하실 이름을 입력하세요" << endl;

	cout << ">" << endl;
	char _bufname[100] = {};

	char* bufname = new char[strlen(_bufname) + 1];

	cin >> bufname;


	index[count++].input(bufname, bufnum);
}


void NumListApp::RecentMenu()
{
	cout << "최근 수신 내역" << endl;


	char _recname[100] = {};
	char _recnum[100] = {};

	cout << ">" << endl;

	char* recnum = new char[strlen(_recnum) + 1];

	//최근 내역에 띄울 번호 입력
	cin >> recnum;

	cout << "해당 번호에 저장하실 이름을 입력하세요" << endl;

	cout << ">" << endl;

	char* recname = new char[strlen(_recname) + 1];

	//최근 내역에 띄울 이름 입력
	cin >> recname;

	recindex[reccount++].input(recname, recnum);
}

void NumListApp::ShowAlllisT()
{

	int i;
	for (i = 0; i < count; ++i)
	{
		cout << index[i].Getname() << " " << index[i].Getnum() << endl;
	}

}

void NumListApp::Search()
{
	char searchQuery[100];
	cout << "검색어를 입력하시오: ";
	cin >> searchQuery;

	bool found = false;

	for (int i = 0; i < count; ++i)
	{
		if (strstr(index[i].Getnum(), searchQuery) != nullptr || strstr(index[i].Getname(), searchQuery) != nullptr)
		{
			cout << index[i].Getname() << ":" << index[i].Getnum() << endl;
			found = true;
		}
	}

	if (!found)
	{
		cout << "검색 결과가 없습니다." << endl;
	}
}

void NumListApp::Delete()
{
	int i;
	char search[100];
	cout << "삭제할 이름 or 번호를 입력하세요 : ";
	cin >> search;
	for (i = 0; i < count; ++i)
	{
		if (strcmp(index[i].Getnum(), search) == 0)
		{
			delete[] index[i].Getname();
			delete[] index[i].Getnum();
			index[i].input(index[i + 1].Getname(), index[i + 1].Getnum());
			count--;

		}

		else if (strcmp(index[i].Getname(), search) == 0)
		{
			delete[] index[i].Getname();
			delete[] index[i].Getnum();
			index[i].input(index[i + 1].Getname(), index[i + 1].Getnum());
			count--;
		}
		else
		{
			return;
		}

	}
}

void NumListApp::Deletehip()
{
	for (int i = 0; i < count; i++)
	{
		delete[] index[i].Getname();
		delete[] index[i].Getnum();
	}
}

Numplay::Numplay()
{
	run = 1;
}

void Numplay::_Play()
{
	while (run)
	{
		switch (MainMenu())
		{
		case '1':
			switch (MainMenu_1())
			{
			case'1':
				_nPlay.InputNumAndName();
				break;


			}

			break;


		case '2':
			switch (MainMenu_3())
			{
			case'1':
				_nPlay.Search();
				break;

			case'2':
				_nPlay.InputNumAndName();
				break;

			case'3':
				_nPlay.Delete();
				break;

			case'4':
				_nPlay.ShowAlllisT();
				break;


			}

			break;

		case'3': { run = 0; break; }


		}
	}
}

void Numplay::_App()
{
	while (run)
	{
		switch (MainMenu_3())
		{
		case'1':
			_nPlay.Search();
			break;

		case'2':
			_nPlay.InputNumAndName();
			break;

		case'3':
			_nPlay.Delete();
			break;

		case'4':
			_nPlay.ShowAlllisT();
			break;

		}
	}
}



char MainMenu()
{ //사용자가 먼저 주소록에 접근할 때.
	cout << "1.키패드에 전화번호 입력" << endl;
	cout << "2.연락처 앱 접속" << endl;
	cout << "3.스토리로 돌아가기" << endl;
	cout << ">" << endl;

	return _getch();
}

char MainMenu_1()
{
	//MainMenu에서 1번 입력시 호출되는 기능. 번호를 입력하면 주소록과 비교 후 탐색해야함. 단축키 부여
	cout << "번호를 입력하시려면 1번을 눌러주세요" << endl;
	cout << ">" << endl;

	return _getch();
}

char MainMenu_3()
{
	cout << "1.탐색" << endl;
	//탐색 시 번호, 이름 입력 and 일부 입력 시 탐색 결과 리스트업
	cout << "2.추가" << endl;
	cout << "3.삭제" << endl;
	cout << "4.전체보기" << endl;
	cout << ">" << endl;

	return _getch();
}

char Str_numMenu()
{ //사용자에게 저장되지 않은 번호로 연락이 왔을 때.
	cout << "1.연락처에 추가" << endl;
	cout << "2.차단" << endl;
	cout << ">" << endl;

	return _getch();
}