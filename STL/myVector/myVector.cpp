#include "myVector.h"

// 实现c++中myVector容器底层（具体实现也要放在与声明同样的文件中）
template <typename T>
myVector<T>::myVector(int c, T v)
{
	m_elem = new T[m_capacity = c];  // 申请容量为T*c的内存空间并用m_elem指针指向该地址
	for (m_size = 0; m_size < c; )// 对有效值进行初始化并更新m_size
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
	delete[] m_elem;// 释放数组中的空间
}

template <typename T> 
void myVector<T>::copyFrom(const myVector<T>& A, Rank lo, Rank hi)
{
	if (lo > hi) swap(lo, hi);
	if (hi > A.size())throw;
	m_capacity = (hi - lo) << 1;	// 区间的两倍
	m_size = 0;
	m_elem = new T[m_capacity];		// 申请内存
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
	m_elem = new T[m_capacity <<= 1];// 扩大原来的一倍
	for (int i = 0; i < m_size; i++)
		m_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T> 
void myVector<T>::sharink()
{
	if (m_size < m_capacity / 4.0)   // m_size小于m_capacity的1/4，缩减
	{
		T *tempPtr = ((m_size << 1) > DEFAULT_CAPACITY) ? new T[m_capacity = (m_size << 1)] : new T[m_capacity = DEFAULT_CAPACITY];
		for (int i = 0; i < m_size; i++)
		{
			tempPtr[i] = m_elem[i];
		}
		delete[] m_elem;
		m_elem = tempPtr;   // 更新指针指向
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
		swap(m_elem[i], m_elem[rand() % m_size]);   // 随机找一个替换
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
Rank myVector<T>::find(Rank lo, Rank hi, const T e)  //	左闭右开
{
	if (lo > hi) swap(lo, hi);
	if (hi >= m_size)throw;
	while ((hi--) > lo)
	{
		if (m_elem[hi] == e) break;
	}
	return hi;
}

// r是下表位置
template<typename T>
Rank myVector<T>::insert(Rank r, const  T& e)
{
	if (r > m_size || r < -1)throw;
	expand();
	// Rank从r至以后的元素都要往后面移一位
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
int myVector<T>::remove(Rank lo, Rank hi)   //	左闭右开
{
	if (lo > hi) swap(lo, hi);
	// 首先指定后界秩后面的元素都往前面移动(hi-lo+1)个位置,原位置置零
	if (lo == hi) return 0;
	while (hi < m_size)
	{
		m_elem[lo++] = m_elem[hi];
		m_elem[hi++] = 0;
	}
	// 更新m_size
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

	Rank rl = 0;   // 第rl个是已经确认无重的最后一个
	Rank rr = 1;   // 第rr个是要判断的
	while (rr < m_size)  // m_size会减,rr会加
	{
		if (find(0, rl + 1, m_elem[rr]) >= 0)    // 确认是之前出现过
			remove(rr);
		else
		{
			rl++;       // 加入一个有效值
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
	Rank rl = 0;    // 已经确认好的序列的最后一个元素的秩
	Rank rr = 1;    // 正要判断的元素的秩
	while (rr < m_size)
	{
		if (m_elem[rr] != m_elem[rr - 1])  // 发现一个新值,移动到rl+1
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
	// 方法一
	// 把mi这一点作为一个分界线，单数直接作为右侧区间的左端点
	Rank mi;
	while (lo < hi)
	{
		mi = (lo + hi) >> 1;   // 取中点的时候是往左偏的
		(e < m_elem[mi]) ? hi = mi : lo = mi + 1;     // 都是左闭右开区间
	}
	return --lo;
	//{   //方法二
	//	Rank mi;
	//	while (lo<hi)
	//	{
	//		mi = (lo + hi) >> 1;
	//		if (m_elem[mi] < e)
	//			lo = mi + 1;
	//		else if(m_elem[mi] > e)
	//			hi = mi;   //都是左闭右开区间
	//		else
	//			return mi;
	//		}
	//	return -1;
	//}
}

template<typename T> 
void myVector<T>::swap( T& a,  T& b)
{
	a = a^b;      //原理:(a^b)^a=b
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
		bubbleSort(lo, hi); break;   // 冒泡排序
	case 2:;
		//selectSort(lo, hi); break;   // 选择排序
	case 3:
		mergeSort(lo, hi); break;    // 归并排序
	case 4:;
		//heapSort(lo, hi); break;     // 堆排序
	default:;
		//quickSort(lo, hi); break;    // 快速排序
	}
}

template<typename T> 
void myVector<T>::bubbleSort(Rank lo, Rank hi)
{
	bool sorted = false;   // 已有序标志
	while (!sorted)        // 如果有序，提前退出
	{
		sorted = true;
		for (int i = lo; i < hi - 1; i++)  // 在一次循环中如果发现逆序，就置标志位为false
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
void myVector<T>::mergeSort(Rank lo, Rank hi)  // 左闭右开区间
{
	if (!(lo < hi - 1)) // 只有一个元素则不用排序
		return;
	Rank mi = (lo + hi) >> 1;          //[0][1][2] [3]
	mergeSort(lo, mi);
	mergeSort(mi, hi);

	// 开始归并
	T* A = m_elem + lo;
	T* C = m_elem + mi;
	int lb = mi - lo;  //1
	int lc = hi - mi;  //2
	T* B = new T[lb];
	for (int i = 0; i < lb; i++)
		B[i] = A[i];    // 复制元素到新空间
	// 比较B和C所指序列的大小，将结果放置在A处
	for (int a = 0, i = 0, j = 0; i < lb || j < lc;)
	{
		if (i < lb&&j < lc)       // 两个序列都还有剩余
			A[a++] = (B[i] < C[j]) ? B[i++] : C[j++];
		if (i < lb && !(j < lc))  // 只有B序列还有剩余
			A[a++] = B[i++];
		if (!(i < lb) && j < lc)  // 只有C序列还有剩余
			A[a++] = C[j++];
	}
	delete[] B;  // 有new就要有delete
}

//重载[]运算符
template<typename T> 
T& myVector<T>::operator[](const Rank i) const
{
	return m_elem[i];
}

template<typename T>
myVector<T>& myVector<T>::operator=(const myVector<T> &A)
{
	// 释放之前的空间，后面会自动创建
	// delete[] m_elem;
	copyFrom(A, 0, A.size());
	return *this;  // 返回this的引用才能连续赋值A=B=C
}

template<typename T>
myVector<T>& myVector<T>::operator=(std::initializer_list<T> li)
{
	delete[] m_elem;
	m_size = 0;
	m_capacity = li.size() << 1;
	m_elem = new T[m_capacity];  //申请内存
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
