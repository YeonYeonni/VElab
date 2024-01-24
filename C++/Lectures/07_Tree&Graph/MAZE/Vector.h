#pragma once
#include <assert.h>

template<typename T>
class Vector
{
public:
	// 생성자
	explicit Vector()
	{
	}
	// 소멸자
	~Vector()
	{
		if (_buffer)
			delete[] _buffer;
	}

	// 현재 데이터들을 모두 소멸
	void clear()
	{
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}
		_size = 0;
	}

	// 데이터 밀어넣기
	void push_back(const T& data)
	{
		if (_size == _capacity)
		{
			// 증설 작업
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
		// 소멸 후 사이즈 줄이기
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

	// 새로운 capacity 요청. 크기에 따라 증설
	void reserve(int capacity)
	{
		// 작아지지는 않도록
		if (_capacity >= capacity)
			return;

		_capacity = capacity;

		T* newData = new T[_capacity]; // 더 큰 영역

		// 원래 데이터를 복사해 새로운 영역에 붙이기
		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		// 원래 공간을 삭제
		if (_buffer)
			delete[] _buffer;

		_buffer = newData;
	}

	// 값 변경 구현을 위함
	T& operator[](int index)
	{
		// 유효 범위 검사
		assert(index >= 0 && index < _size);
		return _buffer[index];
	}

	int size() { return _size; }
	int capacity() { return _capacity; } // 총 용량

private:
	T* _buffer = nullptr;
	int _size = 0;
	int _capacity = 0;
};