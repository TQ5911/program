/************************************************************************/
/* 类模板的定义和实现分在两个函数里，在编译阶段就不通过
解决1：把定义和实现都放到头文件里
解决2：在实现的调用函数文件开头加上#include "binTree.cpp"
*/
/************************************************************************/

#include "binTree.h"
#include <iostream>

using namespace  std;
/*
func 为打印节点数据的函数
*/

// 构造函数
template<typename T>
binTree<T>::binTree() :m_size(0), m_pRoot(nullptr){}

//析构函数
template<typename T>
binTree<T>::~binTree()
{
	if (m_size)
		remove(m_pRoot);
}

// 返回二叉树的规模
template<typename T>
int binTree<T>::size()
{
	return m_size;
}

// 判断二叉树是否为空
template<typename T>
bool binTree<T>::empty()
{
	return m_pRoot ? true : false;
}

// 返回根节点的指针
template<typename T>
binNode<T>* binTree<T>::getRoot()
{
	return m_pRoot;
}

// 将指定元素插入作为根节点
template<typename T>
binNode<T>* binTree<T>::insertAsRoot(const T& e)
{
	if (m_pRoot)
		return nullptr;
	m_size = 1;
	return m_pRoot = new binNode<T>(e);
}

// 将指定元素插入作为指定节点的左孩子
template<typename T>
binNode<T>* binTree<T>::insertAsLChild(binNode<T>* bn, const T& e)
{
	if (bn->lchild)		//若左孩子已经存在则返回
		return nullptr;
	bn->lchild = bn->insertAsLChild(e);
	//bn->lchild = new binNode<T>(e, bn);
	++m_size;
	updateHeightAbove(bn->lchild);
	return bn->lchild;
}

// 将指定元素插入作为指定节点的左孩子
template<typename T>
binNode<T>* binTree<T>::insertAsRChild(binNode<T>* bn, const T& e)
{
	if (bn->rchild)
		return nullptr;
	bn->rchild = bn->insertAsRChild(e);
	//bn->rchild = new binNode<T>(e, bn);
	++m_size;
	updateHeightAbove(bn->rchild);
	return bn->rchild;
}

// 将指定子树插入作为指定节点的左孩子
template<typename T>
binNode<T>* binTree<T>::attachAsLChild(binNode<T>* bn, binTree<T>* &bt)
{
	if (bn->lchild)
		return nullptr;
	bn->lchild = bt->getRoot();
	bt->getRoot()->parent = bn;
	updateHeightAbove(bn->lchild);
	m_size += bt->size();

	// 释放bt
	bt->m_pRoot = nullptr;
	bt->m_size = 0;
	bt = nullptr;
	return bn->lchild;
}

// 将指定子树插入作为指定节点的右孩子
template<typename T>
binNode<T>* binTree<T>::attachAsRChild(binNode<T>* bn, binTree<T>* &bt)
{
	if (bn->rchild)
		return nullptr;
	bn->rchild = bt->getRoot();
	bt->getRoot()->parent = bn;
	updateHeightAbove(bn->rchild);
	m_size += bt->size();

	// 释放bt
	bt->m_pRoot = nullptr;
	bt->m_size = 0;
	bt = nullptr;
	return bn->lchild;
}

// 更新节点的高度
template<typename T>
int binTree<T>::updateHeight(binNode<T>* bn)
{
	return bn->height = (1 + Max(stature(bn->lchild), stature(bn->rchild)));
}

// 更新此节点祖先节点的高度(插入或删除节点要执行更新)
template<typename T>
void binTree<T>::updateHeightAbove(binNode<T>* bn)
{
	while (bn)
	{
		updateHeight(bn);
		bn = bn->parent;
	}
}

// 删除节点bn及其后代，并返回删掉的二叉树节点的总数
template<typename T>
int binTree<T>::removeAt(binNode<T>* bn)
{
	int n = 0;
	if (bn == nullptr)
		return 0;
	n = 1 + removeAt(bn->lchild) + removeAt(bn->rchild);
	delete bn;
	return n;
}

// 删除以bn为根节点的子树
template<typename T>
int binTree<T>::remove(binNode<T>* bn)
{
	if (bn != m_pRoot)
	{
		((bn->parent->lchild) == bn) ? (bn->parent->lchild) == nullptr : (bn->parent->rchild) == nullptr;// 将父节点对应左\右孩子置空
	}
	binNode<T>* bp = bn->parent;
	int n = removeAt(bn);
	updateHeightAbove(bp);
	m_size -= n;
	return n;
}

