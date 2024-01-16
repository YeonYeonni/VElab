// 설계도
class Knight
{
public:
	// 생성자 (constructor)
	// 1. 기본 생성자 (constructor)
	Knight()
	{
		cout << "Knights()" << endl;
	}

	// 2. 일반/기타 생성자
	Knight(int hp, int attack, int defence)
	{
		hp = 0;
		attack = 0;
		defence = 0;
		cout << "Knights()" << endl;
	}

	// 3. 복사 생성자
	Knight(const Knight& other) // 원본을 참조. 원본을 고칠 일은 없으니 const
	{
		this->hp = other.hp;
		this->attack = other.attack;
		this->defence = other.defence;
		cout << "Knights(const Knight&)" << endl;
	}

	// 소멸자 (destructor)
	~Knight()
	{
		cout << "~Knights()" << endl;
	}