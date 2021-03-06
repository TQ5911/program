#ifndef _BINTREE_H_
#define _BINTREE_H_
#pragma once

#include "myBinNode.h"
#include <stack>
#include <queue>
using namespace std;
#define  Max(a,b) (((a)>=(b))?(a):(b))


template<typename T>
class myBinTree
{
protected:
	// 成员变量
	int m_size;				// 二叉树的规模
	myBinNode<T>* m_pRoot;	// 树的根节点指针
public:
	// 构造函数
	myBinTree();
	// 析构函数
	~myBinTree();
	// 成员函数
	int size();		// 返回二叉树的规模
	bool empty();	// 判断二叉树是否为空
	myBinNode<T>* getRoot();	// 返回根节点的指针
	myBinNode<T>* insertAsRoot(const T& e);	// 将指定元素插入作为根节点
	myBinNode<T>* insertAsLChild(myBinNode<T>* bn, const T& e);		// 将指定元素插入作为指定节点的左孩子
	myBinNode<T>* insertAsRChild(myBinNode<T>* bn, const T& e);		// 将指定元素插入作为指定节点的左孩子
	myBinNode<T>* attachAsLChild(myBinNode<T>* bn, myBinTree<T>* &bt);	// 将指定子树插入作为指定节点的左孩子
	myBinNode<T>* attachAsRChild(myBinNode<T>* bn, myBinTree<T>* &bt);	// 将指定子树插入作为指定节点的右孩子
	int updateHeight(myBinNode<T>* bn);			// 更新节点的高度
	void updateHeightAbove(myBinNode<T>* bn);		// 更新此节点祖先节点的高度(插入或删除节点要执行更新)
	int removeAt(myBinNode<T>* bn);       // 删除节点bn及其后代，并返回删掉的二叉树节点的总数
	int remove(myBinNode<T>* bn);			// 删除以bn为根节点的子树
	myBinTree<T>* secede(myBinNode<T>* bn);			// 子树分离，将节点bn及其后代从二叉树中分离出来，然后形成一个独立的二叉树

	void travPre_R(myBinNode<T>* bn_r, void(*func)(T& bn));		// 先序遍历(递归版本:简洁易懂)
	void travIn_R(myBinNode<T>* bn_r, void(*func)(T& bn));		// 中序遍历(递归版本:简洁易懂)
	void travPost_R(myBinNode<T>* bn_r, void(*func)(T& bn));		// 后序遍历(递归版本:简洁易懂)

	void visitAlongLeftBranch(myBinNode<T>* bn, void(*func)(T& bn), stack<myBinNode<T>*> &s);  // 沿着左轮廓线遍历
	void travPre_I(myBinNode<T>* bn_i, void(*func)(T& bn));			// 先序遍历(迭代版本:时间、空间复杂度低)
	void goAlongLeftBranch(myBinNode<T>* bn, stack<myBinNode<T>*> &s);	// 从当前节点开始，沿着左分支深入入栈
	void travIn_I(myBinNode<T>* bn_i, void(*func)(T& bn));			// 中序遍历(迭代版本:时间、空间复杂度低)
	void gotoHLVFL(stack<myBinNode<T>*> &s);							// 在以s栈顶节点为根的子树中，找到最高左侧可见节点
	void travPost_I(myBinNode<T>* bn_i, void(*func)(T& bn));			// 后序遍历(迭代版本:时间、空间复杂度低)
	void travLevel(myBinNode<T>* bn_i, void(*func)(T& bn));			// 层次遍历
};
#endif // !_BINTREE_H_


