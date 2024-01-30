#include <iostream>
using namespace std;

class Pet
{

};

class Knight
{
public:

	Knight()
	{

	}

	~Knight()
	{
		if (_pet)
			delete _pet;
	}

	// 복사 생성자
	Knight(const Knight& knight)
	{

	}

	// 복사 대입 연산자
	void operator=(const Knight& knight)
	{
		_hp = knight._hp;
		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}

	// 이동 생성자
	Knight(Knight&& knight)
	{

	}

	// 이동 대입 연산자
	void operator=(Knight&& knight)
	{
		_hp = knight._hp;
		_pet = knight._pet;
		knight._pet = nullptr;
	}

public:
	int _hp = 0;
	Pet* _pet = nullptr;
};

// 복사해서 넘겨줌. 원본에 영향 없음.
void TestKnight_Copy(Knight knight)
{
	knight._hp = 100;
}

// 원본을 넘겨줌. 값 수정 가능.
void TestKnight_LValueRef(Knight& knight)
{
	knight._hp = 100;
}

// 원본을 넘겨줌. 값 수정 불가능.
void TestKnight_ConstLValueRef(const Knight& knight)
{
}

// 원본을 넘겨줌. 원본을 더는 활용하지 않으니 값 수정 가능.
void TestKnight_RValueRef(Knight&& knight)
{
	knight._hp = 100;
}

int main()
{
	Knight k1;

	TestKnight_Copy(k1);
	TestKnight_LValueRef(k1);
	TestKnight_ConstLValueRef(Knight());
	TestKnight_RValueRef(Knight());
	TestKnight_RValueRef(static_cast<Knight&&>(k1));

	k1._pet = new Pet();
	
	Knight k2;
	k2 = k1; // 복사 대입 연산자 사용

	k2 = static_cast<Knight&&>(k1); // 이동 대입 연산자 사용
	// k2 = std::move(k1);
}