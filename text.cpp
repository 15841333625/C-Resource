// text2.4.cpp : �������̨Ӧ�ó������ڵ㡣
//�����಻��������������ֵ
//A *p[2] = {new B, new C}; ����Ч
//A *p = new B();ʱ��A ���е��鹹����Ҫ�� virtual �ģ�����ʱ���ܵ��� B ������������A ��� B ����������
//     ����p����A�е�
//++i ����ֵ�� i �������Ǹ���ֵ
//virtual ���ܺ� static һ��ʹ��

#include "stdafx.h"
#include<iostream>
using namespace std;

class A
{
public:
	virtual void a() = 0;
	void b(){cout<<"A::b()"<<endl;}  //�޷���̬���ã���û���﷨����
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

