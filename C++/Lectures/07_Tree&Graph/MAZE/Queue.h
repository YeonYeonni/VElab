#pragma once
#include "Vector.h"

// ���� ���̺� ����
// [front/back][][][][][][] // front�� back�� ��ġ�� ������������ �����Ͱ� �����ϴ� ��
// [front][][][back][][][] // �����͸� ������ front�� �ڷ� �̵�. [][][front][back][][][]
// front�� ���� �����͸� ���� ��ġ

template<typename T>
class Queue
{
public:
	Queue()
	{
		_container.resize(100); // 100ĭ�� �Ҵ�ް� ����
	}

	void push(const T& value)
	{
		// ���� �����Ͱ� �� á�� ���, �뷮�� �ø� ���͸� ���� -> ���� �����͵��� ����
		if (_size == _container.size())
		{

		}

		_container[_back] = value;
		_back = (_back + 1) % _container.size(); // front/back�� index�� ��� ��� �ٽ� �� ������ �̵�. ������ ���� �̿�.
		_size++;
	}

	// front -> pop
	void pop() // front Ŀ���� �ڷ� �� ĭ ������
	{
		_front = (_front + 1) % _container.size();
		_size--;
	}

	T& front() // front��ġ�� ������ üũ
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