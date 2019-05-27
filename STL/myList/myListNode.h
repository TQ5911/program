#pragma once
typedef int Rank;

template<typename T> 
struct myListNode   // �ڵ�Ԫ��ģ����
{
	// ��Ա����
	T data;
	myListNode<T> *pred, *succ;    // ����ǰ���ͺ��ָ�룬ʵ��˫������

	// ���캯��
	myListNode() {}     // ����listǰ���ڱ��ڵ���
	myListNode(T e, myListNode<T> *p = nullptr, myListNode<T> *s = nullptr) :data(e), pred(p), succ(s) {}
	// ��������
	~myListNode(){}

	// ��Ա����
	myListNode<T>* insertAsPred(const T& e);  // �ڵ�ǰ�ڵ�ǰ����һ���½ڵ�
	myListNode<T>* insertAsSucc(const T& e);  // �ڵ�ǰ�ڵ�����һ���½ڵ�
};

template<typename T> 
myListNode<T>* myListNode<T>::insertAsPred(const T& e)
{	
	// ��ǰ�ڵ��ǰ��Ϊ�½ڵ��ǰ������ǰ�ڵ�Ϊ�½ڵ�ĺ��
	myListNode<T> *p = new myListNode<T>(e, pred, this);    // ����4��ָ���ָ��
	pred->succ = p;
	pred = p;
	return p;
}

template<typename T> 
myListNode<T>* myListNode<T>::insertAsSucc(const T& e)
{	
	// ��ǰ�ڵ�Ϊ�½ڵ��ǰ������ǰ�ڵ�ĺ��Ϊ�½ڵ�ĺ��
	myListNode<T> *p = new myListNode<T>(e, this, succ);
	succ->pred = p;
	succ = p;
	return p;
}