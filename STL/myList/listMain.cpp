#include "myList.h"
#include "myList.cpp"
#include <iostream>

template<typename T>
void printfFunc(T& data)
{
	cout << data << " ";
}
template<typename T>
void add(T& data)
{
	cout << ++data << " ";
}
typedef void(*pFun)(int& data);
typedef void(*pAdd)(int& data);

int main()
{
	myList<int> mylist;
	mylist.insertAsFirst(2);// 2
	mylist.insert(1, 1);	// 21
	myListNode<int>* pp = mylist.insert(2, 3);	// 213
	mylist.insertAsLast(4);	// 2134
	mylist.insertAsSucc(pp, 5);		// 21354
	mylist.insertAsPred(pp, 6);	// 216354
	mylist.insert(6, 7);	// 2163547
	mylist.insert(7, 0);	// 21635470
	mylist.display();

	mylist.sort(mylist.first(), mylist.size(), 2);
	mylist.display();

	myList<int> copyMylist = mylist;

	myListNode<int>* p = mylist.find(1, 3, mylist.last());
	if (p != nullptr)
	{
		cout << p->data << endl;
	}
	p = mylist.find(1);
	if (p != nullptr)
	{
		cout << p->data << endl;
	}
	p = mylist.search(0, 3, mylist.last());
	if (p != nullptr)
	{
		cout << p->data << endl;
	}

	cout << mylist.remove(mylist.first()) << endl;
	cout << mylist.remove(mylist.last()) << endl; // 26354
	mylist.display();

	mylist.insert(1, 3);	// 236354
	mylist.insert(6, 2);	// 2363547
	mylist.display();

	mylist.deduplicate();
	mylist.display();
	mylist.clear();

	mylist.insert(0, 1);
	mylist.insert(0, 1);
	//mylist.uniquify();
	//mylist.display();
	pFun pfun = printfFunc;
	//mylist.traverse(printfFunc);
	//mylist.traverse(pfun);
	//mylist.traverse(add);
	//mylist.display();

	mylist.traverse<pFun>(pfun);

	myList<int>* mylist1 = new myList<int>();

	//int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	//std::initializer_list<int> li1(arr, arr + 8);
	std::initializer_list<int> li = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	myList<int>* mylist2 = new myList<int>(li);

	int tmpSize = mylist2->size();
	int num = 11;
	myList<int>* mylist3 = new myList<int>(mylist2->first(), num = (num > tmpSize) ? tmpSize : num);
	
	myList<int>* mylist4 = new myList<int>(*mylist3);

	tmpSize = mylist3->size();
	num = 8;
	myList<int>* mylist5 = new myList<int>((*mylist4), 0, num = (num > tmpSize) ? tmpSize : num);


	getchar();
	return 0;
}

#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;
//
//void level(queue<vector<TreeNode*>>&q)
//{
//	vector<TreeNode*> vp;
//	for (int i = 0; i < q.front().size(); ++i)
//	{
//		if (q.front()[i]->left)
//		{
//			vp.push_back(q.front()[i]->left);
//			if (q.front()[i]->right)
//				vp.push_back(q.front()[i]->right);
//		}
//		else if(q.front()[i]->right)
//			vp.push_back(q.front()[i]->right);
//	}
//	q.pop();
//	if (vp.size())
//		q.push(vp);
//}
//
//vector<vector<int>> levelOrder(TreeNode* root)
//{
//	vector<vector<int>> vecs;
//	if (root == NULL)
//		return vecs;
//	vector<TreeNode*> vp;
//	queue<vector<TreeNode*>> q;
//	vp.push_back(root);
//	q.push(vp);
//	while (q.size())
//	{
//		vector<int> v;
//		for (int i = 0; i < q.front().size(); ++i)
//			v.push_back(q.front()[i]->val);
//		vecs.push_back(v);
//		level(q);
//	}
//	return vecs;
//}
int removeDuplicates(vector<int>& nums) {
	std::vector<int>::iterator ite = nums.begin();
	for (; ite < nums.end() - 1;)
	{
		if (*ite == *(ite + 1))
		{
			ite = nums.erase(ite);
		}
		else
		{
			++ite;
		}
	}
	return nums.size();
}

