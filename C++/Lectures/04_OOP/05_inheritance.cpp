class Player // 부모 클래스
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

class Knight : public Player // 자식 클래스
{
public:

public:
};

class Archer : public Player // 자식 클래스
{
public:

public:
	int _arrowCount;
};