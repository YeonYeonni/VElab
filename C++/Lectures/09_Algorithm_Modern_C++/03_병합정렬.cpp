#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <queue>

// 분할 정복
// [3][K][7][2][J][4][8][9] << 8개*1
// [3][K][7][2]	[J][4][8][9] << 4개*2
// [3][K]	[7][2]	[J][4]	[8][9] << 2개*4
// [3]	[K]	[7]	[2]	[J]	[4]	[8]	[9] << 1개*8
// [3][K]	[2][7]	[4][J]	[8][9] << 2개*4
// [2][3][7][K]	[4][8][9][J] << 4개*2
// [2][3][4][7][8][9][J][K]	<< 8개*1

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;

	vector<int> temp; // 정렬된 데이터를 넣어줄 벡터

	while (leftIdx <= mid && rightIdx <= right)
	{
		if (v[leftIdx] <= v[rightIdx])
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}

	// 왼쪽이 먼저 끝
	if (leftIdx > mid)
	{
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	// 오른쪽이 먼저 끝
	else
	{
		while (leftIdx <= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	for (int i = 0; i < temp.size(); i++)
		v[left + i] = temp[i];
}

void MergeSort(vector<int>& v, int left, int right)
{
	// 분할된 데이터가 하나일 경우 함수 종료
	if (left >= right)
		return;

	int mid = (left + right) / 2;
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	MergeResult(v, left, mid, right);
}

int main()
{
	vector<int> v{ 1, 5, 3, 4, 2 };
	MergeSort(v, 0, v.size() - 1);
}