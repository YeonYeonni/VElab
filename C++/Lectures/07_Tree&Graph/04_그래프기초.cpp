#include <iostream>
using namespace std;
#include <vector>
#include <queue>

void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*>edges; // ������ ����� ����
	};

	vector<Vertex> v(6);
	v[0].edges.push_back(&v[1]);
	v[0].edges.push_back(&v[3]);
	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);
	v[3].edges.push_back(&v[4]);
	v[5].edges.push_back(&v[4]);

	// Q) 0��->3���� ����Ǿ� �ֳ���?
	bool connected = false;

	int size = v[0].edges.size();
	for (int i = 0; i < size; i++)
	{
		Vertex* vertex = c[0].edges[i];
		if (vertex == &v[3])
		{
			connected = true;
		}
	}
}

int main()
{
		
}