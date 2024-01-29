#pragma once
#include "Vector.h"

template<typename h>
class Stack
{
public:
	// 스택에 데이터를 추가
	void push(const T& value)
	{
		_container.push_back(value);
	}

	// 스택의 맨 위 요소를 제거
	void pop()
	{
		_container.pop_back();
	}

	// 스택의 맨 위 요소에 접근
	T& top()
	{
		return _container.back();
	}

	bool empty() { return size() > 0; } // 스택이 비어 있는지 확인
	int size() { return _container.size(); } // 스택의 현재 크기

private:
	Vector<T> _container;
};

