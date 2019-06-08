#ifndef _BTREE_H_
#define _BTREE_H_
#include <iostream>
#include <deque>
#define TT 2

template<typename T>
struct myBTnode{
	T keyNum;				/* ��ֵ */
	T* keyValue;			/* �洢��Կ������*/
	myBTnode** children;	/* �洢ָ���ӽڵ��ָ�������s */
	bool leaf;				/* ���ڵ���Ҷ��ʱΪtrue������Ϊfalse */
	myBTnode(bool il = true, T n = 0) :leaf(il), keyNum(n){}
};

template<typename T>
class myBtree
{

public:
	myBtree();		// ����
	~myBtree();		// ����
	myBTnode<T>* getRoot();// �õ����ڵ�

	myBTnode<T>* bTreeSearch(myBTnode<T>* x, int k, int& index);
	bool keyIsExist(int key);		// ���key�Ƿ����
	void printTree(myBTnode<T>* x);	// ��ӡ����Ϣ
	void bTreeInsert(int k);		// ����
	void bTreeDelete(int k);		// ɾ��


private:
	myBTnode<T>* root;	// ���ڵ�
	void deleteTree(myBTnode<T>* pNode);// ɾ��ָ�����ڵ����
	myBTnode<T>* alloactNode();			// Ϊ�ڵ�����ռ�
	void bTreeSplitChild(myBTnode<T>* x, int i);	// ��ֺ���
	void bTreeInsertNonfull(myBTnode<T>* x, int k);	// ����
	void deleteNode(myBTnode<T>* &node);			// ɾ��ָ���ڵ�
	void bTreeMergeChild(myBTnode<T>* x, int index);// �ϲ��ڵ�
	int bTreeFindPredecessor(myBTnode<T>* x); // ǰ���ؼ��� 
	int bTreeFindSuccessor(myBTnode<T>* x);   // ��̹ؼ��� 
	void bTreeDeleteRecursive(myBTnode<T>* x, int k);	// �ݹ�ɾ��

};

template<typename T>
myBtree<T>::myBtree()
{ 
	root = NULL;
}

template<typename T>
myBtree<T>::~myBtree()
{ 
	deleteTree(root); 
}
template<typename T>
myBTnode<T>* myBtree<T>::getRoot()
{ 
	return root; 
}



template<typename T>
void myBtree<T>::deleteTree(myBTnode<T>* pNode)
{
	if(pNode == NULL) return;
	else
	{
		if(!pNode->leaf)
		{
			for(int i=0; i<=pNode->keyNum; i++)
			{
				deleteTree(pNode->children[i]);
			}
		}
		delete pNode;
		pNode = NULL;
	}
}

template<typename T>
myBTnode<T>* myBtree<T>::alloactNode()
{
	myBTnode<T>* newNode = new myBTnode<T>();
	newNode->keyValue = new int[2*TT-1];
	newNode->children = new myBTnode<T>*[2*TT];
	for(int i=0; i<2*TT; i++)
		newNode->children[i] = NULL;
	return newNode;
}

/*
/* �ҵ���Ӧ�Ľڵ㷵�أ�����ͨ��index�����õõ��ڽڵ�x�е�λ�� 
*/
template<typename T>
myBTnode<T>* myBtree<T>::bTreeSearch(myBTnode<T>* x, int k, int& index)
{
	if(x == NULL) return NULL;
	else
	{
		int i=0;
		while(i<x->keyNum && k>x->keyValue[i])
		{
			i++;
		}
		if(i<x->keyNum && k==x->keyValue[i])
		{
			index = i;
			return x;
		} 			
		else
		{
			if(x->leaf)
				return NULL;
			else
				return bTreeSearch(x->children[i], k, index);
		} 
	}
}
template<typename T>
bool myBtree<T>::keyIsExist(int key)
{
	int index;
	if(bTreeSearch(root, key, index)==NULL) return false;
	return true;
}
template<typename T>
void myBtree<T>::printTree(myBTnode<T>* x)
{
	if(NULL == x) return;
	
	// �����ǰ�ڵ�����йؼ��� 
	std::cout << "[";
	for(int i=0; i<x->keyNum; i++) 
		std::cout << " " << x->keyValue[i];
	std::cout << " ]";
	
	// �ݹ������������
	for(int i=0; i<=x->keyNum; i++)
		printTree(x->children[i]); 
		
	std::cout << std::endl;
}

