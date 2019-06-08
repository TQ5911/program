#include "myList.h"
#include <iostream>
using namespace std;
// 构造函数
template<typename T>
myList<T>::myList()
{
	init();
}

// 列表初始化构造方式
template<typename T>
myList<T>::myList(const std::initializer_list<T>& li)
{
	init();
	myListNode<T> *p = m_header;
	if (p == nullptr)
		return;
	std::initializer_list<T>::iterator ite = li.begin();
	for (;ite != li.end(); ite++)
	{

		p = p->insertAsSucc(*ite);
		m_size++;
	}
}

// 拷贝构造，拷贝节点p及其后n个范围内的所有节点
template<typename T>
myList<T>::myList(const myListNode<T>* p, int n)
{
	init();
	myListNode<T> *ptr = m_header;
	while (n-- && ptr != nullptr && p != nullptr)
	{
		ptr = ptr->insertAsSucc(p->data);
		p = p->succ;
		m_size++;
	}
}

// 拷贝构造，拷贝整个list对象
template<typename T>
myList<T>::myList(myList<T>& li) :myList(li.first(), li.m_size)
{
}

// 拷贝构造，拷贝指定list对象的指定区间(lr从0开始，rr最大为m_size,左闭右开)
template<typename T>
myList<T>::myList(myList<T>& li, Rank lr, Rank rr)
{
	init();
	myListNode<T>* p = li.first();
	myListNode<T>* ptr = m_header;
	for (int i = 0; i < rr && p != nullptr && ptr != nullptr; i++)
	{
		if (i < lr)
			p = p->succ;
		else
		{
			ptr = ptr->insertAsSucc(p->data);
			p = p->succ;
			m_size++;
		}
	}
}


// 析构函数(只需要手动处理new的对象)
template<typename T>
myList<T>::~myList()
{
	clear();   // 清除所有有效节点
	delete m_header;
	delete m_trailer;
}

// list初始化时创建前后哨兵节点，_size置0
template<typename T>
void myList<T>::init()
{
	m_header = new myListNode<T>();	// 创建前后哨兵节点
	m_trailer = new myListNode<T>();
	m_size = 0;
	m_header->succ = m_trailer;		// 设置指针指向
	m_header->pred = nullptr;
	m_trailer->pred = m_header;
	m_trailer->succ = nullptr;
}

// 返回list对象的规模
template<typename T>
int myList<T>::size()
{
	return m_size;
}

// 打印当前list中的所有元素
template<typename T>
void myList<T>::display()
{
	//myListNode<T>* p = m_header;
	//cout << "size:" << m_size << endl;
	//if (m_size)
	//{
	//	for (Rank r = 0; r < m_size; r++)
	//	{
	//		p = p->succ;
	//		(r < (m_size - 1)) ? cout << p->data << "," : cout << p->data;
	//	}
	//	cout << endl;
	//}
	myListNode<T>* p = m_header->succ;
	while (p != m_trailer && p != nullptr)
	{
		cout << p->data << ",";
		p = p->succ;
	}
	cout << "\b " << endl;
}

// 返回第一个有效节点的地址
template<typename T>
myListNode<T>* myList<T>::first()
{
	return m_header->succ;
}

// 返回最后一个有效节点的地址
template<typename T>
myListNode<T>* myList<T>::last()
{
	return m_trailer->pred;
}

// 在节点p之前的n个长度范围内查找元素e
template<typename T>
myListNode<T>* myList<T>::find(const T& e, int n, myListNode<T>* p)// 包含p节点，n > 1才能搜索
{
	while ((n--) && (p != m_header && p != nullptr))  // 已经遍历n次或则到达m_header
	{
		if (p->data == e)
			return p;
		else
			p = p->pred;
	}
	return nullptr;
}

// 查找元素e
template<typename T>
myListNode<T>* myList<T>::find(const T& e)
{
	return find(e, m_size, last());
}

// 在节点p之前的n个长度范围内查找元素e(要求list为有序序列，返回不大于此元素的最大节点的指针)	
template<typename T>
myListNode<T>* myList<T>::search(const T& e, int n, myListNode<T>* p)
{
	while ((n--) && (p != m_header && p != nullptr))
	{
		if (p->data <= e) // 返回不大于指定元素的最大节点，方便在其后面插入
			return p;
		else
			p = p->pred;
	}
	return p;
}

// 查找元素e(要求list为有序序列，返回不大于此元素的最大节点的指针)
template<typename T>
myListNode<T>* myList<T>::search(const T& e)
{
	return search(e, m_size, last());
}

// 插入元素作为first节点
template<typename T>
myListNode<T>* myList<T>::insertAsFirst(const T& e)
{
	if (m_header == nullptr)
		return nullptr;
	m_size++;
	myListNode<T> *p = m_header->insertAsSucc(e);   // 函数内部已经更新了4个指针指向
	return p;
}

