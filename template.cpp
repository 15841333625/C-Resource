// text2.5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

template<class T> 
class A {
public:
	T& a(T t);
};
//定义类中的函数T& a()
template<class K>
K& A<K>::a(K t) {
	cout<<t<<endl;
	return t;
}
//特化
template<>
float& A<float>::a(float f) {
	cout<<"f = "<<f<<endl;
	return f;
}

int _tmain(int argc, _TCHAR* argv[])
{
	A<int> a;    //显式实例化
	A<float> b;
	a.a(5);
	b.a(5);      //调用特化的函数
	system("pause");
	return 0;
}

