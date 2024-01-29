#pragma once
#include "Vector.h"

// front가 다음 데이터를 꺼낼 위치
// [front][][][back][][] -> [][][front][back][][] 데이터를 꺼내면 front가 뒤로 이동
// [front/back][][][][] front와 back의 위치가 합쳐지면 데이터 존재 x

template<typename T>
class Queue
{
public:
	Queue()
	{
		_container.resize(100);
	}

	// 큐에 데이터를 추가
	void push(const T& value)
	{
		if (_size == _container.size())
		{

		}
		_container[_back] = value; // 큐의 뒤쪽에 데이터 추가
		_back = (_back + 1) % _container.size(); // 
		_size++; // 큐의 size 증가
	}

	// 큐의 맨 앞 데이터를 제거
	void pop()
	{
		_front = { _front + 1 } % _container.size();
		_size--;
	}

	// 큐의 맨 앞 요소에 접근
	T& front()
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