template<typename T>
void myBtree<T>::bTreeSplitChild(myBTnode<T>* x, int index)
{
	myBTnode<T>* z = alloactNode();
	myBTnode<T>* y = x->children[index];
	z->leaf = y->leaf;
	z->keyNum = TT-1;
	for(int i=0; i<TT-1; i++)
	{ // ��ȡ���ιؼ�����Ϊ���ӽڵ�Ĺؼ��� 
		z->keyValue[i] = y->keyValue[TT+i];
	}
	if(!y->leaf)
	{
		for(int i=0; i<TT; i++)
		{
			z->children[i] = y->children[TT+i];
		}
	}
	
	y->keyNum = TT-1; // ����ԭ�����Ĺؼ��ָ���
	// �����ڵ�x�У�λ��index������йؼ��ֺ���������һλ 
	for(int i=x->keyNum; i>index; i--)
	{
		x->children[i+1] = x->children[i];
		x->keyValue[i] = x->keyValue[i-1]; 
	} 
	x->keyNum++;
	x->children[index+1] = z; // �洢������
	x->keyValue[index] = y->keyValue[TT-1]; // ���ڵ��м�ֵ���������ڵ� 
}
template<typename T>
void myBtree<T>::bTreeInsertNonfull(myBTnode<T>* x, int k)
{
	int i=x->keyNum-1;
	if(x->leaf)
	{
		for(; i>=0&&k<x->keyValue[i]; i--)
		{
			x->keyValue[i+1] = x->keyValue[i];
		}
		i++;
		(x->keyNum)++;
		x->keyValue[i] = k;
	}
	else
	{ 
		while(i>=0&&k<x->keyValue[i])
			i--;
		i++;
		if(x->children[i]->keyNum == 2*TT-1)
		{
			bTreeSplitChild(x, i);
			if(k>x->keyValue[i]) i++; 
		}
		bTreeInsertNonfull(x->children[i], k);
	}
}
template<typename T>
void myBtree<T>::bTreeInsert(int k)
{
	if(!keyIsExist(k))
	{
		if(root == NULL)
		{ // ����Ϊ���� 
			root = alloactNode();
		}
		if(root->keyNum == 2*TT-1)
		{ // ���ڵ����������¸������Ѹ��ڵ� 
			myBTnode<T>* newRoot = alloactNode();
			newRoot->children[0] = root;
			newRoot->leaf = false;
			bTreeSplitChild(newRoot, 0);
			root = newRoot; // ���¸��ڵ� 
		}
		bTreeInsertNonfull(root, k);
	} 
}
template<typename T>
void myBtree<T>::deleteNode(myBTnode<T>* &node)
{
	if(node != NULL){
		delete node;
		node = NULL;
	}
}
template<typename T>
void myBtree<T>::bTreeMergeChild(myBTnode<T>* x, int index)
{
	myBTnode<T>* xchild1 = x->children[index];
	myBTnode<T>* xchild2 = x->children[index+1];
	xchild1->keyValue[TT-1] = x->keyValue[index]; 
	for(int j=0; j<TT-1; j++)
		xchild1->keyValue[TT+j] = xchild2->keyValue[j];
	if(!xchild1->leaf)
	{ // ����ڵ㲻��Ҷ�ڵ㣬����Ҫ�ƶ����� 
		for(int j=0; j<TT; j++)
		{
			xchild1->children[j+TT] = xchild2->children[j];
		} 
	}
	xchild1->keyNum = 2*TT-1;
	
	// �ָ����ڵ㣺ɾ����һ���ؼ��֣�index֮��Ĺؼ��ּ�ָ����Ҫǰ�� 
	x->keyNum--;
	for(int j=index; j<=x->keyNum; j++)
	{
		x->keyValue[j] = x->keyValue[j+1];
		x->children[j+1] = x->children[j+2];
	}
	deleteNode(xchild2);
	if(x->keyNum == 0) deleteNode(x);
}
template<typename T>
int myBtree<T>::bTreeFindPredecessor(myBTnode<T>* x)
{
	while(!x->leaf){
		x = x->children[x->keyNum];
	}
	return x->keyValue[x->keyNum-1];
} 
template<typename T>
int myBtree<T>::bTreeFindSuccessor(myBTnode<T>* x)
{
	while(!x->leaf){
		x = x->children[0];
	}
	return x->keyValue[0];
} 
template<typename T>
void myBtree<T>::bTreeDeleteRecursive(myBTnode<T>* x, int k)
{
	int index=0;
	while(index<x->keyNum && k>x->keyValue[index])
		index++;
	if(k==x->keyValue[index])
	{ // �ؼ����ڽڵ�x 
		if(x->leaf)
		{ // case 1
			for(int j=index; j<x->keyNum; j++)
				x->keyValue[j] = x->keyValue[j+1];
			x->keyNum--;
			std::cout << "aaa" << std::endl;
			return;
		} 
		else
		{ // �ڵ�xΪ�ڲ��ڵ� 
			myBTnode<T>* y = x->children[index]; // �ڵ�x��ǰ��k���ӽڵ� 
			myBTnode<T>* z = x->children[index+1]; // �ڵ�x�к���k���ӽڵ� 
			
			if(y->keyNum >= TT)
			{ // case 2a: �ڵ�y���ٰ���TT���ؼ��� 
				int prevKey = bTreeFindPredecessor(y); // ���key��ǰ���ؼ���
				 bTreeDeleteRecursive(y, prevKey);
				 x->keyValue[index] = prevKey;
				 return;
			} 
			else if(z->keyNum >= TT)
			{ // case 2b: �ڵ�z���ٰ���TT���ؼ��� 
				int nextKey = bTreeFindSuccessor(z); // ���key�ĺ����ؼ���
				bTreeDeleteRecursive(z, nextKey);
				x->keyValue[index] = nextKey;
				return; 
			}
			else{ // case 2c: �ڵ�y��z��ֻ����TT-1���ؼ��� 
				bTreeMergeChild(x, index);
				bTreeDeleteRecursive(y, k);
			}
		}
	}
	else{ // �ؼ���k���ڽڵ�x�У���x->children[index]Ϊ����k�������ĸ��ڵ�
		myBTnode<T>* xchild = x->children[index]; // ����k���������ڵ�
		if(xchild->keyNum == TT-1){ // ֻ��TT-1���ؼ���
		 	myBTnode<T>* pLeft = index>0? x->children[index-1]:NULL; // ���ֵܽڵ�
			myBTnode<T>* pRight = index<x->keyNum? x->children[index+1]:NULL; // ���ֵܽڵ�  
			if(pLeft && pLeft->keyNum>=TT){ // case 3a: ���ֵܽڵ��еĹؼ�����������TT	
				// ���ڵ���i-1���ؼ����½����ϲ��ڵ�
				for(int j=xchild->keyNum; j>0; j--){
					xchild->keyValue[j] = xchild->keyValue[j-1];
				} 
				xchild->keyValue[0] = x->keyValue[index-1];
				if(!pLeft->leaf){
					// �����ֵܽڵ��к��ʵĺ���ָ����ֲ��xchild 
					for(int j=xchild->keyNum+1; j>0; j--){
						xchild->children[j] = xchild->children[j-1];
					}
					xchild->children[0] = pLeft->children[pLeft->keyNum];
				}
				xchild->keyNum++;
				x->keyValue[index] = pLeft->keyValue[pLeft->keyNum-1]; // ���ֵܽڵ��е����ؼ����������丸�ڵ���
				pLeft->keyNum--; 
			}
			else if(pRight && pRight->keyNum>=TT){ // case 3a: ���ֵܽڵ��еĹؼ�����������TT	
				// ���ڵ���i���ؼ����½����ϲ��ڵ� 
				xchild->keyValue[xchild->keyNum] = x->keyValue[index];
				xchild->keyNum++;
				x->keyValue[index] = pRight->keyValue[0]; // ���ֵܽڵ��е���С�ؼ������������ڵ�x
				pRight->keyNum--;
				for(int j=0; j<pRight->keyNum; j++){
					pRight->keyValue[j] = pRight->keyValue[j+1];
				} 
				if(!pRight->leaf){
					// �����ֵܽڵ��к��ʵĺ���ָ����ֲ��xchild 
					xchild->children[xchild->keyNum] = pRight->children[0];
					for(int j=0; j<=pRight->keyNum; j++){
						pRight->children[j] = pRight->children[j+1];
					} 
				}
			} 
			else if(pLeft){ // ���ֵܽڵ�ǿգ������ֵܺϲ� 
				bTreeMergeChild(x, index-1);
				xchild = pLeft;
			}
			else if(pRight){ // ���ֵܽڵ�ǿգ������ֵܺϲ� 
				bTreeMergeChild(x, index-1);
			}
		} 	
		bTreeDeleteRecursive(xchild, k); 
	} 
}	
template<typename T>
void myBtree<T>::bTreeDelete(int k){
	if(keyIsExist(k)){
		if(root->keyNum == 1){
			if(root->leaf)
				deleteTree(root);
			else{ // case 3b: ���ݲ�����򣬵����ڵ�ֻ��һ���ؼ���ʱ��ֻ������2������
			 	myBTnode<T>* rchild1 = root->children[0];
				myBTnode<T>* rchild2 = root->children[1];
				if(rchild1->keyNum == TT-1 && rchild2->keyNum == TT-1){
					bTreeMergeChild(root, 0);
					root = rchild1;
				} 	
			}
		}
		bTreeDeleteRecursive(root, k);
	}
}


#endif