#include <iostream>
#include "myAVLTree.h"
#include "myAVLTree.cpp"
using namespace std;

void RRtest()
{
	myAVLTree<int> tree;
	AVLTreeNode<int>* root = tree.getRoot();
	root = tree.insert(root, 1);
	/* 1 */
	root = tree.insert(root, 2);
	/*	1
			2*/
	root = tree.insert(root, 3);
	/*	1						2	
			2			==>	1		3			RR
				3									*/
	root = tree.insert(root, 4);
	/*	2
	1		3
				4									*/
	root = tree.insert(root, 5);
	/*	2						2
	1		3			==> 1		4			RR
				4				  3   5	
					5								*/
	root = tree.insert(root, 6);
	/*	2							4
	1		4			==>		2		5		RR
		  3   5				  1   3			6
				6									*/
	cout << "前序遍历："; tree.pre_order_traversal(root); cout << endl;
	cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;

}

void LLtest()
{
	myAVLTree<int> tree;
	AVLTreeNode<int>* root = tree.getRoot();
	root = tree.insert(root, 6);
	/* 6 */
	root = tree.insert(root, 5);
	/*	6
	5		*/
	root = tree.insert(root, 4);
	/*		6					5
		5				==>	4		6				LL
	4													*/
	root = tree.insert(root, 3);
	/*		5
		4		6
	3													*/
	root = tree.insert(root, 2);
	/*			5						5
			4		6	==>			3		6		LL
		3						  2	  4		
	2													*/
	root = tree.insert(root, 1);
	/*		5							3	
		3		6			==>		2		5		LL
	  2   4						  1 	  4	  6
	1													*/
	cout << "先序遍历："; tree.pre_order_traversal(root); cout << endl;
	cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;

}
int main(){
	cout << "----------------RRtest----------------" << endl;
	RRtest();
	cout << "----------------LLtest----------------" << endl;
	LLtest();
	return 0;
}
