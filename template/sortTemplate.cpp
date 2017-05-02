// shangji7_1sort.cpp : 定义控制台应用程序的入口点。
// 用函数模板方式设计一个函数模板sort<T>，采用直接插入排序方式对数据进行排序，并对整数序列和字符序列进行排序。

#include "stdafx.h"
#include<iostream>
using namespace std;

//直接插入排序模板
template<class T>
void sort(T a[], int n)
{
	int i = 0, j = 0;
	for(i = 1; i<n; i++)
	{
		T temp;
		temp = a[i];
		for(j = i-1; j>=0 && a[j]>temp; j--)
			a[j+1] = a[j];
		a[j+1] = temp;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[5];
	cout<<"input int a[5]:"<<endl;
	for(int i = 0; i<5; i++)
	{
		cin>>a[i];
	}
	sort<int>(a,5);               //显式实例化模板
	for(int i = 0; i<5; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	char b[6];                    //显示实例化模板
	cout<<"input char b[6]:"<<endl;
	for(int i = 0; i<6; i++)
	{
		cin>>b[i];
	}
	sort<char>(b,6);
	for(int i = 0; i<6; i++)
	{
		cout<<b[i]<<" ";
	}
	cout<<endl;
	system("pause");
	return 0;
}

