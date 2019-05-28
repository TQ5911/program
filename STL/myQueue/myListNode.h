#pragma once
typedef int Rank;

template<typename T> 
struct myListNode   // 节点元素模板类
{
	// 成员变量
	T data;
	myListNode<T> *pred, *succ;    // 定义前驱和后继指针，实现双向链表

	// 构造函数
	myListNode() {}     // 构造list前后哨兵节点用
	myListNode(T e, myListNode<T> *p = nullptr, myListNode<T> *s = nullptr) :data(e), pred(p), succ(s) {}
	// 析构函数
	~myListNode(){}

	// 成员函数
	myListNode<T>* insertAsPred(const T& e);  // 在当前节点前插入一个新节点
	myListNode<T>* insertAsSucc(const T& e);  // 在当前节点后插入一个新节点
};

template<typename T> 
myListNode<T>* myListNode<T>::insertAsPred(const T& e)
{	
	// 当前节点的前驱为新节点的前驱，当前节点为新节点的后继
	myListNode<T> *p = new myListNode<T>(e, pred, this);    // 更新4个指针的指向
	pred->succ = p;
	pred = p;
	return p;
}

template<typename T> 
myListNode<T>* myListNode<T>::insertAsSucc(const T& e)
{	
	// 当前节点为新节点的前驱，当前节点的后继为新节点的后继
	myListNode<T> *p = new myListNode<T>(e, this, succ);
	succ->pred = p;
	succ = p;
	return p;
}