#include <iostream>
using namespace std;

int main()
{
	// ���ڿ��� �ѱ� ����
	const char* test = "������";
	cout << test << endl; // ������

	// ANSI
	setlocale(LC_ALL, "");
	cout << "LC_ALL: " << setlocale(LC_ALL, NULL) << endl;

	// UTF-8
	auto test2 = u8"aaa�ȳ��ϼ���";
	setlocale(LC_ALL, "en_US.UTF-8");
	cout << test2 << endl;

	// WBCS
	//wchar_t ch = L"��"; // 2byte
	wstring name = L"aaa�ȳ��ϼ���"; // 2byte * N
	wcout << name << endl;
}