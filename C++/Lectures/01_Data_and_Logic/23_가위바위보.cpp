#include <iostream>
using namespace std;

const int SCISSORS = 0;
const int ROCK = 1;
const int PAPER = 2;

int main()
{
	srand(time(0)); // seed

	// ���� ���� ��
	while (true)
	{
		cout << "����(0) ����(1) ��(2) ����ּ���!" << endl;
		cout << "> ";

		// �����
		int value;
		cin >> value;

		// ��ǻ��
		int computerValue = rand() % 3;

		if (value == SCISSORS) // ����
		{
			switch (computerValue)
			{
			case SCISSORS: // ��ǻ�� ����
				cout << "����(Player) vs ����(Computer) : �����ϴ�!" << endl;
				break;
			case ROCK: // ��ǻ�� ����
				cout << "����(Player) vs ����(Computer) : �����ϴ�!" << endl;
				break;
			case PAPER: // ��ǻ�� ��
				cout << "����(Player) vs ��(Computer) : �̰���ϴ�!" << endl;
				break;
			default:
				break;
			}
		}
		else if (value == ROCK) // ����
		{
			switch (computerValue)
			{
			case SCISSORS: // ��ǻ�� ����
				cout << "����(Player) vs ����(Computer) : �̰���ϴ�!" << endl;
				break;
			case ROCK: // ��ǻ�� ����
				cout << "����(Player) vs ����(Computer) : �����ϴ�!" << endl;
				break;
			case PAPER: // ��ǻ�� ��
				cout << "����(Player) vs ��(Computer) : �����ϴ�!" << endl;
				break;
			default:
				break;
			}
		}
		else // ��
		{
			switch (computerValue)
			{
			case SCISSORS: // ��ǻ�� ����
				cout << "��(Player) vs ����(Computer) : �����ϴ�!" << endl;
				break;
			case ROCK: // ��ǻ�� ����
				cout << "��(Player) vs ����(Computer) : �̰���ϴ�!" << endl;
				break;
			case PAPER: // ��ǻ�� ��
				cout << "��(Player) vs ��(Computer) : �����ϴ�!" << endl;
				break;
			default:
				break;
			}
		}
	}
}