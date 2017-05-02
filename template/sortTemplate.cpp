// shangji7_1sort.cpp : �������̨Ӧ�ó������ڵ㡣
// �ú���ģ�巽ʽ���һ������ģ��sort<T>������ֱ�Ӳ�������ʽ�����ݽ������򣬲����������к��ַ����н�������

#include "stdafx.h"
#include<iostream>
using namespace std;

//ֱ�Ӳ�������ģ��
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
	sort<int>(a,5);               //��ʽʵ����ģ��
	for(int i = 0; i<5; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	char b[6];                    //��ʾʵ����ģ��
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

