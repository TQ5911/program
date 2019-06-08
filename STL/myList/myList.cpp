#include "myList.h"
#include <iostream>
using namespace std;
// ���캯��
template<typename T>
myList<T>::myList()
{
	init();
}

// �б��ʼ�����췽ʽ
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

// �������죬�����ڵ�p�����n����Χ�ڵ����нڵ�
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

// �������죬��������list����
template<typename T>
myList<T>::myList(myList<T>& li) :myList(li.first(), li.m_size)
{
}

// �������죬����ָ��list�����ָ������(lr��0��ʼ��rr���Ϊm_size,����ҿ�)
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


// ��������(ֻ��Ҫ�ֶ�����new�Ķ���)
template<typename T>
myList<T>::~myList()
{
	clear();   // ���������Ч�ڵ�
	delete m_header;
	delete m_trailer;
}

// list��ʼ��ʱ����ǰ���ڱ��ڵ㣬_size��0
template<typename T>
void myList<T>::init()
{
	m_header = new myListNode<T>();	// ����ǰ���ڱ��ڵ�
	m_trailer = new myListNode<T>();
	m_size = 0;
	m_header->succ = m_trailer;		// ����ָ��ָ��
	m_header->pred = nullptr;
	m_trailer->pred = m_header;
	m_trailer->succ = nullptr;
}

// ����list����Ĺ�ģ
template<typename T>
int myList<T>::size()
{
	return m_size;
}

// ��ӡ��ǰlist�е�����Ԫ��
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

// ���ص�һ����Ч�ڵ�ĵ�ַ
template<typename T>
myListNode<T>* myList<T>::first()
{
	return m_header->succ;
}

// �������һ����Ч�ڵ�ĵ�ַ
template<typename T>
myListNode<T>* myList<T>::last()
{
	return m_trailer->pred;
}

// �ڽڵ�p֮ǰ��n�����ȷ�Χ�ڲ���Ԫ��e
template<typename T>
myListNode<T>* myList<T>::find(const T& e, int n, myListNode<T>* p)// ����p�ڵ㣬n > 1��������
{
	while ((n--) && (p != m_header && p != nullptr))  // �Ѿ�����n�λ��򵽴�m_header
	{
		if (p->data == e)
			return p;
		else
			p = p->pred;
	}
	return nullptr;
}

// ����Ԫ��e
template<typename T>
myListNode<T>* myList<T>::find(const T& e)
{
	return find(e, m_size, last());
}

// �ڽڵ�p֮ǰ��n�����ȷ�Χ�ڲ���Ԫ��e(Ҫ��listΪ�������У����ز����ڴ�Ԫ�ص����ڵ��ָ��)	
template<typename T>
myListNode<T>* myList<T>::search(const T& e, int n, myListNode<T>* p)
{
	while ((n--) && (p != m_header && p != nullptr))
	{
		if (p->data <= e) // ���ز�����ָ��Ԫ�ص����ڵ㣬��������������
			return p;
		else
			p = p->pred;
	}
	return p;
}

// ����Ԫ��e(Ҫ��listΪ�������У����ز����ڴ�Ԫ�ص����ڵ��ָ��)
template<typename T>
myListNode<T>* myList<T>::search(const T& e)
{
	return search(e, m_size, last());
}

// ����Ԫ����Ϊfirst�ڵ�
template<typename T>
myListNode<T>* myList<T>::insertAsFirst(const T& e)
{
	if (m_header == nullptr)
		return nullptr;
	m_size++;
	myListNode<T> *p = m_header->insertAsSucc(e);   // �����ڲ��Ѿ�������4��ָ��ָ��
	return p;
}

// ����Ԫ����Ϊlast�ڵ�
template<typename T>
myListNode<T>* myList<T>::insertAsLast(const T& e)
{
	if (m_trailer == nullptr)
		return nullptr;
	m_size++;
	myListNode<T> *p = m_trailer->insertAsPred(e);
	return p;
}

// �ڽڵ�P֮ǰ����Ԫ��e
template<typename T>
myListNode<T>* myList<T>::insertAsPred(myListNode<T>* p, const T& e)
{
	if (p == nullptr)
		return nullptr;
	m_size++;
	return p->insertAsPred(e);
}

// �ڽڵ�P֮�����Ԫ��e
template<typename T>
myListNode<T>* myList<T>::insertAsSucc(myListNode<T>* p, const T& e)
{
	if (p == nullptr)
		return nullptr;
	m_size++;
	return p->insertAsSucc(e);
}

// ��ָ���ȳ�����Ԫ��(����:���Ը��Ӷ�,r���ֵΪlist�ĳ���)
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

// ɾ��ָ���ڵ�
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

// ���list��������Ч�ڵ�
template<typename T>
int myList<T>::clear()
{
	int oldSize = m_size;
	while (m_header != nullptr && m_header->succ != m_trailer)
		remove(m_header->succ);// ɾͷ����Ľڵ�
	return oldSize;
}

