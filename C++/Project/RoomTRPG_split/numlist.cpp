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

	const char* initialName = "ä����";
	const char* initialNum = "01011112222";

	const char* initialName2 = "�豳��";
	const char* initialNum2 = "01033334444";

	const char* initialName3 = "�ڱ���";
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

	const char* initialName4 = "������";
	const char* initialNum4 = "01066667777";

	const char* initialName5 = "�α���";
	const char* initialNum5 = "01077778888";

	const char* initialName6 = "�汳��";
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
	// 1�϶� Ű�е�� ���� -> ��ȣ �Է�

	cout << "��ȣ�� �Է��ϼ���" << endl;


	char _bufnum[100] = {};

	cout << ">" << endl;

	char* bufnum = new char[strlen(_bufnum) + 1];

	cin >> bufnum;

	cout << "�ش� ��ȣ�� �����Ͻ� �̸��� �Է��ϼ���" << endl;

	cout << ">" << endl;
	char _bufname[100] = {};

	char* bufname = new char[strlen(_bufname) + 1];

	cin >> bufname;


	index[count++].input(bufname, bufnum);
}


void NumListApp::RecentMenu()
{
	cout << "�ֱ� ���� ����" << endl;


	char _recname[100] = {};
	char _recnum[100] = {};

	cout << ">" << endl;

	char* recnum = new char[strlen(_recnum) + 1];

	//�ֱ� ������ ��� ��ȣ �Է�
	cin >> recnum;

	cout << "�ش� ��ȣ�� �����Ͻ� �̸��� �Է��ϼ���" << endl;

	cout << ">" << endl;

	char* recname = new char[strlen(_recname) + 1];

	//�ֱ� ������ ��� �̸� �Է�
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
	cout << "�˻�� �Է��Ͻÿ�: ";
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
		cout << "�˻� ����� �����ϴ�." << endl;
	}
}

void NumListApp::Delete()
{
	int i;
	char search[100];
	cout << "������ �̸� or ��ȣ�� �Է��ϼ��� : ";
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
{ //����ڰ� ���� �ּҷϿ� ������ ��.
	cout << "1.Ű�е忡 ��ȭ��ȣ �Է�" << endl;
	cout << "2.����ó �� ����" << endl;
	cout << "3.���丮�� ���ư���" << endl;
	cout << ">" << endl;

	return _getch();
}

char MainMenu_1()
{
	//MainMenu���� 1�� �Է½� ȣ��Ǵ� ���. ��ȣ�� �Է��ϸ� �ּҷϰ� �� �� Ž���ؾ���. ����Ű �ο�
	cout << "��ȣ�� �Է��Ͻ÷��� 1���� �����ּ���" << endl;
	cout << ">" << endl;

	return _getch();
}

char MainMenu_3()
{
	cout << "1.Ž��" << endl;
	//Ž�� �� ��ȣ, �̸� �Է� and �Ϻ� �Է� �� Ž�� ��� ����Ʈ��
	cout << "2.�߰�" << endl;
	cout << "3.����" << endl;
	cout << "4.��ü����" << endl;
	cout << ">" << endl;

	return _getch();
}

char Str_numMenu()
{ //����ڿ��� ������� ���� ��ȣ�� ������ ���� ��.
	cout << "1.����ó�� �߰�" << endl;
	cout << "2.����" << endl;
	cout << ">" << endl;

	return _getch();
}