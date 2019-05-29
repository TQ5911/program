#ifndef _BINODE_H_
#define _BINODE_H_

#pragma once
#define stature(p)	((p)?(p)->height:-1)
#define NULL 0

template<typename T> 
struct myBinNode
{
	// ��Ա����
	T data;
	myBinNode<T> *parent, *lchild, *rchild;	// ָ���࣬�����Һ��ӵ�ָ��
	int height;								// �߶�
	//���캯��
	myBinNode() :data(NULL), lchild(nullptr), rchild(nullptr), height(0){}
	myBinNode(T e, myBinNode* p = nullptr, myBinNode* lc = nullptr, myBinNode* rc = nullptr, int h = 0) :
		data(e), parent(p), lchild(lc), rchild(rc), height(h){}
	//��������
	~myBinNode() {}

	// ��Ա����
	myBinNode<T>* insertAsLChild(const T& e);	// ��Ϊ���ڵ�����Ӳ���
	myBinNode<T>* insertAsRChild(const T& e);	// ��Ϊ���ڵ���Һ��Ӳ���
	int size();    //	�����Ա��ڵ�Ϊroot�Ķ������Ĺ�ģ
	// ���������
	bool operator==(const myBinNode<T>& bn);  // ���������
	bool operator<(const myBinNode<T>& bn);   // С�������
	bool operator>(const myBinNode<T>& bn);   // ���������
};

template<typename T>
myBinNode<T>* myBinNode<T>::insertAsLChild(const T& e)
{
	return new myBinNode<T>(e,this);// thisΪ���ڵ�(���ڵ�)
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
	if (lchild && rchild)	// �����ӽڵ����
		n = 1 + lchild->size() + rchild->size();// 1(��ǰ�ڵ�) + ��ڵ��� + �ҽڵ���
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