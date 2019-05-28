#include <iostream>
#include "myQueue.h"
#include "myList.cpp"
using namespace std;

int main()
{
	myQueue<int> q;
	cout << q.size() << "	" << q.empty() << endl;
	q.push(1);
	q.push(3);
	q.push(5);
	q.push(7);
	q.push(9);
	q.display();
	cout << q.size() << "	" << q.empty() << endl;

	q.pop();
	cout << q.front() << "	" << q.back() << endl;
	return 0;
}