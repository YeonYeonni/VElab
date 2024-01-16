# include <iostream>
using namespace std;

// [Hello0.....]
int StrLen(const char* str)
{
	int count = 0;

	while (str[count] != '\0')
		count++;

	return count;
}

int main()
{
	const int BUF_SIZE = 100;
	char a[BUF_SIZE] = "Hello";

	int len = StrLen(a);

	cout << len << endl; // 5
}