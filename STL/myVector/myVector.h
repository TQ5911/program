#ifndef MYVECTOR_H
#define MYVECTOR_H
#pragma once

using namespace std;
#include <iostream>
typedef int Rank;

#define DEFAULT_CAPACITY 10 //默认容量大小
template <typename T>
class myVector
{
protected:
	Rank m_size;
	int m_capacity;
	T* m_elem; // myVector内部所维护的数组的指针
public:
	// 构造函数(容量,初始大小,初始值)
	myVector(int c = DEFAULT_CAPACITY, T v = 0);
	myVector(const std::initializer_list<T>& li);    //列表初始化方式
	myVector(const myVector<T>& A);
	myVector(const myVector<T>& A, Rank lo, Rank hi);
	//myVector(const myVector<T>& A, Rank lo = 0, Rank hi = A.size());
	//析构函数
	~myVector();

	// 普通成员函数
	void copyFrom(const myVector<T>& A, Rank lo, Rank hi);	// 复制构造函数
	void expand();		// 容量更新(扩容)
	void sharink();		// 容量更新(缩减)
	void display() const; // 打印myVector内部元素
	Rank size() const;    // 返回myVector当前size
	T get(Rank r);        // 获取指定元素
	void replace(Rank r, const T e);  //替换指定元素
	void permute();       // 打乱顺序
	void unsort(Rank lo, Rank hi);  // 打乱区间顺序
	Rank find(Rank lo, Rank hi, const T e);		//查找指定元素
	Rank insert(Rank r, const T& e);	// 插入
	Rank push_back(const T& e);			// 在向量尾部插入
	int remove(Rank lo, Rank hi);		// 删除指定区间的元素
	T remove(Rank r);					// 删除指定索引的单个元素
	T pop_back();						// 删除尾元素
	void deduplicate();					// 除去重复元素
	void clear();						// 清除所有元素
	T front();							// 头元素
	T back();							// 尾元素
	void traverse(void(*func)(T& a));	// 用指定函数批量处理元素(函数指针方式)
	template<typename FunClass> void traverse(FunClass func);	// 用指定函数批量处理元素(函数对象方式)
	bool disordered() const;      // 判断是不是有序向量
	void uniquify();              // 有序向量除去重复元素
	Rank search(Rank lo, Rank hi, const T e);	// 有序向量，在指定区间中查找元素
	Rank search(const T e);
	Rank binsearch(Rank lo, Rank hi, const T e); // 有序向量，二分查找
	void swap(T& a, T& b);        // 交换元素值
	void sort(Rank lo, Rank hi, int a);		// 排序算法汇总
	void bubbleSort(Rank lo, Rank hi);		// 冒泡排序
	void mergeSort(Rank lo, Rank hi);		// 归并排序(递归实现)
	//重载运算符
	T& operator[](const Rank i) const;           //下标运算符
	myVector<T>& operator=(const myVector<T> &A);		// 赋值运算符
	myVector<T>& operator=(std::initializer_list<T>);   // 赋值运算符，列表初始化
	bool operator==(const myVector<T>& A);         // 判等运算符
	bool operator<=(const myVector<T>& A);         // 小于等于判断
	bool operator>=(const myVector<T>& A);         // 大于等于判断
};

#endif