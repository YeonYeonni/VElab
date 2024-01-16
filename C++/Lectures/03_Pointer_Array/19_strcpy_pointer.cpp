char* StrCpy(char* dest, char* src)
{
	char* ret = dest;

	while (*src != 0)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = 0;

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