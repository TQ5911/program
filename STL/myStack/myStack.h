#ifndef MYSTACK_H
#define MYSTACK_H
#pragma once
#include <iostream>

template<typename T>
class myStack:public myVector<T>
{
public:
	// ���캯��
	myStack(){};
	// ��������
	~myStack(){};

	// ��ͨ��Ա����
	int size();				// stack��ģ
	bool empty();			// �ж��Ƿ�Ϊ��
	void push(const T& e);	// ѹջ
	T pop();				// ��ջ
	T top();				// ȡ��

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
