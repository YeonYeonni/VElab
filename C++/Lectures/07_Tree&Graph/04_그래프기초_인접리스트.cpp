#include <iostream>
using namespace std;
#include <vector>
#include <queue>

// ���� ����Ʈ : ����� ��常 �����ϵ��� [v][v][ ][v][ ][v]
void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};

	vector<Vertex> v(6);

	// [v][v][v][v][v][v]
	vector<vector<int>> adjacent; // ���� ����
	adjacent.resize(6);
	
	// [v][v][ ][v][ ][v]
	adjacent[0] = {1, 3};
	adjacent[1] = {0, 2, 3};
	adjacent[3] = {4};
	adjacent[5] = {4};

	// Q) 0��->3�� ����Ǿ� �ֳ���?
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