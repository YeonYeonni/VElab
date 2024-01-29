#include <iostream>
using namespace std;

class Pet
{
public:
	Pet() {}
	virtual ~Pet() {}
	Pet(const Pet& pet) {}
};

class Knight
{
public:
	Knight() // 기본 생성자 처리
	{
		_pet = new Pet();
	}

	~Knight()
	{
		delete _pet;
	}

	Knight(const Knight& k) // 복사 생성자 처리
	{
		_hp = k._hp;
		_pet = new Pet(*(k._pet));
	}

	void operator = (const Knight& k) // 복사 연산자
	{
		_hp = k._hp;
	}

public:
	int _hp = 100;
	Pet* _pet; // pet 객체의 포인터
};

int main()
{
	Knight k1; // 기본 생성자
	k1._hp = 200;

	Knight k2 = k1; // 복사 생성자. Knight 객체 k2를 생성 -> k1의 상태 복사.
	// Knight k2(k1);

	Knight k3; // 기본 생성자
	k3 = k1; // 복사 연산자
}