int removeDuplicates1(vector<int>& nums) {
	unsigned int cur = 0, i = 1;
	if (nums.size() < 2)
		return nums.size();

	for (; i < nums.size(); ++i){
		if (nums[i] != nums[cur])
			nums[++cur] = nums[i];
	}

	return cur + 1;
}
vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
	vector<int> result;
	int tmpSize1 = nums1.size();
	int tmpSize2 = nums2.size();
	if (tmpSize1 == 0 || tmpSize2 == 0)
		return result;

	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());
	int index1 = 0, index2 = 0;
	for (; index1 < tmpSize1 && index2 < tmpSize2;)
	{
		if (nums1[index1] == nums2[index2])
		{
			result.push_back(nums1[index1]);
			++index1;
			++index2;
		}
		else if (nums1[index1] < nums2[index2])
		{
			++index1;
		}
		else
		{
			++index2;
		}
	}
	return result;
}

vector<int> plusOne(vector<int>& digits) {
	vector<int> result;
	int tmpSize = digits.size();
	if (tmpSize == 0)
		return result;
	else if (tmpSize == 1 && digits.back() == 0)
	{
		return digits;
	}

	int tmpIndex = tmpSize - 1;
	int bitNum = digits[tmpIndex];
	while (tmpIndex >= 0 && bitNum == 0)// 进位
	{
		tmpIndex -= 1;
		bitNum = digits[tmpIndex] + 1;
	}
	if (bitNum == 0)// 全是9情况
	{
		result.assign(tmpSize, 0);
		result.insert(result.begin(), 1);
	}
	else
	{
		for (int i = 0; i < tmpSize; ++i)
		{
			if (i < tmpIndex)
			{
				result.push_back(digits[i]);
			}
			else if (i == tmpIndex)
			{
				result.push_back(digits[i] + 1);
			}
			else
			{
				result.push_back(0);
			}
		}
	}
	return result;
}

vector<int> twoSum(vector<int>& nums, int target) {
	multimap <int, int> indexMap;
	int tmpSize = nums.size();
	multimap <int, int>::iterator ite;
	vector<int> result;
	for (int i = 0; i < tmpSize; ++i)
	{
		indexMap.insert(make_pair(nums[i], i));
		int findNum = target - nums[i];
		ite = indexMap.find(findNum);
		if (ite != indexMap.end() && ite->second != i)
		{
			result.push_back(i);
			result.push_back(ite->second);
			return result;
		}
	}
	return result;
}






bool isValidSudoku(vector<vector<char>>& board) {
	for (int row = 0; row < 9; ++row)
	{
		for (int col = 0; col < 9; ++col)
		{
			char c = board[row][col];
			if (c == '.')
				continue;
			for (int col_1 = col + 1; col_1 < 9; ++col_1)
			{
				if (c == board[row][col_1])
					return false;
			}
		}
	}
	for (int col = 0; col < 9; ++col)
	{
		for (int row = 0; row < 9; ++row)
		{
			char c = board[row][col];
			if (c == '.')
				continue;
			for (int row_1 = row + 1; row_1 < 9; ++row_1)
			{
				if (c == board[row_1][col])
					return false;
			}
		}
	}
	for (int col = 0; col < 9; col += 3)
	{
		for (int row = 0; row < 9; row += 3)
		{
			vector<int> vec;
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (board[row + i][col + j] != '.')
						vec.push_back(board[row + i][col + j]);
				}
			}
			if (vec.size() <= 1)
				continue;
			sort(vec.begin(), vec.end());
			for (unsigned int i = 0; i < vec.size() - 1; ++i)
			{
				if (vec[i] == vec[i + 1])
					return false;
			}
		}
	}
	return true;
}

void rotate(vector<vector<int>>& matrix) {
	int tmpSize = matrix.size();
	if (tmpSize <= 1)
		return;

	for (int row = 0; row < (tmpSize + 1) / 2; ++row)
	{
		for (int col = row; col < tmpSize - row - 1; ++col)
		{
			int num = matrix[row][col];
			int locRow = row;
			int locCol = col;
			int nextNum = 0;
			for (int i = 0; i < 4; ++i)
			{
				int nextNumRow = locCol;
				int nextNumCol = tmpSize - 1 - locRow;
				nextNum = matrix[nextNumRow][nextNumCol];
				matrix[nextNumRow][nextNumCol] = num;
				locRow = nextNumRow;
				locCol = nextNumCol;
				num = nextNum;
			}
		}
	}
	return;
}
int firstUniqChar(string s) {
	int tmpSize = s.length();
	if (tmpSize <= 1)
		return 0;
	vector<int> indexV;
	map<char, int> indexMap;
	for (int i = 0; i < tmpSize; ++i)
	{
		if (indexMap.find(s[i]) != indexMap.end())
		{
			indexV[indexMap[s[i]]] = -1;
		}
		else
		{
			indexV.push_back(i);
			indexMap[s[i]] = indexV.size() - 1;
		}
	}
	for (unsigned int i = 0; i < indexV.size(); ++i)
	{
		if (indexV[i] != -1)
			return indexV[i];
	}
	return 0;
}
#include <ostream>
#include <algorithm>


