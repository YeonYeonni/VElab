#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

int main()
{
	// C 스타일
	const char* name = "Yeon";
	const char* name2 = "Yeon";

	if (name == name2)
		cout << "같음" << endl;
	else
		cout << "다름" << endl;

	char name[] = "Yeon";
	char name2[] = "Yeon";

	if (name == name2)
		cout << "같음" << endl;
	else
		cout << "다름" << endl;

	// C++ 스타일
	std::string str = "Yeon";
	std::string str2 = "Yeon";

	// 비교
	if (str == str2) {}

	// 복사
	string str3;
	str3 = str;

	// 추가
	str.append("1234");
	str += "1234";

	// 찾기
	auto c = str.find("Ye");
	if (c == std::string::npos)
	{
		cout << "not found";
	}

	// 교체
	string chatStr = "SHIT !!!";
	string findStr = "SHIT";
	string replaceStr = "****";

	charStr.replace(chatStr, find(findStr), findStr, length(), replaceStr);

	string str4 = str.substr(0, 3);

	const chat* name = str.c_str();
}