#include <iostream>
using namespace std;

// 소수 : 1보다 큰 자연수 중 1과 자신만을 약수로 갖는 수
int main()
{
	int N;
	int M;
	int answer = 0; // 정답
	int count = 0; // 나누어 떨어짐 판별 용도

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> M;

		// 1부터 자기 자신까지 순회
		for (int j = 1; j <= M; j++)
		{
			// 나누어 떨어지면 count 증가
			if (M % j == 0)
			{
				count += 1;
			}
		}
		// 소수라면 정답 추가
		if (count == 2)
		{
			answer += 1;
		}
		// count 초기화
		count = 0;
	}
	// 정답 출력
	cout << answer;
}