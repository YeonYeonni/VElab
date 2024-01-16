#include <iostream>
using namespace std;

// �ζ� ��ȣ ������
void Swap(int& a, int& b) // ���� ���
{
	int temp = a;
	a = b;
	b = temp;
}

// �������� ���� (���� ����)
void Sort(int* numbers, int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count - 1 /* - i*/; j++)
		{
			if (numbers[j] > numbers[j + 1])
				Swap(numbers[j], numbers[j + 1]);
		}
	}
}

void ChooseLotto(int* numbers)
{
	int count = 0;

	while (count != 6)
	{
		//0~44
		int randValue = 1 + rand() % 45;

		// �ߺ� ó�� (�̹� ã�� ������)
		bool found = false;

		for (int i = 0; i < count; i++)
		{
			if (numbers[i] == randValue)
			{
				found = true;
				break;
			}
		}

		if (found == false)
		{
			numbers[count] = randValue;
			count++;
		}
	}
}

int main()
{
	srand((unsigned)time(0));

	int lotto[6];
	ChooseLotto(lotto);

	for (int i = 0; i < 6; i++)
		cout << lotto[i] << endl;
}