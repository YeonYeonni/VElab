#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

int main()
{
	// C ��Ÿ��
	const char* name = "Yeon";
	const char* name2 = "Yeon";

	if (name == name2)
		cout << "����" << endl;
	else
		cout << "�ٸ�" << endl;

	char name[] = "Yeon";
	char name2[] = "Yeon";

	if (name == name2)
		cout << "����" << endl;
	else
		cout << "�ٸ�" << endl;

	// C++ ��Ÿ��
	std::string str = "Yeon";
	std::string str2 = "Yeon";

	// ��
	if (str == str2) {}

	// ����
	string str3;
	str3 = str;

	// �߰�
	str.append("1234");
	str += "1234";

	// ã��
	auto c = str.find("Ye");
	if (c == std::string::npos)
	{
		cout << "not found";
	}

	// ��ü
	string chatStr = "SHIT !!!";
	string findStr = "SHIT";
	string replaceStr = "****";

	charStr.replace(chatStr, find(findStr), findStr, length(), replaceStr);

	string str4 = str.substr(0, 3);

	const chat* name = str.c_str();
}