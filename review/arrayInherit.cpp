// shangji4_4MyArray.cpp : 定义控制台应用程序的入口点。
// 定义一个基类MyArray,基类中可以存放一组数组。编写构造函数，析构函数及其它函数，实现动态分配内存，释放内存和数据输入输出等功能。并进行调试。
// 定义一个类averarray继承自myarray，在类中求数组的平均值，并输出。进行调试。
// 定义一个类revarray继承自 myarray, 使数组按反序存放，并输出。进行调试。
// 定义一个类Nawarray继承自averarray和revarray。在继承过程中声明为虚基类，体会虚基类在解决二义性中的问题中的作用。调试中可以试一试不用虚基类出现的问题。

#include "stdafx.h"
#include<iostream>
using namespace std;

class MyArray
{
protected:
	int *alist;
	int length;
public:
	MyArray(int len);
	virtual ~MyArray();
	void input();
	void display();
};
MyArray::MyArray(int len):length(len)
{ alist = new int[len];}
MyArray::~MyArray(){delete[] alist; alist = NULL;}
void MyArray::input()
{for(int i = 0; i<length; i++)cin>>alist[i];}
void MyArray::display()
{for(int i = 0; i<length; i++)cout<<alist[i]<<" ";}

//平均值
class averarray:virtual public MyArray
{
public:
	averarray(int leng):MyArray(leng){}
	virtual ~averarray(){cout<<"~averarray()"<<endl;}
	double average();
};
double averarray::average()
{
	double sum = 0;
	for(int i = 0; i<length; i++)
		sum+=alist[i];
	return sum/length;
}

//反序存放
class revarray:virtual public MyArray
{
public:
	revarray(int leng):MyArray(leng){}
	virtual ~revarray(){cout<<"~revarray"<<endl;}
	void reva();
};
void revarray::reva()
{
	for(int i = 0; i<length/2; i++)
	{
		int temp;
		temp = alist[i];
		alist[i] = alist[length - i - 1];
		alist[length - i - 1] = temp;
	}
}

class Nawarray:public averarray, public revarray
{
public:
	Nawarray(int leng):averarray(length),revarray(length),MyArray(leng){cout<<"Nawarray()"<<endl;}
};

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"input a1(2)"<<endl;
	MyArray a1(2);
	a1.input();
	cout<<"display:"<<endl;
	a1.display();
	cout<<endl<<"input a2(3)"<<endl;
	averarray a2(3);
	a2.input();
	cout<<"average: "<<a2.average()<<endl;
	revarray a3(3);
	cout<<"input a3(3)"<<endl;
	a3.input();
	cout<<"revarray:"<<endl;
	a3.reva();
	a3.display();
	cout<<endl;
	Nawarray a4(2);
	system("pause");
	return 0;
}

