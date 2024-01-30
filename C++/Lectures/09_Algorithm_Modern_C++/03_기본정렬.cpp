#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <queue>

void Bubblesort(vector<int>& v) // O(N^2)
{
	const int n = v.size();

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (v[j] > v[j + 1])
			{
				/*
				int temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
				*/
				swap(v[j], v[j + 1]);
			}
		}
	}
}

void SelectionSort(vector<int>& v) // O(N^2)
{
	const int n = v.size();

	for (int i = 0; i < n - 1; i++)
	{
		int bestIdx = i;
		
		for (int j = i + 1; j < n; j++)
		{
			if (v[j] < v[bestIdx])
				bestIdx = j;
		}
		swap(v[i], v[bestIdx]);
	}
}

void HeapSort(vector<int>& v) // O(Nlog N)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	// 벡터 -> 우선순위큐 //O(Nlog N)
	for (int num : v)
		pq.push(num); // O(log N)

	v.clear(); // 벡터 삭제

	// O(Nlog N)
	while (pq.empty() == false) // 데이터가 있는 동안
	{
		v.push_back(pq.top()); // O(1)
		pq.pop(); // O(log N)
	}
}

int main()
{
	vector<int> v{ 1, 5, 3, 4, 2 };
}