#include <iostream>
using namespace std;
#include <vector>
#include <queue>

// ���� ���
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};
	vector<Vertex> v(6);

	// ���� ����� ��ķ� ����
	// [X][O][X][O][X][X]
	// [O][X][O][O][X][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]
	// [X][X][X][X][X][X]
	// [X][X][X][X][O][X]

	// adjacent[from][to]
	vector<vector<bool>> adjacent(6, vector<bool>(6, false)); // ���� ����
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][2] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	// Q) 0��->3�� ����Ǿ� �ֳ���?
	bool connected = adjacent[0][3];
}

int main()
{
	
}