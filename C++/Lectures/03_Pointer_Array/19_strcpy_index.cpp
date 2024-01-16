char* StrCpy(char* dest, char* src)
{
	char* ret = dest;

	// src가 0이 아닐 때까지 복사
	int i = 0;
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = 0; // 마지막에 0

	return ret;
}

int main()
{
	const int BUF_SIZE = 100;
	char a[BUF_SIZE] = "Hello";
	char b[BUF_SIZE];

	StrCpy(b, a);

	cout << b << endl;
}