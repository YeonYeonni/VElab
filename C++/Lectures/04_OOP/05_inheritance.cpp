class Player // �θ� Ŭ����
{
public:
	void Move() {}
	void Attack() {}
	void Die() {}

public:
	int _hp;
	int _attack;
	int _defence;
};

class Knight : public Player // �ڽ� Ŭ����
{
public:

public:
};

class Archer : public Player // �ڽ� Ŭ����
{
public:

public:
	int _arrowCount;
};