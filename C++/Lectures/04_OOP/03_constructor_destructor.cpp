// 설계도
class Knight
{
public:
	// 생성자 (constructor)
	Knight()
	{
		hp = 10;
		attack = 0;
		defence = 0;
		cout << "Knights()" << endl;
	}

	// 소멸자 (destructor)
	~Knight()
	{
		cout << "~Knights()" << endl;
	}