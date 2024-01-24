#include <iostream>
using namespace std;
#include <vector>
#include <queue>

template<typename T, typename Predicate = less<T>>
class PriorityQueue
{
public:
	// O(logN)
	void push(const T& data)
	{
		// 1) Ʈ�� ���� ������
		_heap.push_back(data);

		// 2) �θ� ��� vs ���ο� ���
		int now = static_cast<int>(_heap.size()) - 1;

		// 3) ��Ʈ ������
		while (now > 0)
		{
			// ���ο� ��尡 ������ ����
			int nex = (now - 1) / 2; // �θ� ��� �ε���
			if (_predicate(_heap[now], _heap[next]))
				break;

			// ���ο� ��尡 ũ�� ��ü
			::swap(_heap[now]._heap[next]);
			now = next;
		}
	}

	// O(logN)
	void pop()
	{
		// ��Ʈ ����
		_heap[0] = _heap.back();
		_heap.pop_back();

		// ������ ��带 ��Ʈ�� �̵�
		int now = 0;

		// ��
		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			// leaf�� ������ ��� ����
			if (left >= (int)_heap.size())
				break;

			int next = now;

			// ���� ��
			if (_heap[next] < _heap[left])
				next = left;

			// ���� ���� ���ڸ� �����ʰ� ��
			if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
				next = right;

			// ����/������ �� �� ���� ������ ������ ����
			if (next == now)
				break;

			// ��� ��ü
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	// O(1)
	T& top()
	{
		return _heap[0];
	}

	// O(1)
	bool empty()
	{
		return _heap.empty();
	}

private:
	vector<T> _heap;
	Predicate _predicate;
};

int main()
{
	priority_queue<int> pq;
	//priority_queue<int> pq;

	// Ʈ�� �����
	pq.push(10);
	pq.push(40);
	pq.push(30);
	pq.push(50);
	pq.push(20);

	// �ִ밪 ����
	int value = pq.top();
	pq.pop();
}