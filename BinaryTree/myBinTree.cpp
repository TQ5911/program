/************************************************************************/
/* 
��ģ��Ķ����ʵ�ַ�������������ڱ���׶ξͲ�ͨ��
���1���Ѷ����ʵ�ֶ��ŵ�ͷ�ļ���
���2����ʵ�ֵĵ��ú����ļ���ͷ����#include "myBinTree.cpp"(����treeMain.cpp�����#include "myBinTree.cpp",������д��������)
*/
/************************************************************************/

#include "myBinTree.h"
#include <iostream>

using namespace  std;
/*
func Ϊ��ӡ�ڵ����ݵĺ���
*/

// ���캯��
template<typename T>
myBinTree<T>::myBinTree() :m_size(0), m_pRoot(nullptr){}

//��������
template<typename T>
myBinTree<T>::~myBinTree()
{
	if (m_size)
		remove(m_pRoot);
}

// ���ض������Ĺ�ģ
template<typename T>
int myBinTree<T>::size()
{
	return m_size;
}

// �ж϶������Ƿ�Ϊ��
template<typename T>
bool myBinTree<T>::empty()
{
	return !m_pRoot ? true : false;
}

// ���ظ��ڵ��ָ��
template<typename T>
myBinNode<T>* myBinTree<T>::getRoot()
{
	return m_pRoot;
}

// ��ָ��Ԫ�ز�����Ϊ���ڵ�
template<typename T>
myBinNode<T>* myBinTree<T>::insertAsRoot(const T& e)
{
	if (m_pRoot)
		return nullptr;
	m_size = 1;
	return m_pRoot = new myBinNode<T>(e);
}

// ��ָ��Ԫ�ز�����Ϊָ���ڵ������
template<typename T>
myBinNode<T>* myBinTree<T>::insertAsLChild(myBinNode<T>* bn, const T& e)
{
	if (bn->lchild)		//�������Ѿ������򷵻�
		return nullptr;
	bn->lchild = bn->insertAsLChild(e);
	//bn->lchild = new myBinNode<T>(e, bn);
	++m_size;
	updateHeightAbove(bn->lchild);
	return bn->lchild;
}

// ��ָ��Ԫ�ز�����Ϊָ���ڵ������
template<typename T>
myBinNode<T>* myBinTree<T>::insertAsRChild(myBinNode<T>* bn, const T& e)
{
	if (bn->rchild)
		return nullptr;
	bn->rchild = bn->insertAsRChild(e);
	//bn->rchild = new myBinNode<T>(e, bn);
	++m_size;
	updateHeightAbove(bn->rchild);
	return bn->rchild;
}

// ��ָ������������Ϊָ���ڵ������
template<typename T>
myBinNode<T>* myBinTree<T>::attachAsLChild(myBinNode<T>* bn, myBinTree<T>* &bt)
{
	if (bn->lchild)
		return nullptr;
	bn->lchild = bt->getRoot();
	bt->getRoot()->parent = bn;
	updateHeightAbove(bn->lchild);
	m_size += bt->size();

	// �ͷ�bt
	bt->m_pRoot = nullptr;
	bt->m_size = 0;
	bt = nullptr;
	return bn->lchild;
}

// ��ָ������������Ϊָ���ڵ���Һ���
template<typename T>
myBinNode<T>* myBinTree<T>::attachAsRChild(myBinNode<T>* bn, myBinTree<T>* &bt)
{
	if (bn->rchild)
		return nullptr;
	bn->rchild = bt->getRoot();
	bt->getRoot()->parent = bn;
	updateHeightAbove(bn->rchild);
	m_size += bt->size();

	// �ͷ�bt
	bt->m_pRoot = nullptr;
	bt->m_size = 0;
	bt = nullptr;
	return bn->lchild;
}

// ���½ڵ�ĸ߶�
template<typename T>
int myBinTree<T>::updateHeight(myBinNode<T>* bn)
{
	return bn->height = (1 + Max(stature(bn->lchild), stature(bn->rchild)));
}

// ���´˽ڵ����Ƚڵ�ĸ߶�(�����ɾ���ڵ�Ҫִ�и���)
template<typename T>
void myBinTree<T>::updateHeightAbove(myBinNode<T>* bn)
{
	while (bn)
	{
		updateHeight(bn);
		bn = bn->parent;
	}
}

// ɾ���ڵ�bn��������������ɾ���Ķ������ڵ������
template<typename T>
int myBinTree<T>::removeAt(myBinNode<T>* bn)
{
	int n = 0;
	if (bn == nullptr)
		return 0;
	n = 1 + removeAt(bn->lchild) + removeAt(bn->rchild);
	delete bn;
	return n;
}

// ɾ����bnΪ���ڵ������
template<typename T>
int myBinTree<T>::remove(myBinNode<T>* bn)
{
	if (bn != m_pRoot)
	{
		((bn->parent->lchild) == bn) ? (bn->parent->lchild) = nullptr : (bn->parent->rchild) = nullptr;// �����ڵ��Ӧ��\�Һ����ÿ�
	}
	myBinNode<T>* bp = bn->parent;
	int n = removeAt(bn);
	updateHeightAbove(bp);
	m_size -= n;
	return n;
}

