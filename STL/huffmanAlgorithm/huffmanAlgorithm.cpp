#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 节点类型
struct Node{
	Node(int tmpFreq, Node* pLeft = nullptr, Node* pRight = nullptr) :freq(tmpFreq), left(pLeft), right(pRight){}
	int freq;	// 频率
	Node* left;
	Node* right;
};

// 比较函数(freq小优先级大)
struct cmpNode{
	bool operator()(const Node* a, const Node* b)
	{
		return a->freq >= b->freq; 
	}
};

// 合并节点
Node* mergeTree(Node* &small1, Node* &small2)
{
	Node* newNode = new Node(small1->freq + small2->freq, small1, small2);
	return newNode;
}

void level_traversal(Node* node)
{
	Node* curNode = node;
	queue<Node*> q;
	if (curNode != nullptr) q.push(curNode);
	while (!q.empty())// 层次遍历
	{
		curNode = q.front();
		q.pop();
		cout << curNode->freq << " ";
		if (curNode->left != nullptr) q.push(curNode->left);
		if (curNode->right != nullptr) q.push(curNode->right);
	}
}

int main()
{
	int n, freq;
	Node *less1, *less2, *root;

	cin >> n;			// 5
	// 构建最小堆
	priority_queue<Node*, vector<Node*>, cmpNode> Q;
	for (int i = 0; i < n; i++)
	{
		cin >> freq;// 3 4 5 6 8 五个数字任意顺序输入
		Node* newNode = new Node(freq);
		Q.push(newNode);
	}
	// 34568()
	while (Q.size() > 1)
	{
		less1 = Q.top();
		Q.pop();
		less2 = Q.top();
		Q.pop();
		root = mergeTree(less1, less2);
		Q.push(root);
	}
	// 生成的二叉树
	/*
				26					-- 1
		11				15			-- 2
	 5		6		 7		8		-- 3
				   3   4			-- 4
	带权路径长度(WPL):(5 + 6 + 8) * 3 + (3 + 4) * 4 = 85
	*/
	cout << endl;
	level_traversal(root);
	cout << endl << "END" << endl;

	return 0;
}
