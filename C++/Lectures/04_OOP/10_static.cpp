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
		// attack�� static �����ӿ��� �ʱ�ȭ.
		attack = value;
	}

public:
	// Ư�� ��ü�� ����
	int hp = 40;

	// Ư�� ��ü�� ����
	static int attack;
};

int Marine::attack = 6;