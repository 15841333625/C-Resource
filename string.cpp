// string.cpp : 定义控制台应用程序的入口点。
//  一个简单串类string，包含输入字符串、返回字符串长度及内容等功能；
//	另有一个具有编辑功能的串类edit_string，它继承string类，在其中设置一个光标，
//  使其能支持在光标处的插入、替换和删除等编辑功能。


#include "stdafx.h"
#include<iostream>
using namespace std;
#define N 100 

class String
{
public:
	String();
	String(const String &s);
	~String();
	void input();
	void show();
	int getLength();
	char* getChar();
protected:
	char *m_c;
	int m_length;
};
//构造
String::String():m_length(0)
{
	m_c = new char[N];
	//cout<<"String()"<<endl;
}
//拷贝构造
String::String(const String &s)
{
	m_c = new char[N];
	m_length = s.m_length;
	for(int i = 0; i<s.m_length; i++)
	{
		m_c[i] = s.m_c[i];
	}
	//cout<<"String(const String &s)"<<endl;
}
//输入字符串
void String::input()
{
	for(int i = 0; i<N; i++)
	{
		scanf("%c",&m_c[i]);
		if(m_c[i] == '\n'){break;}  //若输入为回车则停止输入
		else{m_length ++;}
	}
}
//显示
void String::show()
{
	for(int i = 0; i<m_length; i++)
	{
		cout<<m_c[i];
	}
	cout<<endl;
}
//返回长度
int String::getLength()
{
	return m_length;
}
//返回内容
char* String::getChar()
{
	return m_c;
}
//析构
String::~String()
{
	delete m_c; m_c = NULL;
	cout<<"~String()"<<endl;
}

class edit_string:public String
{
public:
	edit_string();
	edit_string( String& s);
	~edit_string(){cout<<"~edit_string()"<<endl;}
	void insert(int , String);
	char replace(int , char);
	void deleteChar(int, int);
private:
	char *p;
};
edit_string::edit_string():p(NULL){
	//cout<<"edit_string()"<<endl;
}
edit_string::edit_string(String &s)
{
	m_c = new char[N];
	m_length = s.getLength();
	for(int i = 0; i<s.getLength(); i++)
	{
		m_c[i] = s.getChar()[i];
	}
}
//插入
void edit_string::insert(int i, String s)
{
	int l = s.getLength();
	char *c = s.getChar();
	for(int j = 0; j<l; j++)
	{
		
		for(int k = m_length; k>i+j ; k--)
		{
			m_c[k+1] = m_c[k];
		}
		m_c[i+j] = c[j];
		m_length ++;
	}
}
//替换
char edit_string::replace(int i, char c)
{
	i--;
	char temp = m_c[i];
	m_c[i] = c;
	return temp;
}
//删除
void edit_string::deleteChar(int i, int len = 1)
{
	for(int k = 0; k<len; k++)
	{
		for(int j = i-1; j<m_length-1; j++)
	    {
		    m_c[j] = m_c[j+1];
	    }
	}
	m_length -= len;
}

int _tmain(int argc, _TCHAR* argv[])
{
	String *s = new edit_string();
	s->input();
	s->show();
	int l = s->getLength();
	cout<<l<<endl;

	edit_string *s2 = new edit_string(*s);
	s2->show();
	s2->insert(2,*s);
	s2->show();
	
	cout<<s2->replace(2,'c')<<endl;
	s2->show();

	s2->deleteChar(2,2);
	s2->show(); 

	delete s;s = 0;
	delete s2; s2 = 0;
	system("pause");
	return 0;
}

