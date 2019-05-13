#ifndef _BINODE_H_
#define _BINODE_H_

#pragma once
#define stature(p)	((p)?(p)->height:-1)
#define NULL 0

template<typename T> 
struct binNode
{
	// ��Ա����
	T data;
	binNode<T> *parent, *lchild, *rchild;	// ָ���࣬�����Һ��ӵ�ָ��
	int height;								// �߶�


	//���캯��
	binNode() :data(NULL),parent(nullptr), lchild(nullptr), rchild(nullptr), height(0){}
	binNode(T e, binNode* p = nullptr, binNode* lc = nullptr, binNode* rc = nullptr, int h = 0):
		data(e), parent(p), lchild(lc), rchild(rc), height(h){}
	//��������
	~binNode() {}

	// ��Ա����
	binNode<T>* insertAsLChild(const T& e);	// ��Ϊ���ڵ�����Ӳ���
	binNode<T>* insertAsRChild(const T& e);	// ��Ϊ���ڵ���Һ��Ӳ���
	int size();    //	�����Ա��ڵ�Ϊroot�Ķ������Ĺ�ģ
	// ���������
	bool operator==(const binNode<T>& bn);  // ���������
	bool operator<(const binNode<T>& bn);   // С�������
	bool operator>(const binNode<T>& bn);   // ���������
};

template<typename T>
binNode<T>* binNode<T>::insertAsLChild(const T& e)
{
	return new binNode<T>(e, this);// thisΪ���ڵ�(���ڵ�)
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