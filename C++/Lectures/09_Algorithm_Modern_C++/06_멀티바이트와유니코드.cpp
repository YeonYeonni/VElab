#include <iostream>
using namespace std;

int main()
{
	// 문자열에 한글 포함
	const char* test = "연여니";
	cout << test << endl; // 연여니

	// ANSI
	setlocale(LC_ALL, "");
	cout << "LC_ALL: " << setlocale(LC_ALL, NULL) << endl;

	// UTF-8
	auto test2 = u8"aaa안녕하세요";
	setlocale(LC_ALL, "en_US.UTF-8");
	cout << test2 << endl;

	// WBCS
	//wchar_t ch = L"안"; // 2byte
	wstring name = L"aaa안녕하세요"; // 2byte * N
	wcout << name << endl;
}