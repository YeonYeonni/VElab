#pragma once
#include "Vector.h"

// front�� ���� �����͸� ���� ��ġ
// [front][][][back][][] -> [][][front][back][][] �����͸� ������ front�� �ڷ� �̵�
// [front/back][][][][] front�� back�� ��ġ�� �������� ������ ���� x

template<typename T>
class Queue
{
public:
	Queue()
	{
		_container.resize(100);
	}

	// ť�� �����͸� �߰�
	void push(const T& value)
	{
		if (_size == _container.size())
		{

		}
		_container[_back] = value; // ť�� ���ʿ� ������ �߰�
		_back = (_back + 1) % _container.size(); // 
		_size++; // ť�� size ����
	}

	// ť�� �� �� �����͸� ����
	void pop()
	{
		_front = { _front + 1 } % _container.size();
		_size--;
	}

	// ť�� �� �� ��ҿ� ����
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

