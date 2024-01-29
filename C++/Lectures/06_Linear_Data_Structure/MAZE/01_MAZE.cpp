#include <iostream>
#include "List.h"
using namespace std;

int main()
{
	List li;
	li.AddAtTail(1);
	li.AddAtTail(2);
	li.AddAtTail(3);

	li.Print();
}