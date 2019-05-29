#ifndef _MYBINARYSEARCHTREE_H_
#define _MYBINARYSEARCHTREE_H_
#pragma  once

// 自定义节点
template <typename T>
struct myBinNode
{
	myBinNode() :data(NULL), left(nullptr), right(nullptr){}
	T data;
	myBinNode<T>* left;
	myBinNode<T>* right;
};

// 二叉搜索树
template <typename T>
class myBinarySearchTree
{
protected:
	myBinNode<T> *root;	// 根结点
public:
	// 构造
	myBinarySearchTree();
	// 析构
	~myBinarySearchTree();

	myBinNode<T>* getRoot();			// 得到根结点
	void insert(const T& value);		// 插入节点
	void remove_node(const T& value);	// 删除节点

	// 遍历
	void pre_order_traversal1(myBinNode<T>* node);	// 先序遍历(递归实现)
	void pre_order_traversal2(myBinNode<T>* node);	// 先序遍历(迭代实现)
	void in_order_traversal1(myBinNode<T>* node);	// 中序遍历(递归实现)
	void in_order_traversal2(myBinNode<T>* node);	// 中序遍历(迭代实现)
	void post_order_traversal1(myBinNode<T>* node);	// 后续遍历(递归实现)
	void post_order_traversal2(myBinNode<T>* node);	// 中序遍历(迭代实现)
	void level_traversal(myBinNode<T>* node);		// 层次遍历

	myBinNode<T>* search_for_node1(myBinNode<T>* sub_root, const T&  target); // 搜索目标节点(递归实现)
	myBinNode<T>* search_for_node2(myBinNode<T>* sub_root, const T&  target); // 搜索目标节点(迭代实现)

protected:
	void deleteSubtree(myBinNode<T> *node);	// 删除根为节点的子树
};


#endif