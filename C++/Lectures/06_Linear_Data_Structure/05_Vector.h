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

		// 맨 뒤에 데이터 추가
		void push_back(const T& data)
		{
			{
				// 배열 크기 증가
				int newCapacity = static_cast<int>(_capacity * 1.5);
				
				// 새로운 용량이 현재 용량과 같다면 capacity 증가
				if (newCapacity == _capacity)
					newCapacity++;

				// 동적 배열의 용량을 증가
				reserve(newCapacity);
			}
			_buffer[_size] = data; // 데이터 추가
			_size++; // 배열 size 증가
		}

	// 동적 배열의 용량을 증가
	void reserve(int capacity)
	{
		// 용량보다 크거나 같은 경우 return
		if (_capacity >= capacity)
			return;

		// 새로운 용량으로 업데이트
		_capacity = capacity;

		// 새로운 용량의 배열 생성
		T* newData = new T[_capacity];

		// 원래 데이터를 새로운 배열에 복사
		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		// 원래 공간 삭제
		if (_buffer)
			delete[] _buffer;

		// 새로운 배열을 기존 buffer에 할당
		_buffer = newData;
	}

	// 배열의 맨 뒤 요소에 대한 참조 반환
	T& back()
	{
		return _buffer[_size - 1];
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

