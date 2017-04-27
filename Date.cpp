// Date.cpp : �������̨Ӧ�ó������ڵ㡣
//����һ��������Date�������ꡢ�¡����������ݳ�Ա 
//������������  ����<<�����

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;

class Date
{
public:
	Date(int, int, int);
	bool leapYear(int);
	bool endOfMonth(int);
	Date& operator++();      //����ǰ++
	Date operator++(int);    //���غ�++
private:
	friend ostream& operator<<(ostream& out, const Date& d); //����Ϊ��Ԫ
	int year;
	int month;
	int day;
	static const int days[];  //ÿ������
	void increment();         //���ں�����1
};
const int Date::days[] = {31,28,31,30,31,30,31,31,30,31,30,31};  //ÿ������
//�ж��Ƿ�Ϊ����
bool Date::leapYear(int y)
{
	if( y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
	{   return true;   }else{
		return false;
	}
}
//�ж��Ƿ�Ϊ��ĩ
bool Date::endOfMonth(int d)
{
	if(!leapYear(year) || leapYear(year) && (month != 2)){
		return (d == days[month]);
	}else{
		return (d == 29);
	}
}
Date::Date(int y = 1900, int m = 1, int d = 1)
{
	//���������������
	year = (y >= 1900 && y <= 2100)? y:1900;
	month = (m > 0 && m < 13)? m:1;
	if(month == 2 && leapYear(year)){
		day = (d > 0 && d < 30)? d:1;
	}else{
		day = (d > 0 && d <= days[month])? d:1;
	}
}
//���ڼ�1
void Date::increment()
{
	//��ĩ
	if(month == 12 && day == 30){
		year ++;
		month = 1;
		day = 1;
	}
	//��ĩ
	else if(endOfMonth(day)){
		day = 1;
		month ++;
	}
	//����
	else{
		day ++;
	}
}
//ǰ++
Date& Date::operator++()
{
	increment();
	return *this;
}
//��++
Date Date::operator++(int)
{
	Date temp = *this;
	increment();
	return temp;
}

//�������Ϊ��ͨ����
ostream& operator<<(ostream& out, const Date& d)
{
	out<<d.year<<"."<<d.month<<"."<<d.day;
	return out;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Date d(1998,1,23);
	cout<<++d<<endl;
	cout<<d++<<endl;
	cout<<d<<endl;
	system("pause");
	return 0;
}

