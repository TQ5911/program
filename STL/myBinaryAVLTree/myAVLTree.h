#ifndef _AVLTREE_H_
#define _AVLTREE_H_
#pragma once

template <typename T>
struct AVLTreeNode
{
	AVLTreeNode(const T& tmpdata = NULL) :data(tmpdata), height(0), left(nullptr), right(nullptr){}
	T data;
	int height;
	AVLTreeNode<T>* left;
	AVLTreeNode<T>* right;
};

// ����ƽ����
template <typename T>
class myAVLTree
{
protected:
	AVLTreeNode<T>* root;
public:
	myAVLTree();	// ���캯��
	~myAVLTree();	// ��������

	AVLTreeNode<T>* getRoot();			// �õ����ڵ�
	int getHeight(AVLTreeNode<T>* node);// ��ȡ�����ĸ߶�
	void setHeight(AVLTreeNode<T>* subroot, const T& subtreeHeight);	// ���������ĸ߶�

	AVLTreeNode<T>* SingleRightRotate(AVLTreeNode<T>* subroot);			// ����LL��ʹ�õ�����ת
	AVLTreeNode<T>* DoubleRightRotate(AVLTreeNode<T>* subroot);			// ����LR, ʹ��˫����ת
	AVLTreeNode<T>* SingleLeftRotate(AVLTreeNode<T>* subroot);			// ����RR��ʹ�õ�����ת
	AVLTreeNode<T>* DoubleLeftRotate(AVLTreeNode<T>* subroot);			// ����RL����ʹ��˫����ת

	AVLTreeNode<T>* insert(AVLTreeNode<T>* subroot, const T& value);	// ���������ڵ�
	void pre_order_traversal(AVLTreeNode<T>* node);		// ����: �ݹ�ʵ��
	void in_order_traversal(AVLTreeNode<T>* node);		// ����: �ݹ�ʵ��
	AVLTreeNode<T>* search_for_node(AVLTreeNode<T>* sub_root, const T& target);// ����Ŀ��ڵ㣺�ǵݹ�ʵ��
protected:
	void deleteSubtree(AVLTreeNode<T>* node);// ɾ����Ϊ�ڵ������
};
#endif