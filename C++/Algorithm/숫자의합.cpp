#include <iostream>
using namespace std;

// ���� ����
int N; // ������ ����
string M;
int answer; // ������ ��

int main()
{
	// �Է� �ޱ�
	cin >> N;
	cin >> M;

	for (int i = 0; i < N; i++)
	{
		//cout << M[i] << endl;
		//answer += (int)M[i] - '0';
		answer += (int)M[i] - 48;
	}

	// ��� ���
	cout << answer;
}