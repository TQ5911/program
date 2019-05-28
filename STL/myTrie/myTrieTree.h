#ifndef _MYTRIETREE_H_
#define _MYTRIETREE_H_
/************************************************************************/
/* 
除根节点之外的所有节点都存储一个字符，从根节点到某一个节点A，路径上经过的所有字符构成节点A对应的字符串。
具有同一父节点的节点存储的字符不同。主要用于处理字符串公共前缀相关的问题。
优点是利用字符串的公共前缀来减少查询时间，最大限度地减少无谓的字符串比较，查询效率比哈希树高。
缺点是如果系统中存在大量字符串且这些字符串基本没有公共前缀，则相应的trie树将非常消耗内存。
                                                                  */
/************************************************************************/
using namespace std;
#define NUM_CHARS 26
// 节点类型
struct myTrieNode
{
	myTrieNode() :count(0)
	{
		memset(branches, 0, sizeof(branches));
	}
	int count;	// 到当前节点位置的字符串的个数
	myTrieNode *branches[NUM_CHARS];// [a-z]都是小写的对应下标[0-25]
};

class myTrieTree{
public:
	myTrieTree();		// 构造函数
	~myTrieTree();	// 析构函数
	void insert(const string& str);// 插入字符串
	bool search(const string& str);// 检测是否存在字符串
protected:
	void deleteNode(myTrieNode *node);	// 清理内存
private:
	myTrieNode *root;
};

myTrieTree::myTrieTree()
{
	root = new myTrieNode;
}

myTrieTree::~myTrieTree()
{
	deleteNode(root);
	root = nullptr;
}

void myTrieTree::insert(const string& str)
{
	int len = str.length();
	if (len <= 0) return;

	myTrieNode *recNode = root;
	for (int i = 0; i < len; i++)
	{
		if (recNode->branches[str[i] - 'a'] == nullptr)	// 不存在该字符
		{
			myTrieNode *tmp = new myTrieNode;			// 新建分支
			recNode->branches[str[i] - 'a'] = tmp;
			recNode = tmp;
		}
		else
		{
			recNode = recNode->branches[str[i] - 'a'];	// 移到下一层节点
		}
	}
	recNode->count++;
}

bool myTrieTree::search(const string& str)
{
	int len = str.length();
	if (len <= 0) return true;
	myTrieNode *recNode = root;
	for (int i = 0; i < len; i++)
	{
		if (recNode->branches[str[i] - 'a'] == nullptr)	// 判断当前字符
			return false;
		recNode = recNode->branches[str[i] - 'a'];		// 移到下一层节点
	}
	return (recNode->count > 0) ? true : false;

	return false;
}

void myTrieTree::deleteNode(myTrieNode *node)
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		if (node->branches[i] != nullptr)
		{
			deleteNode(node->branches[i]);
		}
	}
	delete node;
}

#endif