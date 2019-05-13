#include "binTree.h"
#include "binTree.cpp"
#include <iostream>

template<typename T>
void printfFunc(T& data)
{
	cout << data << " ";
}
typedef void(*pFun)(int& data);


int main()
{
	/************************************************************************/
	/* 本案例中二叉树的结构体
					0
			1				2
		3		4				5
	6						7
	*/
	/************************************************************************/


	binTree<int>* tree = new binTree<int>();
	tree->insertAsRoot(0);
	binNode<int>* node1 = tree->insertAsLChild(tree->getRoot(), 1);
	binNode<int>* node4 = tree->insertAsRChild(node1, 4);
	binNode<int>* node3 = tree->insertAsLChild(node1, 3);
	binNode<int>* node6 = tree->insertAsLChild(node3, 6);

	binNode<int>* node2 = tree->insertAsRChild(tree->getRoot(), 2);
	binNode<int>* node5 = tree->insertAsRChild(node2, 5);
	binNode<int>* node7 = tree->insertAsLChild(node5, 7);

	pFun pfun = printfFunc;
	// 先序遍历01364257
	cout << "--------------先序遍历--------------" << endl;
	tree->travPre_R(tree->getRoot(), printfFunc);
	cout << endl;
	tree->travPre_I(tree->getRoot(), pfun);
	cout << endl;

	// 中序遍历63140275
	cout << "--------------中序遍历--------------" << endl;
	tree->travIn_R(tree->getRoot(), printfFunc);
	cout << endl;
	tree->travIn_I(tree->getRoot(), pfun);
	cout << endl;

	// 后序遍历63417520
	cout << "--------------后序遍历--------------" << endl;
	tree->travPost_R(tree->getRoot(), printfFunc);
	cout << endl;
	tree->travPost_I(tree->getRoot(), pfun);
	cout << endl;

	// 层次遍历01234567
	cout << "--------------层次遍历--------------" << endl;
	tree->travLevel(tree->getRoot(), printfFunc);
	cout << endl;


	binTree<int>* tree1 = new binTree<int>();
	tree1->insertAsRoot(123);
	tree1->attachAsLChild(tree1->getRoot(), tree);

	getchar();
	return 0;
}