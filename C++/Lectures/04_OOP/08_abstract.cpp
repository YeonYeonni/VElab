class Player
{
public:
	virtual void Move() = 0; // 순수 가상 함수
	//virtual void Move() abstract;

public:
	int _hp;
};