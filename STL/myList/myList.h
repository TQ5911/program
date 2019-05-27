#ifndef MYLIST_H
#define MYLIST_H
#pragma once
#include "myListNode.h"
#include <iostream>
typedef int Rank;

template<typename T> 
class myList			// list结构:[sentinel node]--[[first]...[]....[last]]--[sentinel node]
{
protected:
	int m_size;    // list规模
	myListNode<T> *m_header, *m_trailer;      // list的前后哨兵节点的指针

public:
	// 构造函数
	myList();
	myList(const std::initializer_list<T>& li);		// 列表初始化构造方式
	myList(const myListNode<T>* p, int n);			// 拷贝构造，拷贝节点p及其后n个范围内的所有节点
	myList(myList<T>& li);					// 拷贝构造，拷贝整个list对象
	myList(myList<T>& li, Rank lr, Rank rr);// 拷贝构造，拷贝指定list对象的指定区间
	// 析构函数(只需要手动处理new的对象)
	~myList();

	// 普通成员函数
	void init();    // list初始化时创建前后哨兵节点，_size置0
	int size();     // 返回list对象的规模
	void display(); // 打印当前list中的所有元素
	myListNode<T>* first();             // 返回第一个有效节点的地址
	myListNode<T>* last();              // 返回最后一个有效节点的地址
	myListNode<T>* find(const T& e, int n, myListNode<T>* p);	// 在节点p之前的n个长度范围内查找元素e
	myListNode<T>* find(const T& e);							// 查找元素e
	myListNode<T>* search(const T& e, int n, myListNode<T>* p); // 在节点p之前的n个长度范围内查找元素e(要求list为有序序列，返回不大于此元素的最大节点的指针)	
	myListNode<T>* search(const T& e);         // 查找元素e(要求list为有序序列，返回不大于此元素的最大节点的指针)
	myListNode<T>* insertAsFirst(const T& e);  // 插入元素作为first节点
	myListNode<T>* insertAsLast(const T& e);   // 插入元素作为last节点
	myListNode<T>* insertAsPred(myListNode<T>* p, const T& e);  // 在节点P之前插入元素e
	myListNode<T>* insertAsSucc(myListNode<T>* p, const T& e);  // 在节点P之后插入元素e
	myListNode<T>* insert(Rank r, const T& e);                // 在指定秩出插入元素(警告:线性复杂度)
	T remove(myListNode<T>* p);          // 删除指定节点
	int clear();		 // 清除list内所有有效节点
	int deduplicate();   // 去除list内重复元素
	int uniquify();      // 去除list内重复元素(要求list为有序序列)
	void traverse(void(*func)(T &));		    // 批量处理list内所有元素(函数指针方式)
	template<typename FuncClass> void traverse(FuncClass func);	// 批量处理list内所有元素(函数对象方式)
	void sort(myListNode<T>* p, int n, int s);           // 排序接口汇总
	void insertionSort();        // 插入排序法
	void insertionSort(myListNode<T>* p, int n);	// 对从p节点开始的n范围内的节点进行排序
	void selectionSort();        // 选择排序法
	void selectionSort(myListNode<T>* p, int n);	// 对从p节点开始的n范围内的节点进行排序
	void mergeSort(myListNode<T>* p, int n);		// 归并排序法

	// 重载运算符
	T& operator[](Rank r);  // 下标运算符重载
	myList<T>& operator=(const myList<T>& li); // 赋值运算符重载
};
#endif
