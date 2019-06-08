#ifndef _BTREE_H_
#define _BTREE_H_
#include <iostream>
#include <deque>
#define TT 2

template<typename T>
struct myBTnode{
	T keyNum;				/* 键值 */
	T* keyValue;			/* 存储密钥的数组*/
	myBTnode** children;	/* 存储指向子节点的指针的数组s */
	bool leaf;				/* 当节点是叶子时为true，否则为false */
	myBTnode(bool il = true, T n = 0) :leaf(il), keyNum(n){}
};

template<typename T>
class myBtree
{

public:
	myBtree();		// 构造
	~myBtree();		// 析构
	myBTnode<T>* getRoot();// 得到根节点

	myBTnode<T>* bTreeSearch(myBTnode<T>* x, int k, int& index);
	bool keyIsExist(int key);		// 检查key是否存在
	void printTree(myBTnode<T>* x);	// 打印树信息
	void bTreeInsert(int k);		// 插入
	void bTreeDelete(int k);		// 删除


private:
	myBTnode<T>* root;	// 根节点
	void deleteTree(myBTnode<T>* pNode);// 删除指定根节点的树
	myBTnode<T>* alloactNode();			// 为节点申请空间
	void bTreeSplitChild(myBTnode<T>* x, int i);	// 拆分孩子
	void bTreeInsertNonfull(myBTnode<T>* x, int k);	// 插入
	void deleteNode(myBTnode<T>* &node);			// 删除指定节点
	void bTreeMergeChild(myBTnode<T>* x, int index);// 合并节点
	int bTreeFindPredecessor(myBTnode<T>* x); // 前驱关键字 
	int bTreeFindSuccessor(myBTnode<T>* x);   // 后继关键字 
	void bTreeDeleteRecursive(myBTnode<T>* x, int k);	// 递归删除

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
/* 找到对应的节点返回，并且通过index传引用得到在节点x中的位置 
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
	
	// 输出当前节点的所有关键字 
	std::cout << "[";
	for(int i=0; i<x->keyNum; i++) 
		std::cout << " " << x->keyValue[i];
	std::cout << " ]";
	
	// 递归输出所有子树
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
	{ // 截取后半段关键字作为新子节点的关键字 
		z->keyValue[i] = y->keyValue[TT+i];
	}
	if(!y->leaf)
	{
		for(int i=0; i<TT; i++)
		{
			z->children[i] = y->children[TT+i];
		}
	}
	
	y->keyNum = TT-1; // 更新原子树的关键字个数
	// 将父节点x中，位于index后的所有关键字和子树后移一位 
	for(int i=x->keyNum; i>index; i--)
	{
		x->children[i+1] = x->children[i];
		x->keyValue[i] = x->keyValue[i-1]; 
	} 
	x->keyNum++;
	x->children[index+1] = z; // 存储新子树
	x->keyValue[index] = y->keyValue[TT-1]; // 将节点中间值提升到父节点 
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
		{ // 假如为空树 
			root = alloactNode();
		}
		if(root->keyNum == 2*TT-1)
		{ // 根节点满，生成新根，分裂根节点 
			myBTnode<T>* newRoot = alloactNode();
			newRoot->children[0] = root;
			newRoot->leaf = false;
			bTreeSplitChild(newRoot, 0);
			root = newRoot; // 更新根节点 
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
	{ // 假如节点不是叶节点，则需要移动孩子 
		for(int j=0; j<TT; j++)
		{
			xchild1->children[j+TT] = xchild2->children[j];
		} 
	}
	xchild1->keyNum = 2*TT-1;
	
	// 恢复父节点：删除了一个关键字，index之后的关键字及指针需要前移 
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
	{ // 关键字在节点x 
		if(x->leaf)
		{ // case 1
			for(int j=index; j<x->keyNum; j++)
				x->keyValue[j] = x->keyValue[j+1];
			x->keyNum--;
			std::cout << "aaa" << std::endl;
			return;
		} 
		else
		{ // 节点x为内部节点 
			myBTnode<T>* y = x->children[index]; // 节点x中前于k的子节点 
			myBTnode<T>* z = x->children[index+1]; // 节点x中后于k的子节点 
			
			if(y->keyNum >= TT)
			{ // case 2a: 节点y至少包含TT个关键字 
				int prevKey = bTreeFindPredecessor(y); // 获得key的前驱关键字
				 bTreeDeleteRecursive(y, prevKey);
				 x->keyValue[index] = prevKey;
				 return;
			} 
			else if(z->keyNum >= TT)
			{ // case 2b: 节点z至少包含TT个关键字 
				int nextKey = bTreeFindSuccessor(z); // 获得key的后驱关键字
				bTreeDeleteRecursive(z, nextKey);
				x->keyValue[index] = nextKey;
				return; 
			}
			else{ // case 2c: 节点y和z都只包含TT-1个关键字 
				bTreeMergeChild(x, index);
				bTreeDeleteRecursive(y, k);
			}
		}
	}
	else{ // 关键字k不在节点x中，则x->children[index]为包含k的子树的根节点
		myBTnode<T>* xchild = x->children[index]; // 包含k的子树根节点
		if(xchild->keyNum == TT-1){ // 只有TT-1个关键字
		 	myBTnode<T>* pLeft = index>0? x->children[index-1]:NULL; // 左兄弟节点
			myBTnode<T>* pRight = index<x->keyNum? x->children[index+1]:NULL; // 右兄弟节点  
			if(pLeft && pLeft->keyNum>=TT){ // case 3a: 左兄弟节点中的关键字数不少于TT	
				// 父节点中i-1个关键字下降至合并节点
				for(int j=xchild->keyNum; j>0; j--){
					xchild->keyValue[j] = xchild->keyValue[j-1];
				} 
				xchild->keyValue[0] = x->keyValue[index-1];
				if(!pLeft->leaf){
					// 将左兄弟节点中合适的孩子指针移植到xchild 
					for(int j=xchild->keyNum+1; j>0; j--){
						xchild->children[j] = xchild->children[j-1];
					}
					xchild->children[0] = pLeft->children[pLeft->keyNum];
				}
				xchild->keyNum++;
				x->keyValue[index] = pLeft->keyValue[pLeft->keyNum-1]; // 左兄弟节点中的最大关键字上升到其父节点中
				pLeft->keyNum--; 
			}
			else if(pRight && pRight->keyNum>=TT){ // case 3a: 右兄弟节点中的关键字数不少于TT	
				// 父节点中i个关键字下降至合并节点 
				xchild->keyValue[xchild->keyNum] = x->keyValue[index];
				xchild->keyNum++;
				x->keyValue[index] = pRight->keyValue[0]; // 右兄弟节点中的最小关键字上升至父节点x
				pRight->keyNum--;
				for(int j=0; j<pRight->keyNum; j++){
					pRight->keyValue[j] = pRight->keyValue[j+1];
				} 
				if(!pRight->leaf){
					// 将右兄弟节点中合适的孩子指针移植到xchild 
					xchild->children[xchild->keyNum] = pRight->children[0];
					for(int j=0; j<=pRight->keyNum; j++){
						pRight->children[j] = pRight->children[j+1];
					} 
				}
			} 
			else if(pLeft){ // 左兄弟节点非空：与左兄弟合并 
				bTreeMergeChild(x, index-1);
				xchild = pLeft;
			}
			else if(pRight){ // 右兄弟节点非空：与右兄弟合并 
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
			else{ // case 3b: 根据插入规则，当父节点只有一个关键字时，只可能有2个孩子
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