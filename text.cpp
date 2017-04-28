// text2.4.cpp : 定义控制台应用程序的入口点。
//抽象类不能用作函数返回值
//A *p[2] = {new B, new C}; 才有效
//A *p = new B();时，A 类中的虚构函数要是 virtual 的，销毁时才能调用 B 的析构函数；A 类和 B 类中重名的
//     函数p调用A中的
//++i 作左值， i 最后等于那个右值
//virtual 不能和 static 一起使用

#include "stdafx.h"
#include<iostream>
using namespace std;

class A
{
public:
	virtual void a() = 0;
	void b(){cout<<"A::b()"<<endl;}  //无法动态调用，但没有语法错误
	~A(){cout<<"~A()"<<endl;}
};

class B : public A
{
public:
	void a(){cout<<"B::a()"<<endl;}
	void b(){cout<<"B::b()"<<endl;}  
	~B(){cout<<"~B()"<<endl;}
};

int _tmain(int argc, _TCHAR* argv[])
{
	A *p[2] = {new B(),new B()};
	p[0]->a();  
	p[1]->b();  // A::b()
	delete p[0];p[0] = NULL; //~A()
	delete p[1];p[1] = NULL;

	B *p2 = new B();
	p2->b();    //B::b()
	delete p2;p2 = NULL;     //~B()  ~A()

    int i = 0;
	cout<<(++i = i++)<<endl;   //1
	cout<<i<<endl;             //2
	system("pause");
	return 0;
}

