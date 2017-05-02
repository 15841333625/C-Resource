// reviewInherit.cpp : 定义控制台应用程序的入口点。
//class c: public A,B ----- A 是公有继承，B 是私有继承
//按继承顺序初始化，和初始化列表无关
//

#include "stdafx.h"
#include<iostream>
using namespace std;

class A
{
protected:
	int i;
public:
	A(int i = 0):i(i){cout<<"A()"<<endl;}
	void a(){cout<<"a()"<<endl;}
};

class B
{
protected:
	int j;
public:
	B(int j = 1):j(j){cout<<"B()"<<endl;}
	void b(){cout<<"b()"<<endl;}
};

class C : public A,B           //对 B 为私有继承
{
private:
	int i;                     //和 A 类中成员同名，则 A 类中的 i 隐藏
public:
	C(int i = 0, int j = 1):B(j),A(i){cout<<"C()"<<endl;}  //C(int i, int j):B(j),A(i){cout<<"C()"<<endl;} 实例化C c；显示无默认构造函数
	void c(){ a(); b(); }
	void showI() const {cout<<"A:i:"<<A::i<<" "<<"C:i:"<<i<<endl;}  //showI 只读
	const int getI() const {return i;};    //getI 和其返回值都是只读，返回的是 C 中的 i
};

int _tmain(int argc, _TCHAR* argv[])
{
	C c;
	c.a();
	c.c();
	system("pause");
	return 0;
}

