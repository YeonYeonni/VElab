#include <iostream>
using namespace std;

// �Ҽ� : 1���� ū �ڿ��� �� 1�� �ڽŸ��� ����� ���� ��
int main()
{
	int N;
	int M;
	int answer = 0; // ����
	int count = 0; // ������ ������ �Ǻ� �뵵

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> M;

		// 1���� �ڱ� �ڽű��� ��ȸ
		for (int j = 1; j <= M; j++)
		{
			// ������ �������� count ����
			if (M % j == 0)
			{
				count += 1;
			}
		}
		// �Ҽ���� ���� �߰�
		if (count == 2)
		{
			answer += 1;
		}
		// count �ʱ�ȭ
		count = 0;
	}
	// ���� ���
	cout << answer;
}