#include <iostream>
#include "myBinarySearchTree.h"
#include "myBinarySearchTree.cpp"
using namespace std;

void testBinarySearchTree()
{
	myBinarySearchTree<int> bst;
	bst.insert(2);
	bst.insert(1);
	bst.insert(3);
	bst.insert(5);
	bst.insert(0);
	/************************************************************************/
	/* �������ж������Ľṹ��
				2
			1		3
		0				5
	*/
	/************************************************************************/
	cout << "���������"; bst.pre_order_traversal1(bst.getRoot()); cout << endl;
	//cout << "���������"; bst.pre_order_traversal2(bst.getRoot()); cout << endl;
	cout << "���������"; bst.in_order_traversal1(bst.getRoot()); cout << endl;
	//cout << "���������"; bst.in_order_traversal2(bst.getRoot()); cout << endl;
	cout << "���������"; bst.post_order_traversal1(bst.getRoot()); cout << endl;
	//cout << "���������"; bst.post_order_traversal2(bst.getRoot()); cout << endl;
	cout << "��α�����"; bst.level_traversal(bst.getRoot()); cout << endl;


	cout << "value = 3�Ľڵ��Ƿ���ڣ� " << ((bst.search_for_node1(bst.getRoot(), 3) == nullptr) ? "NO" : "YES") << endl;
	cout << "�Ƴ�value = 3�Ľڵ�..." << endl;
	bst.remove_node(3);
	cout << "ǰ�������"; bst.pre_order_traversal2(bst.getRoot()); cout << endl;
	cout << "value = 3�Ľڵ��Ƿ���ڣ� " << ((bst.search_for_node1(bst.getRoot(), 3) == nullptr) ? "NO" : "YES") << endl;
}

int main()
{
	testBinarySearchTree();

	return 0;
}