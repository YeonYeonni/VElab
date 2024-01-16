// dest [HelloWorld0....]
// src [World0....]
char* StrCat(char* dest, char* src)
{
	char* ret = dest;

	int len = StrLen(dest); // 0의 위치를 찾기
	int i = 0;
	while (src[i] != 0)
	{
		dest[len + i] = src[i];
		i++;
	}

	dest[len + i] = 0;

	return ret;
}