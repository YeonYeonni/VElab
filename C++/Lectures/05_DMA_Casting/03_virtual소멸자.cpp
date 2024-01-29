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
	Knight() // �⺻ ������ ó��
	{
		_pet = new Pet();
	}

	~Knight()
	{
		delete _pet;
	}

	Knight(const Knight& k) // ���� ������ ó��
	{
		_hp = k._hp;
		_pet = new Pet(*(k._pet));
	}

	void operator = (const Knight& k) // ���� ������
	{
		_hp = k._hp;
	}

public:
	int _hp = 100;
	Pet* _pet; // pet ��ü�� ������
};

int main()
{
	Knight k1; // �⺻ ������
	k1._hp = 200;

	Knight k2 = k1; // ���� ������. Knight ��ü k2�� ���� -> k1�� ���� ����.
	// Knight k2(k1);

	Knight k3; // �⺻ ������
	k3 = k1; // ���� ������
}