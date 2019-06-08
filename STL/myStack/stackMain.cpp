#include <iostream>
using namespace std;
#include "myVector.h"
#include "myVector.cpp"
#include "myStack.h"

int main()
{
	myStack<int> s;
	cout << s.size() << endl;
	cout << s.empty() << endl;
	s.push(10);
	s.push(5);
	s.push(7);
	s.display();
	s.pop();
	s.display();
	cout << s.top() << endl;
	cout << s.size() << endl;
	cout << s.empty() << endl;
	return 0;
}