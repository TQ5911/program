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


void LRtest()
{
	myAVLTree<int> tree;
	AVLTreeNode<int>* root = tree.getRoot();
	root = tree.insert(root, 31);
	/* 31 */
	root = tree.insert(root, 25);
	/* 31
	25		*/
	root = tree.insert(root, 47);
	/* 31
	25	  47*/
	root = tree.insert(root, 16);
	/*		31
		25	   47
	16			*/
	root = tree.insert(root, 17);
	/*	  		    31								31							31
		   25			    47	==>LR		25				47 ==>		17				47
	16								  17							16		25	
		17						16				 */
	cout << "先序遍历："; tree.pre_order_traversal(root); cout << endl;
	cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;

	//root = tree.insert(root, 23);
	///*				31							31						25
	//		17				47 ==>LR		25		47 ==>		17				31
	//  16		  25					17					16		23				 47
	//		   23					16		23*/	
	//cout << "先序遍历："; tree.pre_order_traversal(root); cout << endl;
	//cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;

	root = tree.insert(root, 27);
	/*				31							31						25
		 17					47 ==>LR		25		47 ==>		17				31
	16		  25						17		27			16				27		 47
				 27					16		*/
	cout << "先序遍历："; tree.pre_order_traversal(root); cout << endl;
	cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;
}

void RLtest()
{
	myAVLTree<int> tree;
	AVLTreeNode<int>* root = tree.getRoot();
	root = tree.insert(root, 31);
	/* 31 */
	root = tree.insert(root, 25);
	/* 31
	25		*/
	root = tree.insert(root, 47);
	/* 31
	25	  47*/
	root = tree.insert(root, 55);
	/*		 31
		25	      47
					  55	*/
	root = tree.insert(root, 50);
	/*		 31						 31							31
		25	      47	  ==>	25		  47	==>		25				50
					  55					  50					47		55
				    50							 55*/
	cout << "先序遍历："; tree.pre_order_traversal(root); cout << endl;
	cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;

	//root = tree.insert(root, 49);
	///*		 31					31								47
	//	25	      50	==> 25		 47				==>		31		50
	//		  47	  55				  50			25		 49		55
	//			49					   49    55	*/
	//cout << "先序遍历："; tree.pre_order_traversal(root); cout << endl;
	//cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;

	root = tree.insert(root, 45);
	/*			31						 31							  47
		25				50		==>	25		  47		==>		 31		   50
					47		55			  45	  50		25		 45		   55
				 45									  55*/
	cout << "先序遍历："; tree.pre_order_traversal(root); cout << endl;
	cout << "中序遍历："; tree.in_order_traversal(root); cout << endl;
}
int main()
{
	cout << "----------------RRtest----------------" << endl;
	RRtest();
	cout << "----------------LLtest----------------" << endl;
	LLtest();
	cout << "----------------LRtest----------------" << endl;
	LRtest();
	cout << "----------------LRtest----------------" << endl;
	RLtest();
	return 0;
}
