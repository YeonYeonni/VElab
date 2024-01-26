#include <iostream>
using namespace std;
#include <vector>
#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree bst;

	bst.Insert(20);
	bst.Insert(30);
	bst.Insert(10);

	bst.Insert(25);
	bst.Insert(26);
	bst.Insert(40);
	bst.Insert(50);

	bst.Delete(26);

	bst.Print();
}