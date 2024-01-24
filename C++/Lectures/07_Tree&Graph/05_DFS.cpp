#include <iostream>
using namespace std;
#include <vector>
#include <queue>

struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

// 방문한 목록
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);

	// 인접 리스트
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// 인접 행렬
	//adjacent = vector<Vector<int>>
	//{
	//	{0, 1, 0, 1, 0, 0},
	//	{1, 0, 1, 1, 0, 0},
	//	{0, 0, 0, 0, 0, 0},
	//	{0, 0, 0, 0, 1, 0},
	//	{0, 0, 0, 0, 0, 0},
	//	{0, 0, 0, 0, 1, 0},
	//}
}

void Dfs(int here)
{
	// 방문 도장
	visited[here] = true;
	cout << "Visited : " << here << endl;

	// 인접 리스트 O(V+E)
	const int size = adjacent[here].size();
	for (int i = 0; i < size; i++)
	{
		int there = adjacent[here][i]; // 인접 노드 모두 체크
		if (visited[there] == false) // 방문 여부 체크
			Dfs(there);
	}

	// 인접 행렬 O(V^2)
	//for (int there = 0; there < 6; there++)
	//{
	//	// 길이 있는지 여부
	//	if (adjacent[here][there] == 0)
	//		continue;

	//	// 아직 방문하지 않은 곳을 방문
	//	if (visited[there] == false)
	//		Dfs(there);
	//}
}

// 연결 여부와 상관없이 모든 노드를 둘러보기
void DfsAll()
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < 6; i++)
		if (visited[i] == false)
		{
			Dfs(i);
			cout << "Hi" << endl; // Hi가 2번 출력
		}
}

int main()
{
	CreateGraph();

	visited = vector<bool>(6, false);
	Dfs(0);
}