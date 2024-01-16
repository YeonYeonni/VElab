#include <iostream>
using namespace std;

// �̱���
class UserManager
{
public:
	static UserManager* GetInstance()
	{
		static UserManager um;
		return &um;
	}
public:
	void AddUser() { _userCount++; }
	int GetUserCount() { return _userCount; }

private:
	int _userCount = 0;
};

int main()
{
	// 10���� �ν��Ͻ�
	for (int i = 0; i < 10; i++)
		UserManager::GetInstance()->AddUser();

	cout << UserManager::GetInstance()->GetUserCount() << endl;
}