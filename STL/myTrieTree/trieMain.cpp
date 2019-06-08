#include <iostream>
#include "myTrieTree.h"
using namespace std;

int main()
{
	myTrieTree myTrieTree;
	myTrieTree.insert("hello");
	myTrieTree.insert("he");
	myTrieTree.insert("her");
	myTrieTree.insert("world");
	myTrieTree.insert("word");

	myTrieTree.search("hello") ? cout << "hello exist!" << endl : cout << "hello not exist!" << endl;
	myTrieTree.search("hel") ? cout << "hel exist!" << endl : cout << "hel not exist!" << endl;
	myTrieTree.search("word") ? cout << "word exist" << endl : cout << "word not exist!" << endl;
	myTrieTree.search("worlld") ? cout << "worlld exist" << endl : cout << "worlld not exist!" << endl;
	getchar();
	return 0;
}