#include <iostream>
using namespace std;

int cnt;

int main()
{
	// for
	for (int j = 0; j < 100; j++)
	{
		for (int i = 0; i < 100; i++)
		{
			cout << "Hello World" << endl;

			if (i > 50)
				break; // ���� for ���� ����������
		}

		if (j > 50)
			break; // �ܺ� for���� ����������
	}
}