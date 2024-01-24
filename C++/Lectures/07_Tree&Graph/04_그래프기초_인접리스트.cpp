#include <iostream>
using namespace std;
#include <vector>
#include <queue>

// 인접 리스트 : 연결된 노드만 존재하도록 [v][v][ ][v][ ][v]
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	// [v][v][v][v][v][v]
	vector<vector<int>> adjacent; // 이중 벡터
	adjacent.resize(6);
	
	// [v][v][ ][v][ ][v]
	adjacent[0] = {1, 3};
	adjacent[1] = {0, 2, 3};
	adjacent[3] = {4};
	adjacent[5] = {4};

	// Q) 0번->3번 연결되어 있나요?
	bool connected = false;
	int size = adjacent[0].size();
	for (int i = 0; i < size; i++)
	{
		int vertex = adjacent[0][i];
		if (vertex == 3)
		{
			connected = true;
		}
	}
 }

int main()
{
	
}