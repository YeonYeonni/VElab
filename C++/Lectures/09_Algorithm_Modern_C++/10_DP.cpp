#include <unordered_map>
#include <algorithm>
#include <Windows.h>

#include <iostream>
using namespace std;

// 메모이제이션 (memoization)
//int cache[50][50];

/*
int combination(int n, int r)
{
	// 예외 사례
	if (r == 0 || n == r)
		return 1;

	// 이미 답을 구한 적 있으면 바로 반환
	int& ret = cache[n][r];
	if (ret != -1)
		return ret;

	ret = combination(n - 1, r - 1) + combination(n - 1, r);
	return ret;
*/

// +9의 아이템이 뜨는 경우의 수는?
// ex) 1, 2, 3, 4, ..., 9
// ex) 3, 6, 9
// ex) 1, 3, 4, ..., 9

int N = 9;
int cache[100];

// [+num]부터 시작해서, [+N]까지 가는 경우의 수
int Enchant(int num)
{
	// 기저 사례
	if (num > N)
		return 0;

	if (num == N)
		return 1;

	// 캐시
	int& ret = cache[num];
	if (ret != -1)
		return ret;

	// 적용
	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}

int main()
{
	/*
	::memset(cache, -1, sizeof(cache)); // 초기값 -1

	__int64 start = GetTickCount64();

	int lotto = combination(45, 6);

	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;
	*/

	memset(cache, -1, sizeof(cache));

	int ret = Enchant(9);
	cout << ret << endl;
}