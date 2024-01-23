#include <iostream>
using namespace std;

// 전역 변수
int N; // 숫자의 개수
string M;
int answer; // 숫자의 합

int main()
{
	// 입력 받기
	cin >> N;
	cin >> M;

	for (int i = 0; i < N; i++)
	{
		//cout << M[i] << endl;
		//answer += (int)M[i] - '0';
		answer += (int)M[i] - 48;
	}

	// 결과 출력
	cout << answer;
}