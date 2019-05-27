#include "myVector.h"

// ʵ��c++��myVector�����ײ㣨����ʵ��ҲҪ����������ͬ�����ļ��У�
template <typename T>
myVector<T>::myVector(int c, T v)
{
	m_elem = new T[m_capacity = c];  // ��������ΪT*c���ڴ�ռ䲢��m_elemָ��ָ��õ�ַ
	for (m_size = 0; m_size < c; )// ����Чֵ���г�ʼ��������m_size
		m_elem[m_size++] = v;  
}


template <typename T>
myVector<T>::myVector(const myVector<T>& A)
{
	*this = A;
	// copyFrom(A, 0, A.size());
}


template<typename T>
myVector<T>::myVector(const std::initializer_list<T>& li)
{
	m_elem = new T[m_capacity = li.size()];
	m_size = 0;
	for (auto iter = li.begin(); iter != li.end(); ++iter)
		m_elem[m_size++] = *iter;
}

template <typename T>
myVector<T>::myVector(const myVector<T>& A, Rank lo, Rank hi)
{
	copyFrom(A, lo, hi);
}

template <typename T>
myVector<T>::~myVector()
{
	delete[] m_elem;// �ͷ������еĿռ�
}

template <typename T> 
void myVector<T>::copyFrom(const myVector<T>& A, Rank lo, Rank hi)
{
	if (lo > hi) swap(lo, hi);
	if (hi > A.size())throw;
	m_capacity = (hi - lo) << 1;	// ���������
	m_size = 0;
	m_elem = new T[m_capacity];		// �����ڴ�
	while (lo < hi)
	{
		m_elem[m_size++] = A[lo++];
	}
}

