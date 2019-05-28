#ifndef _MYTRIETREE_H_
#define _MYTRIETREE_H_
/************************************************************************/
/* 
�����ڵ�֮������нڵ㶼�洢һ���ַ����Ӹ��ڵ㵽ĳһ���ڵ�A��·���Ͼ����������ַ����ɽڵ�A��Ӧ���ַ�����
����ͬһ���ڵ�Ľڵ�洢���ַ���ͬ����Ҫ���ڴ����ַ�������ǰ׺��ص����⡣
�ŵ��������ַ����Ĺ���ǰ׺�����ٲ�ѯʱ�䣬����޶ȵؼ�����ν���ַ����Ƚϣ���ѯЧ�ʱȹ�ϣ���ߡ�
ȱ�������ϵͳ�д��ڴ����ַ�������Щ�ַ�������û�й���ǰ׺������Ӧ��trie�����ǳ������ڴ档
                                                                  */
/************************************************************************/
using namespace std;
#define NUM_CHARS 26
// �ڵ�����
struct myTrieNode
{
	myTrieNode() :count(0)
	{
		memset(branches, 0, sizeof(branches));
	}
	int count;	// ����ǰ�ڵ�λ�õ��ַ����ĸ���
	myTrieNode *branches[NUM_CHARS];// [a-z]����Сд�Ķ�Ӧ�±�[0-25]
};

class myTrieTree{
public:
	myTrieTree();		// ���캯��
	~myTrieTree();	// ��������
	void insert(const string& str);// �����ַ���
	bool search(const string& str);// ����Ƿ�����ַ���
protected:
	void deleteNode(myTrieNode *node);	// �����ڴ�
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
		if (recNode->branches[str[i] - 'a'] == nullptr)	// �����ڸ��ַ�
		{
			myTrieNode *tmp = new myTrieNode;			// �½���֧
			recNode->branches[str[i] - 'a'] = tmp;
			recNode = tmp;
		}
		else
		{
			recNode = recNode->branches[str[i] - 'a'];	// �Ƶ���һ��ڵ�
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
		if (recNode->branches[str[i] - 'a'] == nullptr)	// �жϵ�ǰ�ַ�
			return false;
		recNode = recNode->branches[str[i] - 'a'];		// �Ƶ���һ��ڵ�
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