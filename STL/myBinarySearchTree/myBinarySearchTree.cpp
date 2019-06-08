#include <iostream>
#include <queue>
#include <stack> 
#include "myBinarySearchTree.h"
using namespace std;

template <typename T>
myBinarySearchTree<T>::myBinarySearchTree()
{
	root = nullptr;
}

template <typename T>
myBinarySearchTree<T>::~myBinarySearchTree()
{
	deleteSubtree(root);
	root = nullptr;
}

template <typename T>
myBinNode<T>* myBinarySearchTree<T>::getRoot()
{
	return root;
}

template <typename T>
void myBinarySearchTree<T>::insert(const T& value)
{
	if (root == nullptr)// 插入的第一个节点为根结点
	{
		root = new myBinNode<T>();
		root->data = value;
	}
	else
	{
		myBinNode<T>* recNode = root;
		while (recNode != nullptr)// 判断新节点 插入的(父节点)位置
		{
			if (recNode->data >= value)// 入左子树
			{
				if (recNode->left == nullptr) break;// 存在
				recNode = recNode->left;			// 下一层
			}
			if (recNode->data < value)// 入右左子树
			{
				if (recNode->right == nullptr) break;
				recNode = recNode->right;
			}
		}
		myBinNode<T>* newNode = new myBinNode<T>();
		newNode->data = value;
		if (recNode->data >= value)	// 相等的插入左孩子节点
			recNode->left = newNode;
		else
			recNode->right = newNode;
	}
	return;
}

template <typename T>
void myBinarySearchTree<T>::remove_node(const T& value)
{
	myBinNode<T>* sub_root = root;
	myBinNode<T>* parentNode = root;
	bool isLeft = true;// 待删除节点在父节点的左或右孩子节点上
	if (sub_root == nullptr || sub_root->data == value) return;
	while (sub_root != nullptr && sub_root->data != value)
	{
		parentNode = sub_root;
		if (sub_root->data > value)
		{
			sub_root = sub_root->left;
			isLeft = true;
		}
		else if (sub_root->data < value)
		{
			sub_root = sub_root->right;
			isLeft = false;
		}
	}
	if (sub_root == nullptr)	// 没找到
		cout << "No target!" << endl;
	else if (sub_root->left == nullptr)// 不存在左子树，父节点直接连到当前节点的右孩子节点
	{
		myBinNode<T>* del = sub_root;
		sub_root = sub_root->right;
		delete del;
	}
	else if (sub_root->right == nullptr)// 不存在右子树，父节点直接连到当前节点的左孩子节点
	{
		myBinNode<T>* del = sub_root;
		sub_root = sub_root->left;
		delete del;
	}
	else// 左右子树都存在
	{
		myBinNode<T>* parent = sub_root;		// 替代节点的父节点
		myBinNode<T>* preNode = sub_root->left; // 找到待删除节点的替代节点(即左子树里最大的那个节点)
		while (preNode->right != nullptr)
		{
			parent = preNode;
			preNode = preNode->right;
		}
		sub_root->data = preNode->data;	// 替换掉带待删除的节点内容 为 最大节点的
		if (parent == sub_root)			// 连接最大节点的子树
			sub_root->left = preNode->left;
		else 
			parent->right = preNode->left;
		delete preNode;// 替换完后删除最大的节点
		return;
	}
	if (isLeft)
		parentNode->left = sub_root;
	else 
		parentNode->right = sub_root;
}

template <typename T>
void myBinarySearchTree<T>::pre_order_traversal1(myBinNode<T>* node)
{
	if (node == nullptr) return;
	cout << node->data << " ";
	if (node->left != nullptr)
		pre_order_traversal1(node->left);
	if (node->right != nullptr)
		pre_order_traversal1(node->right);
}

template <typename T>
void myBinarySearchTree<T>::pre_order_traversal2(myBinNode<T>* node)
{
	if (node == nullptr) return;
	myBinNode<T>* curNode = node;
	stack<myBinNode<T>*> s;
	while (curNode != nullptr || !s.empty())
	{
		while (curNode != nullptr)
		{
			cout << curNode->data << " ";
			s.push(curNode);
			curNode = curNode->left;
		}
		curNode = s.top();
		s.pop();
		curNode = curNode->right;
	}
}

