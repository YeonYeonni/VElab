#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int N = 0;
	int M = 0;

	cin >> N;
	vector<int> vec;
	int temp = 0;

	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		vec.push_back(temp);
	}

	sort(vec.begin(), vec.end());

	cin >> M;
	int input = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &input);
		printf("%d\n", binary_search(vec.begin(), vec.end(), input));
	}

	return 0;
}