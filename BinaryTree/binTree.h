#ifndef _BINTREE_H_
#define _BINTREE_H_
#pragma once

#include "binNode.h"
#include <stack>
#include <queue>
using namespace std;
#define  Max(a,b) (((a)>=(b))?(a):(b))


template<typename T>
class binTree
{
protected:
	// ��Ա����
	int m_size;				// �������Ĺ�ģ
	binNode<T>* m_pRoot;	// ���ĸ��ڵ�ָ��
public:
	// ���캯��
	binTree();
	// ��������
	~binTree();
	// ��Ա����
	int size();		// ���ض������Ĺ�ģ
	bool empty();	// �ж϶������Ƿ�Ϊ��
	binNode<T>* getRoot();	// ���ظ��ڵ��ָ��
	binNode<T>* insertAsRoot(const T& e);	// ��ָ��Ԫ�ز�����Ϊ���ڵ�
	binNode<T>* insertAsLChild(binNode<T>* bn, const T& e);		// ��ָ��Ԫ�ز�����Ϊָ���ڵ������
	binNode<T>* insertAsRChild(binNode<T>* bn, const T& e);		// ��ָ��Ԫ�ز�����Ϊָ���ڵ������
	binNode<T>* attachAsLChild(binNode<T>* bn, binTree<T>* &bt);	// ��ָ������������Ϊָ���ڵ������
	binNode<T>* attachAsRChild(binNode<T>* bn, binTree<T>* &bt);	// ��ָ������������Ϊָ���ڵ���Һ���
	int updateHeight(binNode<T>* bn);			// ���½ڵ�ĸ߶�
	void updateHeightAbove(binNode<T>* bn);		// ���´˽ڵ����Ƚڵ�ĸ߶�(�����ɾ���ڵ�Ҫִ�и���)
	int removeAt(binNode<T>* bn);       // ɾ���ڵ�bn��������������ɾ���Ķ������ڵ������
	int remove(binNode<T>* bn);			// ɾ����bnΪ���ڵ������
	binTree<T>* secede(binNode<T>* bn);			// �������룬���ڵ�bn�������Ӷ������з��������Ȼ���γ�һ�������Ķ�����

	void travPre_R(binNode<T>* bn_r, void(*func)(T& bn));		// �������(�ݹ�汾:����׶�)
	void travIn_R(binNode<T>* bn_r, void(*func)(T& bn));		// �������(�ݹ�汾:����׶�)
	void travPost_R(binNode<T>* bn_r, void(*func)(T& bn));		// �������(�ݹ�汾:����׶�)

	void visitAlongLeftBranch(binNode<T>* bn, void(*func)(T& bn), stack<binNode<T>*> &s);  // �����������߱���
	void travPre_I(binNode<T>* bn_i, void(*func)(T& bn));			// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
	void goAlongLeftBranch(binNode<T>* bn, stack<binNode<T>*> &s);	// �ӵ�ǰ�ڵ㿪ʼ���������֧������ջ
	void travIn_I(binNode<T>* bn_i, void(*func)(T& bn));			// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
	void gotoHLVFL(stack<binNode<T>*> &s);							// ����sջ���ڵ�Ϊ���������У��ҵ�������ɼ��ڵ�
	void travPost_I(binNode<T>* bn_i, void(*func)(T& bn));			// �������(�����汾:ʱ�䡢�ռ临�Ӷȵ�)
	void travLevel(binNode<T>* bn_i, void(*func)(T& bn));			// ��α���
};
#endif // !_BINTREE_H_


