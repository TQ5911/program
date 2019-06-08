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
	/* 本案例中二叉树的结构体
				2
			1		3
		0				5
	*/
	/************************************************************************/
	cout << "先序遍历："; bst.pre_order_traversal1(bst.getRoot()); cout << endl;
	//cout << "先序遍历："; bst.pre_order_traversal2(bst.getRoot()); cout << endl;
	cout << "中序遍历："; bst.in_order_traversal1(bst.getRoot()); cout << endl;
	//cout << "中序遍历："; bst.in_order_traversal2(bst.getRoot()); cout << endl;
	cout << "后序遍历："; bst.post_order_traversal1(bst.getRoot()); cout << endl;
	//cout << "后序遍历："; bst.post_order_traversal2(bst.getRoot()); cout << endl;
	cout << "层次遍历："; bst.level_traversal(bst.getRoot()); cout << endl;


	cout << "value = 3的节点是否存在？ " << ((bst.search_for_node1(bst.getRoot(), 3) == nullptr) ? "NO" : "YES") << endl;
	cout << "移除value = 3的节点..." << endl;
	bst.remove_node(3);
	cout << "前序遍历："; bst.pre_order_traversal2(bst.getRoot()); cout << endl;
	cout << "value = 3的节点是否存在？ " << ((bst.search_for_node1(bst.getRoot(), 3) == nullptr) ? "NO" : "YES") << endl;
}

int main()
{
	testBinarySearchTree();

	return 0;
}