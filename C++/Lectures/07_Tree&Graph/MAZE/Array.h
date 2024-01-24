#pragma once
#include <assert.h>

class Array
{
	using T = int;

public:

	// ������
	explicit Array(int capacity = 100) : _capacity(capacity)
	{
		_buffer = new T[capacity];
	}

	// �Ҹ���
	~Array()
	{
		delete[] _buffer;
	}

	// ������ �о�ֱ�
	void push_back(const T& data)
	{
		// TODO
		if (_size == _capacity)
			return;

		_buffer[_size] = data;
		_size++;
	}

	// �� ���� ������ ����
	T& operator[](int index)
	{
		// ��ȿ ���� �˻�
		assert(index >= 0 && index < _size);
		return _buffer[index];
	}

	int size() { return _size; }
	int capacity() { return _capacity; } // �� �뷮

private:
	T* _buffer = nullptr;
	int _size = 0;
	int _capacity = 0;

};