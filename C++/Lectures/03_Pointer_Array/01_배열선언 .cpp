# include <iostream>
using namespace std;

int main()
{
	int arr[10]; // int Ÿ���� 10ĭ¥�� �迭 arr ����

	// 1. �ε��� �� �Ҵ�
	arr[0] = 10;
	arr[1] = 20;

	// 2. �ݺ���
	for (int i = 0; i < 5; i++)
	{
		arr[i] = i * 10;
	}

	// 3, �ʱⰪ ����
	int arr[5] = { 1, 2, 3, 4, 5 };
}