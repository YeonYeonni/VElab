#pragma once
#include <assert.h>
class Array
{
	using T = int;

public:
	explicit Array(int capacity = 100) : _capacity(capacity)
	{
		// ���� �迭 ����
		_buffer = new T[capacity];
	}
	~Array()
	{
		// ���� �迭 ����
		delete[] _buffer;
	}

	// �� �ڿ� ������ �߰�
	void push_back(const T& data)
	{
		// �迭�� ���� ���� �߰����� ����
		if (_size == _capacity)
			return;

		_buffer[_size] = data; // ������ �߰�
		_size++; // �迭 size ����
	}

	// �ε����� ������ �� ����
	T& operator[](int index)
	{
		assert(index >= 0 && index < _size); // �ε��� ��ȿ�� �˻�
		return _buffer[index]; // �ش� �ε����� �� ��ȯ
	}

	int size() { return _size; } // �迭�� ���� ũ��
	int capacity() { return _capacity; } // �迭�� �뷮

private:
	T* _buffer = nullptr;
	int _size = 0;
	int _capacity = 0;
};

