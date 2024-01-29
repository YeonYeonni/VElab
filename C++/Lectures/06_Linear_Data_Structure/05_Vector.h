#pragma once
#include <assert.h>

class Vector
{
	using T = int;

public:
	explicit Vector()
	{
	}
	~Vector()
	{
		if (_buffer)
			delete[] _buffer;
	}

		// �� �ڿ� ������ �߰�
		void push_back(const T& data)
		{
			{
				// �迭 ũ�� ����
				int newCapacity = static_cast<int>(_capacity * 1.5);
				
				// ���ο� �뷮�� ���� �뷮�� ���ٸ� capacity ����
				if (newCapacity == _capacity)
					newCapacity++;

				// ���� �迭�� �뷮�� ����
				reserve(newCapacity);
			}
			_buffer[_size] = data; // ������ �߰�
			_size++; // �迭 size ����
		}

	// ���� �迭�� �뷮�� ����
	void reserve(int capacity)
	{
		// �뷮���� ũ�ų� ���� ��� return
		if (_capacity >= capacity)
			return;

		// ���ο� �뷮���� ������Ʈ
		_capacity = capacity;

		// ���ο� �뷮�� �迭 ����
		T* newData = new T[_capacity];

		// ���� �����͸� ���ο� �迭�� ����
		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		// ���� ���� ����
		if (_buffer)
			delete[] _buffer;

		// ���ο� �迭�� ���� buffer�� �Ҵ�
		_buffer = newData;
	}

	// �迭�� �� �� ��ҿ� ���� ���� ��ȯ
	T& back()
	{
		return _buffer[_size - 1];
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

