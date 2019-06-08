#ifndef _BINTREE_H_
#define _BINTREE_H_
#pragma once

#include "myBinNode.h"
#include <stack>
#include <queue>
using namespace std;
#define  Max(a,b) (((a)>=(b))?(a):(b))


template<typename T>
class myBinTree
{
protected:
	// ��Ա����
	int m_size;				// �������Ĺ�ģ
	myBinNode<T>* m_pRoot;	// ���ĸ��ڵ�ָ��
public:
	// ���캯��
	myBinTree();
	// ��������
	~myBinTree();
	// ��Ա����
	int size();		// ���ض������Ĺ�ģ
	bool empty();	// �ж϶������Ƿ�Ϊ��
	myBinNode<T>* getRoot();	// ���ظ��ڵ��ָ��
	myBinNode<T>* insertAsRoot(const T& e);	// ��ָ��Ԫ�ز�����Ϊ���ڵ�
	myBinNode<T>* insertAsLChild(myBinNode<T>* bn, const T& e);		// ��ָ��Ԫ�ز�����Ϊָ���ڵ������
	myBinNode<T>* insertAsRChild(myBinNode<T>* bn, const T& e);		// ��ָ��Ԫ�ز�����Ϊָ���ڵ������
	myBinNode<T>* attachAsLChild(myBinNode<T>* bn, myBinTree<T>* &bt);	// ��ָ������������Ϊָ���ڵ������
	myBinNode<T>* attachAsRChild(myBinNode<T>* bn, myBinTree<T>* &bt);	// ��ָ������������Ϊָ���ڵ���Һ���
	int updateHeight(myBinNode<T>* bn);			// ���½ڵ�ĸ߶�
	void updateHeightAbove(myBinNode<T>* bn);		// ���´˽ڵ����Ƚڵ�ĸ߶�(�����ɾ���ڵ�Ҫִ�и���)
	int removeAt(myBinNode<T>* bn);       // ɾ���ڵ�bn��������������ɾ���Ķ������ڵ������
	int remove(myBinNode<T>* bn);			// ɾ����bnΪ���ڵ������
	myBinTree<T>* secede(myBinNode<T>* bn);			// �������룬���ڵ�bn�������Ӷ������з��������Ȼ���γ�һ�������Ķ�����

	void travPre_R(myBinNode<T>* bn_r, void(*func)(T& bn));		// �������(�ݹ�汾:����׶�)
	void travIn_R(myBinNode<T>* bn_r, void(*func)(T& bn));		// �������(�ݹ�汾:����׶�)
	void travPost_R(myBinNode<T>* bn_r, void(*func)(T& bn));		// �������(�ݹ�汾:����׶�)

	void visitAlongLeftBranch(myBinNode<T>* bn, void(*func)(T& bn), stack<myBinNode<T>*> &s);  // �����������߱���
	void travPre_I(myBinNode<T>* bn_i, void(*func)(T& bn));			// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
	void goAlongLeftBranch(myBinNode<T>* bn, stack<myBinNode<T>*> &s);	// �ӵ�ǰ�ڵ㿪ʼ���������֧������ջ
	void travIn_I(myBinNode<T>* bn_i, void(*func)(T& bn));			// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
	void gotoHLVFL(stack<myBinNode<T>*> &s);							// ����sջ���ڵ�Ϊ���������У��ҵ�������ɼ��ڵ�
	void travPost_I(myBinNode<T>* bn_i, void(*func)(T& bn));			// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
	void travLevel(myBinNode<T>* bn_i, void(*func)(T& bn));			// ��α���
};
#endif // !_BINTREE_H_