template <typename T>
void myBinarySearchTree<T>::in_order_traversal1(myBinNode<T>* node)
{
	if (node == nullptr) return;
	if (node->left != nullptr)
		in_order_traversal1(node->left);
	cout << node->data << " ";
	if (node->right != nullptr)
		in_order_traversal1(node->right);
}

template <typename T>
void myBinarySearchTree<T>::in_order_traversal2(myBinNode<T>* node)
{
	if (node == nullptr) return;
	myBinNode<T>* curNode = node;
	stack<myBinNode<T>*> s;
	while (curNode != nullptr || !s.empty())
	{
		while (curNode != nullptr)
		{
			s.push(curNode);
			curNode = curNode->left;
		}
		curNode = s.top();
		s.pop();
		cout << curNode->data << " ";
		curNode = curNode->right;
	}
}

template <typename T>
void myBinarySearchTree<T>::post_order_traversal1(myBinNode<T>* node)
{
	if (node == nullptr) return;
	if (node->left != nullptr)
		post_order_traversal1(node->left);
	if (node->right != nullptr)
		post_order_traversal1(node->right);
	cout << node->data << " ";
}

template <typename T>
void myBinarySearchTree<T>::post_order_traversal2(myBinNode<T>* node)
{
	if (node == nullptr) return;
	myBinNode<T>* curNode = node;
	myBinNode<T>* preNode = nullptr;
	stack<myBinNode<T>*> s;
	s.push(curNode);
	while (!s.empty())
	{
		curNode = s.top();
		// visit a leaf node or all the children nodes have been visited
		if (curNode->left == nullptr && curNode->right == nullptr
			|| preNode != nullptr && (preNode == curNode->left || preNode == curNode->right))
		{
			cout << curNode->data << " ";
			s.pop();
			preNode = curNode;
		}
		else
		{
			if (curNode->right != nullptr)
			{
				s.push(curNode->right);
			}
			if (curNode->left != nullptr)
			{
				s.push(curNode->left);
			}
		}
	}
}
// level traversal: non recursive realization
template <typename T>
void myBinarySearchTree<T>::level_traversal(myBinNode<T>* node)
{
	if (node == nullptr) return;
	myBinNode<T>* curNode = node;
	queue<myBinNode<T>*> q;
	if (curNode != nullptr) q.push(curNode);
	while (!q.empty())
	{
		curNode = q.front();
		q.pop();
		cout << curNode->data << " ";
		if (curNode->left != nullptr) q.push(curNode->left);
		if (curNode->right != nullptr) q.push(curNode->right);
	}
}

// search a target node: recursive realization
template <typename T>
myBinNode<T>* myBinarySearchTree<T>::search_for_node1(myBinNode<T>* sub_root, const T&  target)
{
	if (sub_root == nullptr || sub_root->data == target) return sub_root;
	if (sub_root->data > target) return search_for_node1(sub_root->left, target);
	if (sub_root->data < target) return search_for_node1(sub_root->right, target);
}
// search a target node: non recursive realization 
template <typename T>
myBinNode<T>* myBinarySearchTree<T>::search_for_node2(myBinNode<T>* sub_root, const T&  target)
{
	while (sub_root != nullptr && sub_root->data != target)
	{
		if (sub_root->data > target)
			sub_root = sub_root->left;
		else if (sub_root->data < target)
			sub_root = sub_root->right;
	}
	return sub_root;
}

// delete a subtree whose root is node
template <typename T>
void myBinarySearchTree<T>::deleteSubtree(myBinNode<T> *node)
{
	if (node != nullptr && node->left != nullptr)
		deleteSubtree(node->left);

	if (node != nullptr && node->right != nullptr)
		deleteSubtree(node->right);

	delete node;
	node = nullptr;
}