// ȥ��list���ظ�Ԫ��
template<typename T>
int myList<T>::deduplicate()
{
	if (!m_size || m_header == nullptr) return 0;
	int n = 0;
	myListNode<T>* p = m_header->succ;
	myListNode<T>* lp;  // ����p��ǰһ��Ԫ��
	for (int i = 0; i < m_size && p != nullptr;)
	{
		lp = p->pred;
		if (lp != nullptr && find(p->data, m_size, p->pred))// �ڵ�ǰԪ��֮ǰѰ�ң�Խ�����˳�
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

// ȥ��list���ظ�Ԫ��(Ҫ��listΪ��������)
template<typename T>
int myList<T>::uniquify()
{
	if (!m_size || m_header == nullptr) return 0;
	int oldSize = m_size;
	myListNode<T> *p = m_header->succ;
	while (p != nullptr && p->succ != m_trailer)   // ��βԽ��ֹͣ
	{
		if (p->data == p->succ->data)// ǰ==��ɾ����ָ����ָ��ǰ
			remove(p->succ);
		else
			p = p->succ;
	}
	return oldSize - m_size;
}

// ��������list������Ԫ��(����ָ�뷽ʽ)
template<typename T>
void myList<T>::traverse(void(*func)(T &))
{
	for (Rank r = 0; r < m_size; r++)
		func((*this)[r]);
}

// ��������list������Ԫ��(��������ʽ)
template<typename T>
template<typename FuncClass> 
void myList<T>::traverse(FuncClass func)
{
	for (Rank r = 0; r < m_size; r++)
		func((*this)[r]);
}

// ����ӿڻ���
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

// ��������
template<typename T>
void myList<T>::insertionSort()
{
	if (m_size < 2) return;
	myListNode<T> *p = m_header->succ;
	while (p != nullptr && p != m_trailer)   // ��β�������ֹ
	{
		search(p->data,m_size, p->pred)->insertAsSucc(p->data);
		m_size++;
		p = p->succ;
		remove(p->pred);
	}
}


// �Դ�p�ڵ㿪ʼ��n��Χ�ڵĽڵ��������
template<typename T>
void myList<T>::insertionSort(myListNode<T>* p, int n)
{
	if (n < 2) return;
	int s = 0;
	while ((n--) && (p != m_trailer && p != nullptr))   //����n�λ���β�������ֹ
	{
		search(p->data, s, p->pred)->insertAsSucc(p->data);
		m_size++;
		p = p->succ;
		remove(p->pred);
		s++;
	}
}

// ѡ������
template<typename T>
void myList<T>::selectionSort()
{
	if (m_size < 2) return;
	myListNode<T> *p = first();
	myListNode<T> *ptr;   //�����ɾ���Ľڵ�ָ��
	for (int i = 0; i < m_size; i++)   //_size�ε���
	{
		myListNode<T>* f = first();
		if (f == nullptr)
			return;
		T min = f->data;
		p = first();
		ptr = p;
		for (int j = 0; j < m_size - i; j++)   //��ѭ������Сֵ�����뵽lastλ��(��֤�����ȶ�)
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

// �Դ�p�ڵ㿪ʼ��n��Χ�ڵĽڵ��������
template<typename T>
void myList<T>::selectionSort(myListNode<T>* p, int n)
{
	if (n < 2) return;
	p = p->pred;
	myListNode<T> *pp = p->succ;  // ����ָ��
	myListNode<T> *ptr;			// �����ɾ���Ľڵ�ָ��
	myListNode<T> *trail = p;		// ������������һ��Ԫ��,����������Ϊ(p->pred,trail)
	if (trail == nullptr)
		return;
	for (int i = 0; i < n + 1; i++)
		trail = trail->succ;
	for (int i = 0; i < n; i++)			  // n�ε���
	{
		if (p == nullptr)
			return;
		T min = (p->succ)->data;
		pp = p->succ;
		ptr = p->succ;
		for (int j = 0; j < n - i; j++)   // ��ѭ������Сֵ�����뵽trailλ��(��֤�����ȶ�)
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

 // �鲢����
template<typename T>
void myList<T>::mergeSort(myListNode<T>* p, int n)
{
	if (n < 2) return;
	//��ʼ����
	myListNode<T>* ppred = p->pred;  //���������list��ǰ�ڱ�
	myListNode<T>* pmi = p;  //�����м�ڵ�
	if (pmi == nullptr || ppred == nullptr)
		return;
	for (int i = 0; i < (n >> 1); i++)       //[p0,p1,p2] n=3 ==>  [p0] [p1,p2]
	{
		pmi = pmi->succ;
	}
	mergeSort(p, n >> 1);         //������ݹ�����ʾ�ѷ�������������о��Ѿ��������
	mergeSort(pmi, n - (n >> 1));

	//��ʼ�鲢���������������==��һ���������У�  [pred][AAAAAAAAA][BBBBBBBBB]

	//���¸��˵�ĵ�ַ(�ڵݹ�ʱ�����ɾ���ı����߼�˳��ڵ��ʵ�������ַ)
	p = ppred->succ;
	pmi = p;  //�����м�ڵ�
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
		if ((i > 0) && (j == 0))   //ֻʣ��ǰ��list
		{
			i--;
			ppred->insertAsSucc(p->data);
			ppred = ppred->succ;
			m_size++;
			p = p->succ;
			remove(p->pred);
		}
		if ((j > 0) && (i == 0))    //ֻʣ�º��list
		{
			j--;
			ppred->insertAsSucc(pmi->data);
			ppred = ppred->succ;
			m_size++;
			pmi = pmi->succ;
			remove(pmi->pred);
		}
		if ((i > 0) && (j > 0))     //����list����ֵ����ѡ����С�Ĳ���ǰ��
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

// �±����������
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

// ��ֵ���������
template<typename T>
myList<T>& myList<T>::operator=(const myList<T>& li)
{
	clear();  //�����Ч�ڵ�
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