// �������룬���ڵ�bn�������Ӷ������з��������Ȼ���γ�һ�������Ķ�����
template<typename T>
myBinTree<T>* myBinTree<T>::secede(myBinNode<T>* bn)
{
	if (bn != m_pRoot)
	{
		((bn->parent->lchild) == bn) ? (bn->parent->lchild) = nullptr : (bn->parent->rchild) = nullptr;
	}
	// ����height
	myBinNode<T>* bp = bn->parent;
	updateHeightAbove(bp);

	// ��װ���¶�����
	myBinTree<T>* bt = new myBinTree<T>();
	bt->m_pRoot = bn;
	bn->parent = nullptr;
	// ����size
	bt->m_size = bn->size();
	m_size -= bt->m_size;

	// �����������
	if (m_pRoot == bn)
		m_pRoot = nullptr;
	return bt;
}

// �������(�ݹ�汾:����׶�)
template<typename T>
void myBinTree<T>::travPre_R(myBinNode<T>* bn_r, void(*func)(T& bn))
{
	if (!bn_r) return;
	func(bn_r->data);
	travPre_R(bn_r->lchild, func);
	travPre_R(bn_r->rchild, func);
}

// �������(�ݹ�汾:����׶�)
template<typename T>
void myBinTree<T>::travIn_R(myBinNode<T>* bn_r, void(*func)(T& bn))
{
	if (!bn_r) return;
	travIn_R(bn_r->lchild, func);
	func(bn_r->data);
	travIn_R(bn_r->rchild, func);
}

// �������(�ݹ�汾:����׶�)        
template<typename T>
void myBinTree<T>::travPost_R(myBinNode<T>* bn_r, void(*func)(T& bn))
{
	if (!bn_r) return;
	travPost_R(bn_r->lchild, func);
	travPost_R(bn_r->rchild, func);
	func(bn_r->data);
}

// �����������߱���
template<typename T>
void myBinTree<T>::visitAlongLeftBranch(myBinNode<T>* bn, void(*func)(T& bn), stack<myBinNode<T>*> &s)
{
	while (bn)
	{
		func(bn->data);
		s.push(bn->rchild);		// �Һ�����ջ
		bn = bn->lchild;		// ��������ر���
	}
}

// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
template<typename T>
void myBinTree<T>::travPre_I(myBinNode<T>* bn_i, void(*func)(T& bn))
{
	stack<myBinNode<T>*> s;
	while (true)
	{
		visitAlongLeftBranch(bn_i, func, s);	// ��������ջ
		if (s.empty()) break;
		bn_i = s.top();
		s.pop();
	}
}

// �ӵ�ǰ�ڵ㿪ʼ���������֧������ջ
template<typename T>
void myBinTree<T>::goAlongLeftBranch(myBinNode<T>* bn, stack<myBinNode<T>*> &s)
{
	while (bn)
	{
		s.push(bn);
		bn = bn->lchild;
	}
}

// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
template<typename T>
void myBinTree<T>::travIn_I(myBinNode<T>* bn_i, void(*func)(T& bn))
{
	stack<myBinNode<T>*> s;
	while (true)
	{
		goAlongLeftBranch(bn_i, s);
		if (s.empty()) break;
		bn_i = s.top();
		s.pop();
		func(bn_i->data);
		bn_i = bn_i->rchild;
	}
}

// ����sջ���ڵ�Ϊ���������У��ҵ�������ɼ��ڵ�
template<typename T>
void myBinTree<T>::gotoHLVFL(stack<myBinNode<T>*> &s)
{
	while (myBinNode<T>* bn_i = s.top())
	{
		if (bn_i->lchild)
		{
			if (bn_i->rchild)
				s.push(bn_i->rchild);
			s.push(bn_i->lchild);
		}
		else// if (bn_i->rchild) �����жϣ���Ȼ�������������while���
		{
			s.push(bn_i->rchild);
		}
	}
	s.pop();// �Ƴ���ָ��
}

// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
template<typename T>
void myBinTree<T>::travPost_I(myBinNode<T>* bn_i, void(*func)(T& bn))
{
	stack<myBinNode<T>*> s;
	if (bn_i)
		s.push(bn_i);
	while (!s.empty())
	{
		if (s.top() != bn_i->parent)// ��ֹ�ٴα������ҽڵ�
			gotoHLVFL(s);
		bn_i = s.top();
		s.pop();
		func(bn_i->data);
	}
}

// ��α���
template<typename T>
void myBinTree<T>::travLevel(myBinNode<T>* bn_i, void(*func)(T& bn))
{
	queue<myBinNode<T>*> q;
	if (bn_i)
		q.push(bn_i);
	while (!q.empty())  // ���зǿ�
	{
		bn_i = q.front();
		q.pop();
		func(bn_i->data);
		if (bn_i->lchild)
			q.push(bn_i->lchild);
		if (bn_i->rchild)
			q.push(bn_i->rchild);
	}
}

