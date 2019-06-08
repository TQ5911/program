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
	/* �������ж������Ľṹ��
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
	// �������01364257
	cout << "--------------�������--------------" << endl;
	tree->travPre_R(tree->getRoot(), printfFunc);
	cout << endl;
	tree->travPre_I(tree->getRoot(), pfun);
	cout << endl;

	// �������63140275
	cout << "--------------�������--------------" << endl;
	tree->travIn_R(tree->getRoot(), printfFunc);
	cout << endl;
	tree->travIn_I(tree->getRoot(), pfun);
	cout << endl;

	// �������63417520
	cout << "--------------�������--------------" << endl;
	tree->travPost_R(tree->getRoot(), printfFunc);
	cout << endl;
	tree->travPost_I(tree->getRoot(), pfun);
	cout << endl;

	// ��α���01234567
	cout << "--------------��α���--------------" << endl;
	tree->travLevel(tree->getRoot(), printfFunc);

	getchar();
	return 0;
}