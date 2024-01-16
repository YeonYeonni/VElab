#include <iostream>
using namespace std;

// 로또 번호 생성기
void Swap(int& a, int& b) // 참조 방식
{
	int temp = a;
	a = b;
	b = temp;
}

// 오름차순 정렬 (버블 정렬)
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

		// 중복 처리 (이미 찾은 값인지)
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