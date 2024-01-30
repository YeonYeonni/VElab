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

	// ���� ������
	Knight(const Knight& knight)
	{

	}

	// ���� ���� ������
	void operator=(const Knight& knight)
	{
		_hp = knight._hp;
		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}

	// �̵� ������
	Knight(Knight&& knight)
	{

	}

	// �̵� ���� ������
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

// �����ؼ� �Ѱ���. ������ ���� ����.
void TestKnight_Copy(Knight knight)
{
	knight._hp = 100;
}

// ������ �Ѱ���. �� ���� ����.
void TestKnight_LValueRef(Knight& knight)
{
	knight._hp = 100;
}

// ������ �Ѱ���. �� ���� �Ұ���.
void TestKnight_ConstLValueRef(const Knight& knight)
{
}

// ������ �Ѱ���. ������ ���� Ȱ������ ������ �� ���� ����.
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
	k2 = k1; // ���� ���� ������ ���

	k2 = static_cast<Knight&&>(k1); // �̵� ���� ������ ���
	// k2 = std::move(k1);
}