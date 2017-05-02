// shangji4_4MyArray.cpp : �������̨Ӧ�ó������ڵ㡣
// ����һ������MyArray,�����п��Դ��һ�����顣��д���캯������������������������ʵ�ֶ�̬�����ڴ棬�ͷ��ڴ��������������ȹ��ܡ������е��ԡ�
// ����һ����averarray�̳���myarray���������������ƽ��ֵ������������е��ԡ�
// ����һ����revarray�̳��� myarray, ʹ���鰴�����ţ�����������е��ԡ�
// ����һ����Nawarray�̳���averarray��revarray���ڼ̳й���������Ϊ����࣬���������ڽ���������е������е����á������п�����һ�Բ����������ֵ����⡣

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

//ƽ��ֵ
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

//������
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

