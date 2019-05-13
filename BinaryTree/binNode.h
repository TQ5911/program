#ifndef _BINODE_H_
#define _BINODE_H_

#pragma once
#define stature(p)	((p)?(p)->height:-1)
#define NULL 0

template<typename T> 
struct binNode
{
	// 成员变量
	T data;
	binNode<T> *parent, *lchild, *rchild;	// 指向父类，左孩子右孩子的指针
	int height;								// 高度


	//构造函数
	binNode() :data(NULL),parent(nullptr), lchild(nullptr), rchild(nullptr), height(0){}
	binNode(T e, binNode* p = nullptr, binNode* lc = nullptr, binNode* rc = nullptr, int h = 0):
		data(e), parent(p), lchild(lc), rchild(rc), height(h){}
	//析构函数
	~binNode() {}

	// 成员函数
	binNode<T>* insertAsLChild(const T& e);	// 作为本节点的左孩子插入
	binNode<T>* insertAsRChild(const T& e);	// 作为本节点的右孩子插入
	int size();    //	返回以本节点为root的二叉树的规模
	// 重载运算符
	bool operator==(const binNode<T>& bn);  // 等于运算符
	bool operator<(const binNode<T>& bn);   // 小于运算符
	bool operator>(const binNode<T>& bn);   // 大于运算符
};

template<typename T>
binNode<T>* binNode<T>::insertAsLChild(const T& e)
{
	return new binNode<T>(e, this);// this为本节点(父节点)
}

template<typename T>
binNode<T>* binNode<T>::insertAsRChild(const T& e)
{
	return new binNode<T>(e, this);
}

template<typename T>
int binNode<T>::size()
{
	int n = 0;
	if (lchild && rchild)	// 左右子节点存在
		n = 1 + lchild->size() + rchild->size();// 1(当前节点) + 左节点数 + 右节点数
	else if (lchild && !rchild)
		n = 1 + lchild->size();
	else if (!lchild && rchild)
		n = 1 + rchild->size();
	else if (!lchild && !rchild)
		return 1;
	return n;
}

template<typename T>
bool binNode<T>::operator==(const binNode<T>& bn)
{
	return data == bn.data;
}

template<typename T>
bool binNode<T>::operator<(const binNode<T>& bn)
{
	return data < bn.data;
}

template<typename T>
bool binNode<T>::operator>(const binNode<T>& bn)
{
	return data > bn.data;
}

#endif // !_BINODE_H_