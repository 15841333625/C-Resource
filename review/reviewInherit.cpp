// reviewInherit.cpp : �������̨Ӧ�ó������ڵ㡣
//class c: public A,B ----- A �ǹ��м̳У�B ��˽�м̳�
//���̳�˳���ʼ�����ͳ�ʼ���б��޹�
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

class C : public A,B           //�� B Ϊ˽�м̳�
{
private:
	int i;                     //�� A ���г�Աͬ������ A ���е� i ����
public:
	C(int i = 0, int j = 1):B(j),A(i){cout<<"C()"<<endl;}  //C(int i, int j):B(j),A(i){cout<<"C()"<<endl;} ʵ����C c����ʾ��Ĭ�Ϲ��캯��
	void c(){ a(); b(); }
	void showI() const {cout<<"A:i:"<<A::i<<" "<<"C:i:"<<i<<endl;}  //showI ֻ��
	const int getI() const {return i;};    //getI ���䷵��ֵ����ֻ�������ص��� C �е� i
};

int _tmain(int argc, _TCHAR* argv[])
{
	C c;
	c.a();
	c.c();
	system("pause");
	return 0;
}

