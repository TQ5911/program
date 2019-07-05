#include <iostream>
#include <pthread.h>
using namespace std;
/*class Singleton
{
private:
static Singleton *local_instance;
Singleton()
{
cout << "构造" << endl;
}
~Singleton()
{
cout << "析构" << endl;
}
public:
static Singleton *getInstance()
{
if (local_instance == nullptr)
{
local_instance = new Singleton();
}
return local_instance;
}
};




Singleton * Singleton::local_instance = nullptr;

int main()
{
Singleton * s = Singleton::getInstance();
return 0;
}
//代码中有两个问题，一个是多线程的情况下可能会出现new两次的情况。另外一个是程序退出后没有运行析构函数。
//使用局部静态对象来解决存在的两个问题
*/


//内部静态变量的懒汉实现
//class Singleton
//{
//private:
//	static Singleton *local_instance;
//	Singleton()
//	{
//		cout << "构造" << endl;
//	};
//	~Singleton()
//	{
//		cout << "析构" << endl;
//	}
//
//public:
//	static Singleton *getInstance()
//	{
//		static Singleton locla_s;
//		cout << &locla_s << endl;
//		return &locla_s;
//	}
//};
//
//
//int main()
//{
//	cout << "单例模式访问第一次前" << endl;
//	Singleton * s = Singleton::getInstance();
//	cout << "单例模式访问第一次后" << endl;
//	cout << "单例模式访问第二次前" << endl;
//	Singleton * s2 = Singleton::getInstance();
//	cout << "单例模式访问第二次后" << endl;
//	return 0;
//}
//在c++11之前的版本导致多次构造函数的调用，所以只能在较新的编译器上使用。


//线程安全的懒汉实现
class singleton
{
protected:
	singleton()
	{
		cout << "构造" << endl;
		pthread_mutex_init(&mutex,NULL);
	}
private:
	static singleton* p;
public:
	static pthread_mutex_t mutex;
	static singleton* initance();
};

pthread_mutex_t singleton::mutex;
singleton* singleton::p = NULL;
singleton* singleton::initance()
{
	cout << "call initance()" << endl;
	if (p == NULL)
	{
		pthread_mutex_lock(&mutex);
		if (p == NULL)// 这里再判断是防止多次被实例化
			p = new singleton();
		pthread_mutex_unlock(&mutex);
	}
	cout << "exxt initance()" << endl;
	return p;
}
int main()
{
	singleton* p = singleton::initance();
	return 0;
}

//
//
//// 饿汉实现
//class singleton
//{
//protected:
//	singleton()
//	{}
//private:
//	static singleton* p;
//public:
//	static singleton* initance();
//};
//singleton* singleton::p = new singleton;
//singleton* singleton::initance()
//{
//	return p;
//}
//
//int main()
//{
//	auto p = singleton::initance();
//	return 0;
//}
