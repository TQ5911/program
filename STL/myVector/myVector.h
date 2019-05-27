#ifndef MYVECTOR_H
#define MYVECTOR_H
#pragma once

using namespace std;
#include <iostream>
typedef int Rank;

#define DEFAULT_CAPACITY 10 //Ĭ��������С
template <typename T>
class myVector
{
protected:
	Rank m_size;
	int m_capacity;
	T* m_elem; // myVector�ڲ���ά���������ָ��
public:
	// ���캯��(����,��ʼ��С,��ʼֵ)
	myVector(int c = DEFAULT_CAPACITY, T v = 0);
	myVector(const std::initializer_list<T>& li);    //�б��ʼ����ʽ
	myVector(const myVector<T>& A);
	myVector(const myVector<T>& A, Rank lo, Rank hi);
	//myVector(const myVector<T>& A, Rank lo = 0, Rank hi = A.size());
	//��������
	~myVector();

	// ��ͨ��Ա����
	void copyFrom(const myVector<T>& A, Rank lo, Rank hi);	// ���ƹ��캯��
	void expand();		// ��������(����)
	void sharink();		// ��������(����)
	void display() const; // ��ӡmyVector�ڲ�Ԫ��
	Rank size() const;    // ����myVector��ǰsize
	T get(Rank r);        // ��ȡָ��Ԫ��
	void replace(Rank r, const T e);  //�滻ָ��Ԫ��
	void permute();       // ����˳��
	void unsort(Rank lo, Rank hi);  // ��������˳��
	Rank find(Rank lo, Rank hi, const T e);		//����ָ��Ԫ��
	Rank insert(Rank r, const T& e);	// ����
	Rank push_back(const T& e);			// ������β������
	int remove(Rank lo, Rank hi);		// ɾ��ָ�������Ԫ��
	T remove(Rank r);					// ɾ��ָ�������ĵ���Ԫ��
	T pop_back();						// ɾ��βԪ��
	void deduplicate();					// ��ȥ�ظ�Ԫ��
	void clear();						// �������Ԫ��
	T front();							// ͷԪ��
	T back();							// βԪ��
	void traverse(void(*func)(T& a));	// ��ָ��������������Ԫ��(����ָ�뷽ʽ)
	template<typename FunClass> void traverse(FunClass func);	// ��ָ��������������Ԫ��(��������ʽ)
	bool disordered() const;      // �ж��ǲ�����������
	void uniquify();              // ����������ȥ�ظ�Ԫ��
	Rank search(Rank lo, Rank hi, const T e);	// ������������ָ�������в���Ԫ��
	Rank search(const T e);
	Rank binsearch(Rank lo, Rank hi, const T e); // �������������ֲ���
	void swap(T& a, T& b);        // ����Ԫ��ֵ
	void sort(Rank lo, Rank hi, int a);		// �����㷨����
	void bubbleSort(Rank lo, Rank hi);		// ð������
	void mergeSort(Rank lo, Rank hi);		// �鲢����(�ݹ�ʵ��)
	//���������
	T& operator[](const Rank i) const;           //�±������
	myVector<T>& operator=(const myVector<T> &A);		// ��ֵ�����
	myVector<T>& operator=(std::initializer_list<T>);   // ��ֵ��������б��ʼ��
	bool operator==(const myVector<T>& A);         // �е������
	bool operator<=(const myVector<T>& A);         // С�ڵ����ж�
	bool operator>=(const myVector<T>& A);         // ���ڵ����ж�
};

#endif