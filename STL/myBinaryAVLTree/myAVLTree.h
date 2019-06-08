#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#pragma once

template <typename T>
struct AVLTreeNode
{
	AVLTreeNode(const T& tmpdata = NULL) :data(tmpdata), height(0), left(nullptr), right(nullptr){}
	T data;
	int height;
	AVLTreeNode<T>* left;
	AVLTreeNode<T>* right;
};

// 二叉平衡树
template <typename T>
class myAVLTree
{
protected:
	AVLTreeNode<T>* root;
public:
	myAVLTree();	// 构造函数
	~myAVLTree();	// 析构函数

	AVLTreeNode<T>* getRoot();			// 得到根节点
	int getHeight(AVLTreeNode<T>* node);// 获取子树的高度
	void setHeight(AVLTreeNode<T>* subroot, const T& subtreeHeight);	// 设置子树的高度

	AVLTreeNode<T>* SingleRightRotate(AVLTreeNode<T>* subroot);			// 对于LL，使用单右旋转
	AVLTreeNode<T>* DoubleRightRotate(AVLTreeNode<T>* subroot);			// 对于LR, 使用双右旋转
	AVLTreeNode<T>* SingleLeftRotate(AVLTreeNode<T>* subroot);			// 对于RR，使用单左旋转
	AVLTreeNode<T>* DoubleLeftRotate(AVLTreeNode<T>* subroot);			// 对于RL，请使用双左旋转

	AVLTreeNode<T>* insert(AVLTreeNode<T>* subroot, const T& value);	// 创建或插入节点
	void pre_order_traversal(AVLTreeNode<T>* node);		// 先序: 递归实现
	void in_order_traversal(AVLTreeNode<T>* node);		// 中序: 递归实现
	AVLTreeNode<T>* search_for_node(AVLTreeNode<T>* sub_root, const T& target);// 搜索目标节点：非递归实现
protected:
	void deleteSubtree(AVLTreeNode<T>* node);// 删除根为节点的子树
};
#endif