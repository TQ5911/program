#ifndef MYQUEUE_H
#define MYQUEUE_H
#pragma once
#include "myList.h"
#include <iostream>
typedef int Rank;

template<typename T>
class myQueue:public myList<T>
{
protected:

public:
	// ���캯��
	myQueue(){}
	~myQueue(){}

	// ��������
	int size(){ return myList<T>::size(); }
	bool empty(){ return (size() ?  false : true); }
	// ���(��β)
	void push(const T& e){ insertAsLast(e); }
	// ����(��ͷ)
	void pop(){ remove(first()); }
	// ��ͷԪ��
	T front(){ return first()->data; }
	// ��βԪ��
	T back(){ return last()->data; }
};
#endif
