#pragma once
#include <assert.h>

template<typename T>
class Vector
{
public:
	// ������
	explicit Vector()
	{
	}
	// �Ҹ���
	~Vector()
	{
		if (_buffer)
			delete[] _buffer;
	}

	// ���� �����͵��� ��� �Ҹ�
	void clear()
	{
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}
		_size = 0;
	}

	// ������ �о�ֱ�
	void push_back(const T& data)
	{
		if (_size == _capacity)
		{
			// ���� �۾�
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}
		_buffer[_size] = data;
		_size++;
	}

	void pop_back()
	{
		// �Ҹ� �� ������ ���̱�
		_size--;
	}

	T& back()
	{
		return _buffer[_size - 1];
	}

	void resize(int size)
	{
		reserve(size);
		_size = size;
	}

	// ���ο� capacity ��û. ũ�⿡ ���� ����
	void reserve(int capacity)
	{
		// �۾������� �ʵ���
		if (_capacity >= capacity)
			return;

		_capacity = capacity;

		T* newData = new T[_capacity]; // �� ū ����

		// ���� �����͸� ������ ���ο� ������ ���̱�
		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		// ���� ������ ����
		if (_buffer)
			delete[] _buffer;

		_buffer = newData;
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