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
		// 1) 트리 구조 맞춰줌
		_heap.push_back(data);

		// 2) 부모 노드 vs 새로운 노드
		int now = static_cast<int>(_heap.size()) - 1;

		// 3) 루트 노드까지
		while (now > 0)
		{
			// 새로운 노드가 작으면 종료
			int nex = (now - 1) / 2; // 부모 노드 인덱스
			if (_predicate(_heap[now], _heap[next]))
				break;

			// 새로운 노드가 크면 교체
			::swap(_heap[now]._heap[next]);
			now = next;
		}
	}

	// O(logN)
	void pop()
	{
		// 루트 제거
		_heap[0] = _heap.back();
		_heap.pop_back();

		// 마지막 노드를 루트로 이동
		int now = 0;

		// 비교
		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			// leaf에 도달한 경우 종료
			if (left >= (int)_heap.size())
				break;

			int next = now;

			// 왼쪽 비교
			if (_heap[next] < _heap[left])
				next = left;

			// 왼쪽 비교의 승자를 오른쪽과 비교
			if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
				next = right;

			// 왼쪽/오른쪽 둘 다 현재 값보다 작으면 종료
			if (next == now)
				break;

			// 노드 교체
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

	// 트리 만들기
	pq.push(10);
	pq.push(40);
	pq.push(30);
	pq.push(50);
	pq.push(20);

	// 최대값 제거
	int value = pq.top();
	pq.pop();
}