template<typename T>
void myVector<T>::expand()
{
	if (m_size < m_capacity) return;
	if (m_capacity < DEFAULT_CAPACITY) m_capacity = DEFAULT_CAPACITY;
	T* oldElem = m_elem;
	m_elem = new T[m_capacity <<= 1];// ����ԭ����һ��
	for (int i = 0; i < m_size; i++)
		m_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T> 
void myVector<T>::sharink()
{
	if (m_size < m_capacity / 4.0)   // m_sizeС��m_capacity��1/4������
	{
		T *tempPtr = ((m_size << 1) > DEFAULT_CAPACITY) ? new T[m_capacity = (m_size << 1)] : new T[m_capacity = DEFAULT_CAPACITY];
		for (int i = 0; i < m_size; i++)
		{
			tempPtr[i] = m_elem[i];
		}
		delete[] m_elem;
		m_elem = tempPtr;   // ����ָ��ָ��
	}
}

template<typename T> 
void myVector<T>::display() const
{
	if (m_size)
	{
		for (int i = 0; i < m_size - 1; i++)
		{
			cout << m_elem[i] << ",";
		}
		cout << m_elem[m_size - 1] << endl;
	}
}

template<typename T>
Rank myVector<T>::size() const
{
	return m_size;
}

template<typename T>
T myVector<T>::get(Rank r)
{
	if (r >= m_size)
		throw;
	return m_elem[r];
}

template<typename T>
void myVector<T>::replace(Rank r, const T e)
{
	if (r >= m_size)throw;
	m_elem[r] = e;
}

template<typename T> 
void myVector<T>::permute()
{
	for (int i = 0; i < m_size; i++)
	{
		swap(m_elem[i], m_elem[rand() % m_size]);   // �����һ���滻
	}
}

template<typename T>
void myVector<T>::unsort(Rank lo, Rank hi)
{
	if (lo > hi) swap(lo, hi);
	if (hi >= m_size)throw;
	for (int i = lo; i < hi; i++)
	{
		swap(m_elem[i], m_elem[rand() % (hi - lo) + lo]);
	}
}

template<typename T>  
Rank myVector<T>::find(Rank lo, Rank hi, const T e)  //	����ҿ�
{
	if (lo > hi) swap(lo, hi);
	if (hi >= m_size)throw;
	while ((hi--) > lo)
	{
		if (m_elem[hi] == e) break;
	}
	return hi;
}

// r���±�λ��
template<typename T>
Rank myVector<T>::insert(Rank r, const  T& e)
{
	if (r > m_size || r < -1)throw;
	expand();
	// Rank��r���Ժ��Ԫ�ض�Ҫ��������һλ
	for (int i = m_size; i > r; i--)
	{
		m_elem[i] = m_elem[i - 1];
	}
	m_elem[r] = e;
	m_size++;
	return r;
}

template<typename T> 
Rank myVector<T>::push_back(const T& e)
{
	return insert(m_size, e);
}

template<typename T> 
int myVector<T>::remove(Rank lo, Rank hi)   //	����ҿ�
{
	if (lo > hi) swap(lo, hi);
	// ����ָ������Ⱥ����Ԫ�ض���ǰ���ƶ�(hi-lo+1)��λ��,ԭλ������
	if (lo == hi) return 0;
	while (hi < m_size)
	{
		m_elem[lo++] = m_elem[hi];
		m_elem[hi++] = 0;
	}
	// ����m_size
	m_size -= (hi - lo);
	sharink();
	return (hi - lo);
}

template<typename T> 
T myVector<T>::remove(Rank r)
{
	if (r > m_size || r < 0)throw;
	T e = m_elem[r];
	remove(r, r + 1);
	return e;
}
template<typename T>
T myVector<T>::pop_back()
{
	if (!m_size) return 0;
	return remove(m_size - 1);
}

template<typename T>
void myVector<T>::deduplicate()
{
	if (m_size <= 1) return;

	Rank rl = 0;   // ��rl�����Ѿ�ȷ�����ص����һ��
	Rank rr = 1;   // ��rr����Ҫ�жϵ�
	while (rr < m_size)  // m_size���,rr���
	{
		if (find(0, rl + 1, m_elem[rr]) >= 0)    // ȷ����֮ǰ���ֹ�
			remove(rr);
		else
		{
			rl++;       // ����һ����Чֵ
			rr++;
		}
	}
}


template <typename T>
void myVector<T>::clear()
{
	delete[] m_elem;
	m_elem = new T[m_capacity = DEFAULT_CAPACITY];
	m_size = 0;
	for (int i = 0; i < m_capacity; ++i)
		m_elem[i] = 0;
}


template <typename T>
T myVector<T>::front()
{
	if (!m_size)throw;
	return m_elem[0];
}

template <typename T>
T myVector<T>::back()
{
	if (!m_size)throw;
	return m_elem[m_size - 1];
}

template<typename T>
void myVector<T>::traverse(void(*func)(T& a))
{
	for (int i = 0; i < m_size; i++)
	{
		func(m_elem[i]);
	}
}

template<typename T> 
template<typename FunClass> 
void myVector<T>::traverse(FunClass func)
{
	for (int i = 0; i < m_size; i++)
	{
		func(m_elem[i]);
	}
}

template<typename T> bool myVector<T>::disordered() const
{
	for (int i = 0; i < m_size - 1; i++)
	{
		if (m_elem[i] > m_elem[i + 1])
		{
			return false;
		}
	}
	return true;
}

template<typename T> 
void myVector<T>::uniquify()
{
	if (m_size <= 1) return;
	Rank rl = 0;    // �Ѿ�ȷ�Ϻõ����е����һ��Ԫ�ص���
	Rank rr = 1;    // ��Ҫ�жϵ�Ԫ�ص���
	while (rr < m_size)
	{
		if (m_elem[rr] != m_elem[rr - 1])  // ����һ����ֵ,�ƶ���rl+1
		{
			m_elem[++rl] = m_elem[rr++];
		}
		else
			rr++;
	}
	m_size = rl + 1;
	sharink();
}

template<typename T> 
Rank myVector<T>::search(Rank lo, Rank hi, const T e)
{
	if (lo > hi) swap(lo, hi);
	if (hi > m_size)throw;
	return binsearch(lo, hi, e);
}

template<typename T> 
Rank myVector<T>::search(const T e)
{
	return (m_size <= 0) ? -1 : search(0, m_size, e);
}

template<typename T> 
Rank myVector<T>::binsearch(Rank lo, Rank hi, const T e)    //  [0][1][2][3][m][5][6][7][hi(8)]
{
	// ����һ
	// ��mi��һ����Ϊһ���ֽ��ߣ�����ֱ����Ϊ�Ҳ��������˵�
	Rank mi;
	while (lo < hi)
	{
		mi = (lo + hi) >> 1;   // ȡ�е��ʱ��������ƫ��
		(e < m_elem[mi]) ? hi = mi : lo = mi + 1;     // ��������ҿ�����
	}
	return --lo;
	//{   //������
	//	Rank mi;
	//	while (lo<hi)
	//	{
	//		mi = (lo + hi) >> 1;
	//		if (m_elem[mi] < e)
	//			lo = mi + 1;
	//		else if(m_elem[mi] > e)
	//			hi = mi;   //��������ҿ�����
	//		else
	//			return mi;
	//		}
	//	return -1;
	//}
}

template<typename T> 
void myVector<T>::swap( T& a,  T& b)
{
	a = a^b;      //ԭ��:(a^b)^a=b
	b = a^b;
	a = a^b;
}

template<typename T> 
void myVector<T>::sort(Rank lo, Rank hi, int a)
{
	if (lo > hi) swap(lo, hi);
	if (hi > m_size)throw;
	switch (a)
	{
	case 1:
		bubbleSort(lo, hi); break;   // ð������
	case 2:;
		//selectSort(lo, hi); break;   // ѡ������
	case 3:
		mergeSort(lo, hi); break;    // �鲢����
	case 4:;
		//heapSort(lo, hi); break;     // ������
	default:;
		//quickSort(lo, hi); break;    // ��������
	}
}

template<typename T> 
void myVector<T>::bubbleSort(Rank lo, Rank hi)
{
	bool sorted = false;   // �������־
	while (!sorted)        // ���������ǰ�˳�
	{
		sorted = true;
		for (int i = lo; i < hi - 1; i++)  // ��һ��ѭ��������������򣬾��ñ�־λΪfalse
		{
			if (m_elem[i] > m_elem[i + 1])
			{
				sorted = false;
				swap(m_elem[i], m_elem[i + 1]);
			}
		}
		hi--;
	}
}

template<typename T> 
void myVector<T>::mergeSort(Rank lo, Rank hi)  // ����ҿ�����
{
	if (!(lo < hi - 1)) // ֻ��һ��Ԫ����������
		return;
	Rank mi = (lo + hi) >> 1;          //[0][1][2] [3]
	mergeSort(lo, mi);
	mergeSort(mi, hi);

	// ��ʼ�鲢
	T* A = m_elem + lo;
	T* C = m_elem + mi;
	int lb = mi - lo;  //1
	int lc = hi - mi;  //2
	T* B = new T[lb];
	for (int i = 0; i < lb; i++)
		B[i] = A[i];    // ����Ԫ�ص��¿ռ�
	// �Ƚ�B��C��ָ���еĴ�С�������������A��
	for (int a = 0, i = 0, j = 0; i < lb || j < lc;)
	{
		if (i < lb&&j < lc)       // �������ж�����ʣ��
			A[a++] = (B[i] < C[j]) ? B[i++] : C[j++];
		if (i < lb && !(j < lc))  // ֻ��B���л���ʣ��
			A[a++] = B[i++];
		if (!(i < lb) && j < lc)  // ֻ��C���л���ʣ��
			A[a++] = C[j++];
	}
	delete[] B;  // ��new��Ҫ��delete
}

//����[]�����
template<typename T> 
T& myVector<T>::operator[](const Rank i) const
{
	return m_elem[i];
}

template<typename T>
myVector<T>& myVector<T>::operator=(const myVector<T> &A)
{
	// �ͷ�֮ǰ�Ŀռ䣬������Զ�����
	// delete[] m_elem;
	copyFrom(A, 0, A.size());
	return *this;  // ����this�����ò���������ֵA=B=C
}

template<typename T>
myVector<T>& myVector<T>::operator=(std::initializer_list<T> li)
{
	delete[] m_elem;
	m_size = 0;
	m_capacity = li.size() << 1;
	m_elem = new T[m_capacity];  //�����ڴ�
	for (auto iter = li.begin(); iter != li.end(); iter++)
		m_elem[m_size++] = *iter;

	return *this;
}

template<typename T>
bool myVector<T>::operator==(const myVector<T>& A)
{
	if (m_size != A.size()) return false;
	for (int i = 0; i < m_size; i++)
	{
		if (m_elem[i] != A[i]) return false;
	}
	return true;
}

template<typename T> 
bool myVector<T>::operator<=(const myVector<T>& A)
{
	int min = (m_size <= A.size()) ? m_size : A.size();
	for (int i = 0; i < min; i++)
	{
		if ((*this)[i] != A[i])
			return ((*this)[i] <= A[i]) ? true : false;
	}
	return (m_size <= A.size()) ? true : false;
}

template<typename T>
bool myVector<T>::operator>=(const myVector<T>& A)
{
	int min = (m_size <= A.size()) ? m_size : A.size();
	for (int i = 0; i < min; i++)
	{
		if ((*this)[i] != A[i])
			return ((*this)[i] >= A[i]) ? true : false;
	}
	return (m_size >= A.size()) ? true : false;
}