bool isAnagram(string s, string t)
{
	if (s.size() != t.size())
	{
		return false;
	}
	int tem[26] = { 0 };
	for (unsigned int i = 0; i < s.size(); i++)
	{
		tem[s[i] - 'a']++;
	}
	for (unsigned int i = 0; i < t.size(); i++)
	{
		tem[t[i] - 'a']--;
	}
	int index = 0;
	for (int i = 0; i < 26; i++)
	{
		index = i;
		if (tem[i] != 0)
		{
			break;
		}
	}
	if (index == 25)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#define isCharacter(c)  (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) ? true: false)   // 判断是否字母
#define isDigital_s(n)    ((n >= '0' && n <= '9') ? true : false)  // 判断是否数字
#define isSameCharacter(a,b) ((toupper(a) == toupper(b)) ? true: false)// 忽略大小写，判断是否是同字符

	bool isPalindrome(string s) {
		int tmpSize = s.size();
		if (tmpSize <= 1)
			return true;
		int head = 0;
		int tail = tmpSize - 1;
		bool headFlag = false;
		bool tailFlag = false;
		while (head <= tail)
		{
			if (!headFlag)
			{
				if (isCharacter(s[head]) || isDigital_s(s[head]))
				{
					headFlag = true;
				}
				else
				{
					++head;
					continue;
				}
			}
			if (!tailFlag)
			{
				if (isCharacter(s[tail]) || isDigital_s(s[tail]))
				{
					tailFlag = true;
				}
				else
				{
					--tail;
					continue;
				}
			}
			if (!isSameCharacter(s[head], s[tail]))//tailFlag && headFlag && 
				return false;
			else
			{
				++head;
				--tail;
				tailFlag = false;
				headFlag = false;
			}
		}
		return true;
	}

#define isNum_1(num) if (num == 1)\
{\
	return true;\
}





#define INT_MAX 2147483647
#define _INT_MIN (-INT_MAX - 1)
#define isDigital(n)        (((n) >= '0' && (n) <= '9') ? true : false)  // 判断是否数字
#define is(n)        (((n) >= '0' && (n) <= '9') ? true : false)  // 判断是否数字
#define transformCtoN(n)    ((n) - '0')

	enum symbol{
		none,          // 未确定
		positive,      // 正数
		negative,      // 负数
	};


	symbol judgeSymbol(char c)
	{
		if (c == '+')
			return symbol::positive;
		else if (c == '-')
			return symbol::negative;
		else
			return symbol::none;
	}

	long long myAtoi(string str) {
		int tmpSize = str.size();
		symbol sym = symbol::none;
		long long num = 0;
		for (int i = 0; i < tmpSize; ++i)
		{
			if (isspace(str[i]) && sym == symbol::none)
				continue;
			else
			{
				if (sym == symbol::none)
					return 0;
				else if (sym == symbol::negative)
					num *= -1;
				return num;
			}
			if (sym == symbol::none && (sym = judgeSymbol(str[i])))// 确定正负数
			{

			}
			else if (isDigital(str[i]))
			{
				if (sym == symbol::none)
					sym = symbol::positive;
				num = num * 10 + transformCtoN(str[i]);
			}
			else
			{
				if (sym == symbol::none)
					return 0;
				else if (sym == symbol::negative)
					num *= -1;
				return num;
			}

		}
		if (sym == symbol::none)
			return 0;
		else if (sym == symbol::negative)
			num *= -1;

		if (num > INT_MAX)
			return INT_MAX;
		else if (num < _INT_MIN)
			return _INT_MIN;
		return num;
	}

#include <string>

	string longestCommonPrefix(vector<string>& strs) {
		int tmpSize = strs.size();
		string s;
		if (tmpSize == 0)
			return s;
		if (tmpSize == 1)
			return strs.front();
		unsigned int tmpIndex = 0;
		while (1)
		{
			int i = 0;
			for (; i <= tmpSize - 1; ++i)
			{
				if (tmpIndex >= strs[i].size() || tmpIndex >= strs[i + 1].size() || strs[i + 1][tmpIndex] != strs[i][tmpIndex])
					return s;
				if (i == tmpSize - 2)
					break;
			}
			s += strs[0][tmpIndex++];
		}
		return s;
	}











	/*
int main()
{
	vector<string> strs;
	string s = "";
	strs.push_back(s);

	cout << longestCommonPrefix(strs);
	getchar();
	//cout << myAtoi("   +0 123");
	//cout << isPalindrome("A man, a plan, a canal: Panama");
	//char cc = '1';
	//cout << toupper(cc) << "   " << isCharacter('z');
	//cout << "  " << isSameCharacter('b', 'a');
	//cout << isDigital('a');
	//int add = 1;
	//int pp = 2;
	//auto addre = &pp;
	//cout << isAnagram("abcde","acebd");
	//cout << isAnagram("rat", "rta");





	//int arr1[10] = { 1, 2, 3, -1, 5, 6, 7, 8, 9, 10 };
	//auto a2313 = [](int arr[10]) { for (int i = 0; i < 10; ++i)
	//	if (arr[i] < 0)
	//		return i; }(arr1);
	//string s = "";
	//cout << s.size();
	//cout << firstUniqChar("loveleetcodeleetcode");
	//map<char, int> indexMap; 
	//long long num = 0;
	//int x = 1534236469;
	//while (x / 10)
	//{
	//	num *= 10;
	//	num += x % 10;
	//	x /= 10;
	//}
	//num *= 10;
	//num += x % 10;
	//int ma = (2 << 30) - 1;
	//int mi = (-2 << 30);
	//if (num > ma || num < mi)
	//	return 0;
	//return num;
	//string s1("123456");
	//auto aaa = s1.size();
	//aaa = s1.length();
	//reverse(s1.begin(), s1.end());
	//vector<vector<int>> matris;
	//vector<int> vc11 = { 1, 2, 3 };
	//reverse(vc11.begin(), vc11.end());
	//vector<int> vc12 = { 4, 5, 6 };
	//vector<int> vc13 = { 7, 8, 9 };
	//matris.push_back(vc11);
	//matris.push_back(vc12);
	//matris.push_back(vc13);
	//rotate(matris);
	//vector<vector<char>> board;
	//vector<char> vc1 = { '5', '3', '.', '.', '7', '.', '.', '.', '.' };
	//vector<char> vc2 = { '6', '.', '.', '1', '9', '5', '.', '.', '.' };
	//vector<char> vc3 = { '.', '9', '8', '.', '.', '.', '.', '6', '.' };
	//vector<char> vc4 = { '8', '.', '.', '.', '6', '.', '.', '.', '3' };
	//vector<char> vc5 = { '4', '.', '.', '8', '.', '3', '.', '.', '1' };
	//vector<char> vc6 = { '7', '.', '.', '.', '2', '.', '.', '.', '6' };
	//vector<char> vc7 = { '.', '6', '.', '.', '.', '.', '2', '8', '.' };
	//vector<char> vc8 = { '.', '.', '.', '4', '1', '9', '.', '.', '5' };
	//vector<char> vc9 = { '.', '.', '.', '.', '8', '.', '.', '7', '9' };
	//board.push_back(vc1);
	//board.push_back(vc2);
	//board.push_back(vc3);
	//board.push_back(vc4);
	//board.push_back(vc5);
	//board.push_back(vc6);
	//board.push_back(vc7);
	//board.push_back(vc8);
	//board.push_back(vc9);
	//cout << isValidSudoku(board);

	//vector<int> nums4 = { 3,3 };
	//auto re = twoSum(nums4, 6);

	//vector<int> nums1 = { 1, 1, 2, 3, 4, 5, 6 };
	//auto loc = find(nums1.begin(), nums1.end(), 7);
	//loc == nums1.end() ? cout << "last" : cout << "nolast";
	//vector<int> nums2 = { 1, 1, 5, 6 };
	//auto reus = intersect(nums1,nums2);
	//vector<int> nums = { 2,2,1};
	////nums.insert(nums.begin(), 5);
	////nums.pop_back();
	////reverse(nums.begin(), nums.end());
	////removeDuplicates1(nums);
	//int tmpSize = nums.size();
	//if (tmpSize <= 1)
	//	return nums.back();
	//sort(nums.begin(), nums.end());
	//for (int i = 1; i < tmpSize; i += 2)
	//{
	//	if (nums[i] != nums[i - 1])
	//		return nums[i];
	//}
	return NULL;
}
*/