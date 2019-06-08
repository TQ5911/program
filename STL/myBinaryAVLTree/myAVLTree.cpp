#include <iostream>
#include <algorithm>
#include "myAVLTree.h"
using namespace std;

template <typename T>
myAVLTree<T>::myAVLTree()
{
	root = nullptr;
}

template <typename T>
myAVLTree<T>::~myAVLTree()
{
	deleteSubtree(root);
	root = nullptr;
}

template <typename T>
AVLTreeNode<T>* myAVLTree<T>::getRoot()
{
	return root;
}

template <typename T>
int myAVLTree<T>::getHeight(AVLTreeNode<T>* node)
{
	return (nullptr == node) ? -1 : node->height;
}

template <typename T>
void myAVLTree<T>::setHeight(AVLTreeNode<T>* subroot, const T& subtreeHeight)
{
	subroot->height = subtreeHeight;
}

template <typename T>
AVLTreeNode<T>* myAVLTree<T>::SingleRightRotate(AVLTreeNode<T>* subroot)
{
	AVLTreeNode<T>* originRoot = subroot;
	AVLTreeNode<T>* newRoot = subroot->left;
	originRoot->left = newRoot->right;
	newRoot->right = originRoot;
	
	//更新子树的高度
	originRoot->height = max(getHeight(originRoot->left), getHeight(originRoot->right)) + 1;
	newRoot->height =  max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
	
	return newRoot;
}

template <typename T>
AVLTreeNode<T>* myAVLTree<T>::DoubleRightRotate(AVLTreeNode<T>* subroot)
{
	// 使用两次单次旋转实现双右旋转
	subroot->left = SingleLeftRotate(subroot->left);
	return SingleRightRotate(subroot);
}

template <typename T>
AVLTreeNode<T>* myAVLTree<T>::SingleLeftRotate(AVLTreeNode<T>* subroot)
{
	AVLTreeNode<T>* originRoot = subroot;
	AVLTreeNode<T>* newRoot = subroot->right;
	originRoot->right = newRoot->left;
	newRoot->left = originRoot;
	
	// 更新子树的高度
	originRoot->height = max(getHeight(originRoot->left), getHeight(originRoot->right)) + 1;
	newRoot->height =  max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
	
	return newRoot;	
}

template <typename T>
AVLTreeNode<T>* myAVLTree<T>::DoubleLeftRotate(AVLTreeNode<T>* subroot)
{
	subroot->right = SingleRightRotate(subroot->right);
	return SingleLeftRotate(subroot);
}

template <typename T>
AVLTreeNode<T>* myAVLTree<T>::insert(AVLTreeNode<T>* subroot, const T& value)
{
	if (nullptr == subroot)// 创建根节点
	{
		AVLTreeNode<T>* newNode = new AVLTreeNode<T>(value);
		if (nullptr == root) root = newNode;
		return newNode;
	}
	else
	{
		if (subroot->data >= value)
		{
			// 将节点插入左子树
			subroot->left = insert(subroot->left, value);
			// 检查子树是否仍然是avl tree
			if (getHeight(subroot->left) - getHeight(subroot->right) > 1){
				// LL：插入左子树的左子节点
				if (value < subroot->left->data)
					subroot = SingleRightRotate(subroot);
				// LR：插入左子树的右子节点
				if (value > subroot->left->data)
					subroot = DoubleRightRotate(subroot);
			}
		}
		if (subroot->data < value)
		{
			// 将节点插入右子树
			subroot->right = insert(subroot->right, value);
			// 检查子树是否仍然是avl tree
			if (getHeight(subroot->right) - getHeight(subroot->left) > 1)
			{
				// RR：插入左子树的左子节点
				if (value > subroot->right->data)
					subroot = SingleLeftRotate(subroot);
				// RL：插入左子树的右子节点
				if (value < subroot->right->data)
					subroot = DoubleLeftRotate(subroot);
			}
		}
		setHeight(subroot, max(getHeight(subroot->left), getHeight(subroot->right)) + 1);
		return subroot;
	}
}

template <typename T>
void myAVLTree<T>::pre_order_traversal(AVLTreeNode<T>* node)
{
	if (node == nullptr) return;
	cout << node->data << " ";
	if (node->left != nullptr)
		pre_order_traversal(node->left);
	if (node->right != nullptr)
		pre_order_traversal(node->right);
}

template <typename T>
void myAVLTree<T>::in_order_traversal(AVLTreeNode<T>* node)
{
	if (node == nullptr) return;
	if (node->left != nullptr)
		in_order_traversal(node->left);
	cout << node->data << " ";
	if (node->right != nullptr)
		in_order_traversal(node->right);
}

template <typename T>
AVLTreeNode<T>* myAVLTree<T>::search_for_node(AVLTreeNode<T>* sub_root, const T& target)
{
	if (sub_root == nullptr || sub_root->data == target) return sub_root;
	while (sub_root != nullptr && sub_root->data != target){
		if (sub_root->data > target)
			sub_root = sub_root->left;
		else if (sub_root->data < target)
			sub_root = sub_root->right;
	}
	return sub_root;
}

template <typename T>
void myAVLTree<T>::deleteSubtree(AVLTreeNode<T> *node)
{
	if (node->left != nullptr)
		deleteSubtree(node->left);
	if (node->right != nullptr)
		deleteSubtree(node->right);

	delete node;
	node = nullptr;
}
