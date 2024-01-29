#pragma once
#include <assert.h>
class Array
{
	using T = int;

public:
	explicit Array(int capacity = 100) : _capacity(capacity)
	{
		// 동적 배열 생성
		_buffer = new T[capacity];
	}
	~Array()
	{
		// 동적 배열 삭제
		delete[] _buffer;
	}

	// 맨 뒤에 데이터 추가
	void push_back(const T& data)
	{
		// 배열이 가득 차면 추가하지 않음
		if (_size == _capacity)
			return;

		_buffer[_size] = data; // 데이터 추가
		_size++; // 배열 size 증가
	}

	// 인덱스로 접근해 값 변경
	T& operator[](int index)
	{
		assert(index >= 0 && index < _size); // 인덱스 유효성 검사
		return _buffer[index]; // 해당 인덱스의 값 반환
	}

	int size() { return _size; } // 배열의 현재 크기
	int capacity() { return _capacity; } // 배열의 용량

private:
	T* _buffer = nullptr;
	int _size = 0;
	int _capacity = 0;
};

