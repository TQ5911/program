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
	// 构造函数
	myQueue(){}
	~myQueue(){}

	// 析构函数
	int size(){ return myList<T>::size(); }
	bool empty(){ return (size() ?  false : true); }
	// 入队(队尾)
	void push(const T& e){ insertAsLast(e); }
	// 出队(队头)
	void pop(){ remove(first()); }
	// 队头元素
	T front(){ return first()->data; }
	// 队尾元素
	T back(){ return last()->data; }
};
#endif
