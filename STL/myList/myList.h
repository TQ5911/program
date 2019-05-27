#ifndef MYLIST_H
#define MYLIST_H
#pragma once
#include "myListNode.h"
#include <iostream>
typedef int Rank;

template<typename T> 
class myList			// list�ṹ:[sentinel node]--[[first]...[]....[last]]--[sentinel node]
{
protected:
	int m_size;    // list��ģ
	myListNode<T> *m_header, *m_trailer;      // list��ǰ���ڱ��ڵ��ָ��

public:
	// ���캯��
	myList();
	myList(const std::initializer_list<T>& li);		// �б��ʼ�����췽ʽ
	myList(const myListNode<T>* p, int n);			// �������죬�����ڵ�p�����n����Χ�ڵ����нڵ�
	myList(myList<T>& li);					// �������죬��������list����
	myList(myList<T>& li, Rank lr, Rank rr);// �������죬����ָ��list�����ָ������
	// ��������(ֻ��Ҫ�ֶ�����new�Ķ���)
	~myList();

	// ��ͨ��Ա����
	void init();    // list��ʼ��ʱ����ǰ���ڱ��ڵ㣬_size��0
	int size();     // ����list����Ĺ�ģ
	void display(); // ��ӡ��ǰlist�е�����Ԫ��
	myListNode<T>* first();             // ���ص�һ����Ч�ڵ�ĵ�ַ
	myListNode<T>* last();              // �������һ����Ч�ڵ�ĵ�ַ
	myListNode<T>* find(const T& e, int n, myListNode<T>* p);	// �ڽڵ�p֮ǰ��n�����ȷ�Χ�ڲ���Ԫ��e
	myListNode<T>* find(const T& e);							// ����Ԫ��e
	myListNode<T>* search(const T& e, int n, myListNode<T>* p); // �ڽڵ�p֮ǰ��n�����ȷ�Χ�ڲ���Ԫ��e(Ҫ��listΪ�������У����ز����ڴ�Ԫ�ص����ڵ��ָ��)	
	myListNode<T>* search(const T& e);         // ����Ԫ��e(Ҫ��listΪ�������У����ز����ڴ�Ԫ�ص����ڵ��ָ��)
	myListNode<T>* insertAsFirst(const T& e);  // ����Ԫ����Ϊfirst�ڵ�
	myListNode<T>* insertAsLast(const T& e);   // ����Ԫ����Ϊlast�ڵ�
	myListNode<T>* insertAsPred(myListNode<T>* p, const T& e);  // �ڽڵ�P֮ǰ����Ԫ��e
	myListNode<T>* insertAsSucc(myListNode<T>* p, const T& e);  // �ڽڵ�P֮�����Ԫ��e
	myListNode<T>* insert(Rank r, const T& e);                // ��ָ���ȳ�����Ԫ��(����:���Ը��Ӷ�)
	T remove(myListNode<T>* p);          // ɾ��ָ���ڵ�
	int clear();		 // ���list��������Ч�ڵ�
	int deduplicate();   // ȥ��list���ظ�Ԫ��
	int uniquify();      // ȥ��list���ظ�Ԫ��(Ҫ��listΪ��������)
	void traverse(void(*func)(T &));		    // ��������list������Ԫ��(����ָ�뷽ʽ)
	template<typename FuncClass> void traverse(FuncClass func);	// ��������list������Ԫ��(��������ʽ)
	void sort(myListNode<T>* p, int n, int s);           // ����ӿڻ���
	void insertionSort();        // ��������
	void insertionSort(myListNode<T>* p, int n);	// �Դ�p�ڵ㿪ʼ��n��Χ�ڵĽڵ��������
	void selectionSort();        // ѡ������
	void selectionSort(myListNode<T>* p, int n);	// �Դ�p�ڵ㿪ʼ��n��Χ�ڵĽڵ��������
	void mergeSort(myListNode<T>* p, int n);		// �鲢����

	// ���������
	T& operator[](Rank r);  // �±����������
	myList<T>& operator=(const myList<T>& li); // ��ֵ���������
};
#endif
