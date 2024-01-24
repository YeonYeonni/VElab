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

// �߰��� ���
vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);

	// ���� ����Ʈ
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	// ���� ���
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
	// ex) ������ ���ؼ� �߰�?
	vector<int> parent(6, -1);

	// ex) ���������� ��ŭ ������ �ִ���?
	vector<int> dist(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	// �ʱ�ȭ
	parent[here] = here;
	dist[here] = 0;

	while (q.empty() == false)
	{
		// ������ ����
		here = q.front();
		q.pop();

		// �湮 ����
		cout << "Visited : " << here << endl;

		int size = adjacent[here].size();  // ���� ��� ��� üũ

		// ���� ����Ʈ
		for (int i = 0; i < size; i++)
		{
			int there = adjacent[here][i];
			if (discovered[there]) // �̹� �߰��� ���� ����
				continue;

			// �߰����� ���� ���� ť�� ���� (�湮 ����)
			q.push(there);
			discovered[there] = true;

			// ���� �߰�
			parent[there] = here;
			dist[there] = dist[here] + 1;
		}

		// ���� ���
		//for (int there = 0; there < 6; there++)
		//{
		//	if (adjacent[here][there] == 0) // ���������� ����
		//		continue;
		//	if (discovered[there]) // �̹� �߰��� ���� ����
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