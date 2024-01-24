#pragma once
#include <assert.h>

class Array
{
	using T = int;

public:

	// 생성자
	explicit Array(int capacity = 100) : _capacity(capacity)
	{
		_buffer = new T[capacity];
	}

	// 소멸자
	~Array()
	{
		delete[] _buffer;
	}

	// 데이터 밀어넣기
	void push_back(const T& data)
	{
		// TODO
		if (_size == _capacity)
			return;

		_buffer[_size] = data;
		_size++;
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