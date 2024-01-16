// dest [HelloWorld0....]
// src [World0....]
char* StrCat(char* dest, char* src)
{
	char* ret = dest;

	while (*dest != 0)
		dest++;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	return ret;
}