// 子树分离，将节点bn及其后代从二叉树中分离出来，然后形成一个独立的二叉树
template<typename T>
binTree<T>* binTree<T>::secede(binNode<T>* bn)
{
	if (bn != m_pRoot)
	{
		((bn->parent->lchild) == bn) ? (bn->parent->lchild) = nullptr : (bn->parent->rchild) = nullptr;
	}
	// 更新height
	binNode<T>* bp = bn->parent;
	updateHeightAbove(bp);

	// 封装成新二叉树
	binTree<T>* bt = new binTree<T>();
	bt->m_pRoot = bn;
	bn->parent = nullptr;
	// 更新size
	bt->m_size = bn->size();
	m_size -= bt->m_size;

	// 特殊情况处理
	if (m_pRoot == bn)
		m_pRoot = nullptr;
	return bt;
}

// 先序遍历(递归版本:简洁易懂)
template<typename T>
void binTree<T>::travPre_R(binNode<T>* bn_r, void(*func)(T& bn))
{
	if (!bn_r) return;
	func(bn_r->data);
	travPre_R(bn_r->lchild, func);
	travPre_R(bn_r->rchild, func);
}

// 中序遍历(递归版本:简洁易懂)
template<typename T>
void binTree<T>::travIn_R(binNode<T>* bn_r, void(*func)(T& bn))
{
	if (!bn_r) return;
	travIn_R(bn_r->lchild, func);
	func(bn_r->data);
	travIn_R(bn_r->rchild, func);
}

// 后序遍历(递归版本:简洁易懂)        
template<typename T>
void binTree<T>::travPost_R(binNode<T>* bn_r, void(*func)(T& bn))
{
	if (!bn_r) return;
	travPost_R(bn_r->lchild, func);
	travPost_R(bn_r->rchild, func);
	func(bn_r->data);
}

// 沿着左轮廓线遍历
template<typename T>
void binTree<T>::visitAlongLeftBranch(binNode<T>* bn, void(*func)(T& bn), stack<binNode<T>*> &s)
{
	while (bn)
	{
		func(bn->data);
		s.push(bn->rchild);		// 右孩子入栈
		bn = bn->lchild;		// 沿着左边沿遍历
	}
}

// 先序遍历(迭代版本:时间、空间复杂度低)
template<typename T>
void binTree<T>::travPre_I(binNode<T>* bn_i, void(*func)(T& bn))
{
	stack<binNode<T>*> s;
	while (true)
	{
		visitAlongLeftBranch(bn_i, func, s);	// 遍历且入栈
		if (s.empty()) break;
		bn_i = s.top();
		s.pop();
	}
}

// 从当前节点开始，沿着左分支深入入栈
template<typename T>
void binTree<T>::goAlongLeftBranch(binNode<T>* bn, stack<binNode<T>*> &s)
{
	while (bn)
	{
		s.push(bn);
		bn = bn->lchild;
	}
}

// 中序遍历(迭代版本:时间、空间复杂度低)
template<typename T>
void binTree<T>::travIn_I(binNode<T>* bn_i, void(*func)(T& bn))
{
	stack<binNode<T>*> s;
	while (true)
	{
		goAlongLeftBranch(bn_i, s);
		if (s.empty()) break;
		bn_i = s.top();
		s.pop();
		func(bn_i->data);
		bn_i = bn_i->rchild;
	}
}

// 在以s栈顶节点为根的子树中，找到最高左侧可见节点
template<typename T>
void binTree<T>::gotoHLVFL(stack<binNode<T>*> &s)
{
	while (binNode<T>* bn_i = s.top())
	{
		if (bn_i->lchild)
		{
			if (bn_i->rchild)
				s.push(bn_i->rchild);
			s.push(bn_i->lchild);
		}
		else// if (bn_i->rchild) 不能判断，不然存在跳不出这个while语句
		{
			s.push(bn_i->rchild);
		}
	}
	s.pop();// 移除空指针
}

// 后序遍历(迭代版本:时间、空间复杂度低)
template<typename T>
void binTree<T>::travPost_I(binNode<T>* bn_i, void(*func)(T& bn))
{
	stack<binNode<T>*> s;
	if (bn_i)
		s.push(bn_i);
	while (!s.empty())
	{
		if (s.top() != bn_i->parent)// 防止再次遍历左右节点
			gotoHLVFL(s);
		bn_i = s.top();
		s.pop();
		func(bn_i->data);
	}
}

// 层次遍历
template<typename T>
void binTree<T>::travLevel(binNode<T>* bn_i, void(*func)(T& bn))
{
	queue<binNode<T>*> q;
	if (bn_i)
		q.push(bn_i);
	while (!q.empty())  // 队列非空
	{
		bn_i = q.front();
		q.pop();
		func(bn_i->data);
		if (bn_i->lchild)
			q.push(bn_i->lchild);
		if (bn_i->rchild)
			q.push(bn_i->rchild);
	}
}