// 插入元素作为last节点
template<typename T>
myListNode<T>* myList<T>::insertAsLast(const T& e)
{
	if (m_trailer == nullptr)
		return nullptr;
	m_size++;
	myListNode<T> *p = m_trailer->insertAsPred(e);
	return p;
}

// 在节点P之前插入元素e
template<typename T>
myListNode<T>* myList<T>::insertAsPred(myListNode<T>* p, const T& e)
{
	if (p == nullptr)
		return nullptr;
	m_size++;
	return p->insertAsPred(e);
}

// 在节点P之后插入元素e
template<typename T>
myListNode<T>* myList<T>::insertAsSucc(myListNode<T>* p, const T& e)
{
	if (p == nullptr)
		return nullptr;
	m_size++;
	return p->insertAsSucc(e);
}

// 在指定秩出插入元素(警告:线性复杂度,r最大值为list的长度)
template<typename T>
myListNode<T>* myList<T>::insert(Rank r, const T& e)
{
	myListNode<T> *p = m_header;
	while (r-- && p != nullptr)
	{
		p = p->succ;
	}
	return insertAsSucc(p, e);
}

// 删除指定节点
template<typename T>
T myList<T>::remove(myListNode<T>* p)
{
	if (p == nullptr)
		return T(0);
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	m_size--;
	delete p;
	return e;
}

// 清除list内所有有效节点
template<typename T>
int myList<T>::clear()
{
	int oldSize = m_size;
	while (m_header != nullptr && m_header->succ != m_trailer)
		remove(m_header->succ);// 删头结点后的节点
	return oldSize;
}

// 去除list内重复元素
template<typename T>
int myList<T>::deduplicate()
{
	if (!m_size || m_header == nullptr) return 0;
	int n = 0;
	myListNode<T>* p = m_header->succ;
	myListNode<T>* lp;  // 缓存p的前一个元素
	for (int i = 0; i < m_size && p != nullptr;)
	{
		lp = p->pred;
		if (lp != nullptr && find(p->data, m_size, p->pred))// 在当前元素之前寻找，越界则退出
		{
			remove(p); 
			n++;
			p = lp->succ;
		}
		else
		{
			i++;
			p = p->succ;
		}
	}
	return n;
}

// 去除list内重复元素(要求list为有序序列)
template<typename T>
int myList<T>::uniquify()
{
	if (!m_size || m_header == nullptr) return 0;
	int oldSize = m_size;
	myListNode<T> *p = m_header->succ;
	while (p != nullptr && p->succ != m_trailer)   // 队尾越界停止
	{
		if (p->data == p->succ->data)// 前==后，删除后，指针仍指向前
			remove(p->succ);
		else
			p = p->succ;
	}
	return oldSize - m_size;
}

// 批量处理list内所有元素(函数指针方式)
template<typename T>
void myList<T>::traverse(void(*func)(T &))
{
	for (Rank r = 0; r < m_size; r++)
		func((*this)[r]);
}

// 批量处理list内所有元素(函数对象方式)
template<typename T>
template<typename FuncClass> 
void myList<T>::traverse(FuncClass func)
{
	for (Rank r = 0; r < m_size; r++)
		func((*this)[r]);
}

// 排序接口汇总
template<typename T>
void myList<T>::sort(myListNode<T>* p, int n, int s)
{
	switch (s)
	{
	case 0:
		 insertionSort(p, n);
		//insertionSort();
		break;
	case 1:
		// selectionSort(p, n); 
		selectionSort();
		break;
	case 2:
		mergeSort(p, n); break;
	default:
		break;
	}
}

// 插入排序法
template<typename T>
void myList<T>::insertionSort()
{
	if (m_size < 2) return;
	myListNode<T> *p = m_header->succ;
	while (p != nullptr && p != m_trailer)   // 列尾溢出则终止
	{
		search(p->data,m_size, p->pred)->insertAsSucc(p->data);
		m_size++;
		p = p->succ;
		remove(p->pred);
	}
}


// 对从p节点开始的n范围内的节点进行排序
template<typename T>
void myList<T>::insertionSort(myListNode<T>* p, int n)
{
	if (n < 2) return;
	int s = 0;
	while ((n--) && (p != m_trailer && p != nullptr))   //变量n次或列尾溢出则终止
	{
		search(p->data, s, p->pred)->insertAsSucc(p->data);
		m_size++;
		p = p->succ;
		remove(p->pred);
		s++;
	}
}

