#ifndef _MYBINARYSEARCHTREE_H_
#define _MYBINARYSEARCHTREE_H_
#pragma  once

// �Զ���ڵ�
template <typename T>
struct myBinNode
{
	myBinNode() :data(NULL), left(nullptr), right(nullptr){}
	T data;
	myBinNode<T>* left;
	myBinNode<T>* right;
};

// ����������
template <typename T>
class myBinarySearchTree
{
protected:
	myBinNode<T> *root;	// �����
public:
	// ����
	myBinarySearchTree();
	// ����
	~myBinarySearchTree();

	myBinNode<T>* getRoot();			// �õ������
	void insert(const T& value);		// ����ڵ�
	void remove_node(const T& value);	// ɾ���ڵ�

	// ����
	void pre_order_traversal1(myBinNode<T>* node);	// �������(�ݹ�ʵ��)
	void pre_order_traversal2(myBinNode<T>* node);	// �������(����ʵ��)
	void in_order_traversal1(myBinNode<T>* node);	// �������(�ݹ�ʵ��)
	void in_order_traversal2(myBinNode<T>* node);	// �������(����ʵ��)
	void post_order_traversal1(myBinNode<T>* node);	// ��������(�ݹ�ʵ��)
	void post_order_traversal2(myBinNode<T>* node);	// �������(����ʵ��)
	void level_traversal(myBinNode<T>* node);		// ��α���

	myBinNode<T>* search_for_node1(myBinNode<T>* sub_root, const T&  target); // ����Ŀ��ڵ�(�ݹ�ʵ��)
	myBinNode<T>* search_for_node2(myBinNode<T>* sub_root, const T&  target); // ����Ŀ��ڵ�(����ʵ��)

protected:
	void deleteSubtree(myBinNode<T> *node);	// ɾ����Ϊ�ڵ������
};


#endif