// static
class Marine
{
public:
	void TakeDamage(int damage)
	{
		hp -= damage;
	}

	static void SetAttack(int value)
	{
		// attack은 static 변수임에도 초기화.
		attack = value;
	}

public:
	// 특정 객체와 연관
	int hp = 40;

	// 특정 객체와 무관
	static int attack;
};

int Marine::attack = 6;