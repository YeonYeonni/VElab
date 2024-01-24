#pragma once
#include "Vector.h"

// 원형 테이블 형태
// [front/back][][][][][][] // front와 back의 위치가 합쳐질때까지 데이터가 존재하는 것
// [front][][][back][][][] // 데이터를 꺼내면 front가 뒤로 이동. [][][front][back][][][]
// front가 다음 데이터를 꺼낼 위치

template<typename T>
class Queue
{
public:
	Queue()
	{
		_container.resize(100); // 100칸을 할당받고 시작
	}

	void push(const T& value)
	{
		// 만약 데이터가 다 찼을 경우, 용량을 늘린 벡터를 생성 -> 원래 데이터들을 복사
		if (_size == _container.size())
		{

		}

		_container[_back] = value;
		_back = (_back + 1) % _container.size(); // front/back이 index를 벗어날 경우 다시 맨 앞으로 이동. 나머지 연산 이용.
		_size++;
	}

	// front -> pop
	void pop() // front 커서를 뒤로 한 칸 움직임
	{
		_front = (_front + 1) % _container.size();
		_size--;
	}

	T& front() // front위치의 데이터 체크
	{
		return _container[_front];
	}

	bool empty() { return _size == 0; }
	int size() { return _size; }

private:
	Vector<T> _container;

	int _front = 0;
	int _back = 0;
	int _size = 0;
};