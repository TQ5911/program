#include "myBinTree.h"
#include "myBinTree.cpp"
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


	myBinTree<int>* tree = new myBinTree<int>();
	tree->insertAsRoot(0);
	myBinNode<int>* node1 = tree->insertAsLChild(tree->getRoot(), 1);
	myBinNode<int>* node4 = tree->insertAsRChild(node1, 4);
	myBinNode<int>* node3 = tree->insertAsLChild(node1, 3);
	myBinNode<int>* node6 = tree->insertAsLChild(node3, 6);

	myBinNode<int>* node2 = tree->insertAsRChild(tree->getRoot(), 2);
	myBinNode<int>* node5 = tree->insertAsRChild(node2, 5);
	myBinNode<int>* node7 = tree->insertAsLChild(node5, 7);

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

	getchar();
	return 0;
}