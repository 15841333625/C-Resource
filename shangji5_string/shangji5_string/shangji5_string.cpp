// shangji5_string.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#define N 100
using namespace std;

class String 
{
public:
	char *c;
	int length;
public:
	String():length(0){c = new char[N];}
	~String(){delete c;c = 0;}
	void input()
	{
		for(int i = 0; i<N; i++)
		{scanf("%c",&c[i]);length++;if(c[i]=='\n')break;}
		length--;
	}
	int getlength(){return length;}
	void print(){for(int i=0; i<length; i++)cout<<c[i];}
};

class edit_string:public String
{
private:
	char *p;
public:
	edit_string(){}
	void insert(int i,String s);
	void replace(int i, char a);
	void remove(int i); 
};
void edit_string::insert(int i,String _s)
{
	for(int j = 0; j < _s.length; j++)
	{
		for(int k = length; k > i+j; k--)
		{
			c[k+1] = c[k];
		}
		c[i+j] = _s.c[j];
		length++;
	}
}
void edit_string::replace(int i, char a)
{
	c[i-1] = a;
}
void edit_string::remove(int i)
{
	for(int j = i-1; j<length; j++)
	{
		c[j] = c[j+1];
	}
	length--;
}

int _tmain(int argc, _TCHAR* argv[])
{
	edit_string s;
	s.input();
	cout<<s.getlength()<<endl;
	s.print();
	String _s;
	cout<<endl<<"输入要插入的字符串："<<endl;
	_s.input();
	int x;
	cout<<"输入插入字符串的位置："<<endl;
	scanf("%d",&x);
	s.insert(x,_s);
	s.print();
	int y;
	cout<<endl<<"输入替换字符的位置："<<endl;
	cin>>y;
	char a;
	cout<<"输入替换的字符"<<endl;
	cin>>a;
	s.replace(y,a);
	s.print();
	cout<<endl;
	int n;
	cout<<"输入删除字符位置："<<endl;
	cin>>n;
	s.remove(n);
	s.print();
	system("pause");
	return 0;
}

