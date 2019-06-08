#include "stdafx.h"
#include "BTree.h"
int main()
{
	myBtree<int> tree;
	tree.bTreeInsert(1);
	tree.bTreeInsert(2);
	tree.bTreeInsert(3);
	tree.bTreeInsert(4);
	tree.bTreeInsert(5);
	tree.bTreeInsert(6);
	tree.bTreeInsert(7);
	tree.bTreeInsert(8);
	tree.bTreeInsert(9);
	tree.bTreeInsert(10);
	std::cout << "build tree(1~10): " << std::endl;
	tree.printTree(tree.getRoot());
	std::cout << "delete key 2(test case 2): " << std::endl;
	tree.bTreeDelete(2);
	tree.printTree(tree.getRoot());
	std::cout << "delete key 4(test case 3): " << std::endl;
	tree.bTreeDelete(4);
	tree.printTree(tree.getRoot());
	std::cout << "delete key 10(test case 1): " << std::endl;
	tree.bTreeDelete(10);
	tree.printTree(tree.getRoot());
	
	return 0;
} 
