#include <iostream>
using namespace std;
int main()
{
	// malloc
	void* ptr = malloc(monsters);

	// free
	free(ptr);
}
