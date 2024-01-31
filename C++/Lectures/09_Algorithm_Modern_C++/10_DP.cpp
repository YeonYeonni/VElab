#include <unordered_map>
#include <algorithm>
#include <Windows.h>

#include <iostream>
using namespace std;

// �޸������̼� (memoization)
//int cache[50][50];

/*
int combination(int n, int r)
{
	// ���� ���
	if (r == 0 || n == r)
		return 1;

	// �̹� ���� ���� �� ������ �ٷ� ��ȯ
	int& ret = cache[n][r];
	if (ret != -1)
		return ret;

	ret = combination(n - 1, r - 1) + combination(n - 1, r);
	return ret;
*/

// +9�� �������� �ߴ� ����� ����?
// ex) 1, 2, 3, 4, ..., 9
// ex) 3, 6, 9
// ex) 1, 3, 4, ..., 9

int N = 9;
int cache[100];

// [+num]���� �����ؼ�, [+N]���� ���� ����� ��
int Enchant(int num)
{
	// ���� ���
	if (num > N)
		return 0;

	if (num == N)
		return 1;

	// ĳ��
	int& ret = cache[num];
	if (ret != -1)
		return ret;

	// ����
	return ret = Enchant(num + 1) + Enchant(num + 2) + Enchant(num + 3);
}

int main()
{
	/*
	::memset(cache, -1, sizeof(cache)); // �ʱⰪ -1

	__int64 start = GetTickCount64();

	int lotto = combination(45, 6);

	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;
	*/

	memset(cache, -1, sizeof(cache));

	int ret = Enchant(9);
	cout << ret << endl;
}