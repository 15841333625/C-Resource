// text2.5.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;

template<class T> 
class A {
public:
	T& a(T t);
};
//�������еĺ���T& a()
template<class K>
K& A<K>::a(K t) {
	cout<<t<<endl;
	return t;
}
//�ػ�
template<>
float& A<float>::a(float f) {
	cout<<"f = "<<f<<endl;
	return f;
}

int _tmain(int argc, _TCHAR* argv[])
{
	A<int> a;    //��ʽʵ����
	A<float> b;
	a.a(5);
	b.a(5);      //�����ػ��ĺ���
	system("pause");
	return 0;
}

