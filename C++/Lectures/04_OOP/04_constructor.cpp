// ���赵
class Knight
{
public:
	// ������ (constructor)
	// 1. �⺻ ������ (constructor)
	Knight()
	{
		cout << "Knights()" << endl;
	}

	// 2. �Ϲ�/��Ÿ ������
	Knight(int hp, int attack, int defence)
	{
		hp = 0;
		attack = 0;
		defence = 0;
		cout << "Knights()" << endl;
	}

	// 3. ���� ������
	Knight(const Knight& other) // ������ ����. ������ ��ĥ ���� ������ const
	{
		this->hp = other.hp;
		this->attack = other.attack;
		this->defence = other.defence;
		cout << "Knights(const Knight&)" << endl;
	}

	// �Ҹ��� (destructor)
	~Knight()
	{
		cout << "~Knights()" << endl;
	}