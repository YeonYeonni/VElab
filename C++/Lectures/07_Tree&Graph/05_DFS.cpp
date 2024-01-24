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

// �湮�� ���
vector<bool> visited;

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

void Dfs(int here)
{
	// �湮 ����
	visited[here] = true;
	cout << "Visited : " << here << endl;

	// ���� ����Ʈ O(V+E)
	const int size = adjacent[here].size();
	for (int i = 0; i < size; i++)
	{
		int there = adjacent[here][i]; // ���� ��� ��� üũ
		if (visited[there] == false) // �湮 ���� üũ
			Dfs(there);
	}

	// ���� ��� O(V^2)
	//for (int there = 0; there < 6; there++)
	//{
	//	// ���� �ִ��� ����
	//	if (adjacent[here][there] == 0)
	//		continue;

	//	// ���� �湮���� ���� ���� �湮
	//	if (visited[there] == false)
	//		Dfs(there);
	//}
}

// ���� ���ο� ������� ��� ��带 �ѷ�����
void DfsAll()
{
	visited = vector<bool>(6, false);

	for (int i = 0; i < 6; i++)
		if (visited[i] == false)
		{
			Dfs(i);
			cout << "Hi" << endl; // Hi�� 2�� ���
		}
}

int main()
{
	CreateGraph();

	visited = vector<bool>(6, false);
	Dfs(0);
}