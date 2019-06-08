#ifndef _BINODE_H_
#define _BINODE_H_

#pragma once
#define stature(p)	((p)?(p)->height:-1)
#define NULL 0

template<typename T> 
struct myBinNode
{
	// 成员变量
	T data;
	myBinNode<T> *parent, *lchild, *rchild;	// 指向父类，左孩子右孩子的指针
	int height;								// 高度
	//构造函数
	myBinNode() :data(NULL), lchild(nullptr), rchild(nullptr), height(0){}
	myBinNode(T e, myBinNode* p = nullptr, myBinNode* lc = nullptr, myBinNode* rc = nullptr, int h = 0) :
		data(e), parent(p), lchild(lc), rchild(rc), height(h){}
	//析构函数
	~myBinNode() {}

	// 成员函数
	myBinNode<T>* insertAsLChild(const T& e);	// 作为本节点的左孩子插入
	myBinNode<T>* insertAsRChild(const T& e);	// 作为本节点的右孩子插入
	int size();    //	返回以本节点为root的二叉树的规模
	// 重载运算符
	bool operator==(const myBinNode<T>& bn);  // 等于运算符
	bool operator<(const myBinNode<T>& bn);   // 小于运算符
	bool operator>(const myBinNode<T>& bn);   // 大于运算符
};

template<typename T>
myBinNode<T>* myBinNode<T>::insertAsLChild(const T& e)
{
	return new myBinNode<T>(e,this);// this为本节点(父节点)
}

template<typename T>
myBinNode<T>* myBinNode<T>::insertAsRChild(const T& e)
{
	return new myBinNode<T>(e, this);
}

template<typename T>
int myBinNode<T>::size()
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
bool myBinNode<T>::operator==(const myBinNode<T>& bn)
{
	return data == bn.data;
}

template<typename T>
bool myBinNode<T>::operator<(const myBinNode<T>& bn)
{
	return data < bn.data;
}

template<typename T>
bool myBinNode<T>::operator>(const myBinNode<T>& bn)
{
	return data > bn.data;
}

#endif // !_BINODE_H_