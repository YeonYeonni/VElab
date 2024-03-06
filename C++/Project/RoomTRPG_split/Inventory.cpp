#include "pch.h"
#include "Inventory.h"

// 생성자
Inventory::Inventory()
{
	// 배열의 모든 값을 null로 초기화
	for (int i = 0; i < MAX_SLOT; i++)
		_signs[i] = nullptr;
}

// 소멸자
Inventory::~Inventory()
{
}

// FindEmptySlot 함수를 사용해 빈 곳의 위치를 얻은 뒤, 원하는 값을 삽입. signCount를 1 증가.
bool Inventory::AddInven(string* sign)
{
	// 예외 처리) 받아온 값이 null이면 AddInven 함수를 실행하지 않음.
	if (sign == nullptr)
		return false;

	// FindEmpty 함수 사용. 빈 곳의 위치를 emptySlot에 저장.
	int emptySlot = FindEmptySlot();

	// 예외 처리) FindEmpty 함수 작동이 실패 (-1) 하면 AddInven 함수를 실행하지 않음.
	if (emptySlot < 0)
		return false;

	// 정상 작동
	_signs[emptySlot] = sign; // 빈 곳에 원하는 값을 삽입.
	_signCount++; // 현재 배열의 개수를 1 증가.
	return true;
}

// FindItemSlot 함수를 사용해 찾고자 하는 값의 위치를 얻은 뒤, 값을 null로 변경. signCount를 1 감소
bool Inventory::RemoveInven(string* sign)
{
	// 예외 처리) 받아온 값이 null이면 RemoveInven 함수를 실행하지 않음.
	if (sign == nullptr)
		return false;

	// FindItemSlot 함수 사용. 제거하고자 하는 값의 위치를 slot에 저장.
	int slot = FindItemSlot(sign);

	// 예외 처리) FindItemSlot 함수 작동이 실패 (-1) 하면 RemoveInven 함수를 실행하지 않음.
	if (slot < 0)
		return false;

	// 정상 작동
	_signs[slot] = nullptr; // 값이 있던 곳에 null을 삽입.
	_signCount--; // 현재 배열의 개수를 1 감소.
	return true;
}

// 배열을 오름차순 정렬
bool Inventory::SortInven()
{
	if (_signCount > 0)
	{
		std::sort(_signs, _signs + _signCount, [](string* a, string* b)
			{ return *a < *b; });
		return true;
	}
	return false;
}

// 배열 전체를 null로 초기화
void Inventory::Clear()
{
	for (int i = 0; i < MAX_SLOT; i++)
	{
		if (_signs[i])
		{
			delete _signs[i];
			_signs[i] = nullptr;
		}
	}
}

// 배열을 순회하면서 빈 곳의 위치를 반환
int Inventory::FindEmptySlot()
{
	// 정상 작동
	for (int i = 0; i < MAX_SLOT; i++)
	{
		// 값이 없는 곳을 찾으면 그 위치를 반환.
		if (_signs[i] == nullptr)
			return i;
	}

	// 예외 발생) 배열이 모두 차있으면 -1 반환.
	return -1;
}

// 배열을 순회하면서 찾고자 하는 값의 위치를 반환.
int Inventory::FindItemSlot(string* sign)
{
	// 정상 작동
	for (int i = 0; i < MAX_SLOT; i++)
	{
		// 원하는 값을 찾으면 그 위치를 반환.
		if (_signs[i] == sign)
			return i;
	}
	// 예외 발생) 찾고자 하는 값이 없으면 -1 반환.
	return -1;
}
