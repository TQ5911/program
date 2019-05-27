#include <time.h>
#include <iostream>
using namespace std;
#include "myVector.h"
#include "myVector.cpp"
typedef void(*pFunc)(int& data);

template<typename T>
void printfFunc(T& data)
{
	cout << data << " ";
}

int main()
{
	pFunc fun = printfFunc;
	srand(time(NULL));
	std::initializer_list<int> li = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//stack<int> s;
	myVector<int> v;
	myVector<int> v1(li);
	myVector<int> v2(v1);
	myVector<int> v3(v1,0,v1.size());
	myVector<int> v4 = v;
	v.display();
	v1.display();
	v2.display();
	v3.display();
	v4.display();

	v1.replace(9, 10);  //Ìæ»»Ö¸¶¨ÔªËØ	
	cout << v1.get(9) << endl;

	cout << v1.find(0,v1.size() - 1,9) << endl;
	v1.insert(0, 9);
	v1.push_back(11);v1.display();
	v1.remove(11); v1.display();
	v1.insert(0, 8); v1.traverse(fun);
	cout << endl;
	v1.deduplicate(); v1.traverse(printfFunc);
	cout << endl;
	cout << v1.search(5) << endl;

	cout << v1.front() << "		" << v1.back() << endl;


	v1.sort(0, v1.size(), 3); v1.display();
	v1.permute();v1.display();
	v1.sort(0, v1.size(), 1); v1.display();
	v1.unsort(5, 9);v1.display();

	v1.clear(); 
	v.expand();
	return 0;
}