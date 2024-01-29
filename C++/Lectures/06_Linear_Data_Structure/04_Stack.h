#pragma once
#include "Vector.h"

template<typename h>
class Stack
{
public:
	// ���ÿ� �����͸� �߰�
	void push(const T& value)
	{
		_container.push_back(value);
	}

	// ������ �� �� ��Ҹ� ����
	void pop()
	{
		_container.pop_back();
	}

	// ������ �� �� ��ҿ� ����
	T& top()
	{
		return _container.back();
	}

	bool empty() { return size() > 0; } // ������ ��� �ִ��� Ȯ��
	int size() { return _container.size(); } // ������ ���� ũ��

private:
	Vector<T> _container;
};