// 选择排序法
template<typename T>
void myList<T>::selectionSort()
{
	if (m_size < 2) return;
	myListNode<T> *p = first();
	myListNode<T> *ptr;   //缓存待删除的节点指针
	for (int i = 0; i < m_size; i++)   //_size次迭代
	{
		myListNode<T>* f = first();
		if (f == nullptr)
			return;
		T min = f->data;
		p = first();
		ptr = p;
		for (int j = 0; j < m_size - i; j++)   //内循环找最小值并插入到last位置(保证排序稳定)
		{
			if (p != nullptr && p->data <= min)
			{
				min = p->data;
				ptr = p;
			}
			p = p->succ;
		}
		remove(ptr);
		insertAsLast(min);
	}
}

// 对从p节点开始的n范围内的节点进行排序
template<typename T>
void myList<T>::selectionSort(myListNode<T>* p, int n)
{
	if (n < 2) return;
	p = p->pred;
	myListNode<T> *pp = p->succ;  // 迭代指针
	myListNode<T> *ptr;			// 缓存待删除的节点指针
	myListNode<T> *trail = p;		// 排序区间的最后一个元素,即排序区间为(p->pred,trail)
	if (trail == nullptr)
		return;
	for (int i = 0; i < n + 1; i++)
		trail = trail->succ;
	for (int i = 0; i < n; i++)			  // n次迭代
	{
		if (p == nullptr)
			return;
		T min = (p->succ)->data;
		pp = p->succ;
		ptr = p->succ;
		for (int j = 0; j < n - i; j++)   // 内循环找最小值并插入到trail位置(保证排序稳定)
		{
			if (pp == nullptr)
				return;
			if ((pp->data) <= min)
			{
				min = pp->data;
				ptr = pp;
			}
			pp = pp->succ;
		}
		remove(ptr);
		trail->insertAsPred(min);
		m_size++;
	}
}

 // 归并排序法
template<typename T>
void myList<T>::mergeSort(myListNode<T>* p, int n)
{
	if (n < 2) return;
	//开始分裂
	myListNode<T>* ppred = p->pred;  //缓存待排序list的前哨兵
	myListNode<T>* pmi = p;  //计算中间节点
	if (pmi == nullptr || ppred == nullptr)
		return;
	for (int i = 0; i < (n >> 1); i++)       //[p0,p1,p2] n=3 ==>  [p0] [p1,p2]
	{
		pmi = pmi->succ;
	}
	mergeSort(p, n >> 1);         //这两句递归语句表示已分离的两个子序列均已经排序完成
	mergeSort(pmi, n - (n >> 1));

	//开始归并（两个有序短序列==》一个有序长序列）  [pred][AAAAAAAAA][BBBBBBBBB]

	//更新各端点的地址(在递归时插入和删除改变了逻辑顺序节点的实际物理地址)
	p = ppred->succ;
	pmi = p;  //计算中间节点
	for (int i = 0; i < (n >> 1); i++)
	{
		if (pmi == nullptr)
			return;
		pmi = pmi->succ;
	}
	for (Rank i = (n >> 1), j = (n - (n >> 1)); i || j;)
	{
		if (p == nullptr || ppred == nullptr || pmi == nullptr)
			return;
		if ((i > 0) && (j == 0))   //只剩下前段list
		{
			i--;
			ppred->insertAsSucc(p->data);
			ppred = ppred->succ;
			m_size++;
			p = p->succ;
			remove(p->pred);
		}
		if ((j > 0) && (i == 0))    //只剩下后段list
		{
			j--;
			ppred->insertAsSucc(pmi->data);
			ppred = ppred->succ;
			m_size++;
			pmi = pmi->succ;
			remove(pmi->pred);
		}
		if ((i > 0) && (j > 0))     //两段list都有值，则选择最小的插在前面
		{
			if ((p->data) < (pmi->data))
			{
				i--;
				ppred->insertAsSucc(p->data);
				ppred = ppred->succ;
				m_size++;
				p = p->succ;
				remove(p->pred);
			}
			else
			{
				j--;
				ppred->insertAsSucc(pmi->data);
				ppred = ppred->succ;
				m_size++;
				pmi = pmi->succ;
				remove(pmi->pred);
			}
		}
	}
}

// 下标运算符重载
template<typename T>
T& myList<T>::operator[](Rank r)
{
	myListNode<T>* p = m_header->succ;
	while (r-- > 0 && p != nullptr)
	{
		p = p->succ;
	}
	return p->data;
}

// 赋值运算符重载
template<typename T>
myList<T>& myList<T>::operator=(const myList<T>& li)
{
	clear();  //清空有效节点
	if (!li.m_size) return *this;
	myListNode<T>* p = li.m_header;
	myListNode<T>* lp = m_header;

	while (p != nullptr && lp != nullptr && (p = p->succ) != li.m_trailer)
	{
		lp->insertAsSucc(p->data);
		lp = lp->succ;
		m_size++;
	}
	return *this;
}