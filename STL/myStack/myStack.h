#ifndef MYSTACK_H
#define MYSTACK_H
#pragma once
#include <iostream>

template<typename T>
class myStack:public myVector<T>
{
public:
	// 构造函数
	myStack(){};
	// 析构函数
	~myStack(){};

	// 普通成员函数
	int size();				// stack规模
	bool empty();			// 判断是否为空
	void push(const T& e);	// 压栈
	T pop();				// 弹栈
	T top();				// 取顶

};

template<typename T>
int myStack<T>::size()
{
	return myVector<T>::size();
}

template<typename T>
bool myStack<T>::empty()
{
	return m_size ? false : true;
}

template<typename T>
void myStack<T>::push(const T& e)
{
	push_back(e);
}

template<typename T>
T myStack<T>::pop()
{
	T e = back();
	pop_back();
	return e;
}

template<typename T>
T myStack<T>::top()
{
	return back();
}

#endif
