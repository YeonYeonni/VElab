#include <iostream>
using namespace std;

int main()
{
	// ������ ����

	int round = 1; // ����
	int hp = 100; // ���� HP
	int damage = 10; //�÷��̾� ������

	// 5���� �̳��� ������ Ŭ���� �ؾ� ��

	while (true)
	{
		// ���� ����
		hp -= damage;

		// hp�� ������ ���� �ʰ�
		if (hp < 0)
			hp = 0;

		// �� ������ ��Ȳ
		cout << "Round: " << round << " ���� ü��: " << hp << endl;

		// hp�� 0�� ���
		if (hp == 0)
		{
			cout << "���� óġ!" << endl;
			break;
		}

		// 5���� �ȿ� Ŭ�������� ������ ���
		if (round == 5)
		{
			cout << "���� ���� ����" << endl;
			break;
		}
		round++;
	}
}