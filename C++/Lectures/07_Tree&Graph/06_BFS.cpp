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

// 발견한 목록
vector<bool> discovered;

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

void Bfs(int here)
{
	// ex) 누구에 의해서 발견?
	vector<int> parent(6, -1);

	// ex) 시작점에서 얼만큼 떨어져 있는지?
	vector<int> dist(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	// 초기화
	parent[here] = here;
	dist[here] = 0;

	while (q.empty() == false)
	{
		// 시작점 삽입
		here = q.front();
		q.pop();

		// 방문 도장
		cout << "Visited : " << here << endl;

		int size = adjacent[here].size();  // 인접 노드 모두 체크

		// 인접 리스트
		for (int i = 0; i < size; i++)
		{
			int there = adjacent[here][i];
			if (discovered[there]) // 이미 발견한 노드면 무시
				continue;

			// 발견한적 없는 노드면 큐에 삽입 (방문 예약)
			q.push(there);
			discovered[there] = true;

			// 정보 추가
			parent[there] = here;
			dist[there] = dist[here] + 1;
		}

		// 인접 행렬
		//for (int there = 0; there < 6; there++)
		//{
		//	if (adjacent[here][there] == 0) // 끊겨있으면 무시
		//		continue;
		//	if (discovered[there]) // 이미 발견한 노드면 무시
		//		continue;
		//	q.push(there);
		//	discovered[there] = true;
		//}
	}
}

void BfsAll()
{
	discovered = vector<bool>(6, false);
	for (int i = 0; i < 6; i++)
		if (discovered[i] == false)
			Bfs(i);
}

int main()
{
	CreateGraph();
	discovered = vector<bool>(6, false);
	Bfs(0);
}