// Date.cpp : 定义控制台应用程序的入口点。
//定义一个日期类Date，包含年、月、日三个数据成员 
//重载自增运算  重载<<运算符

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
	Date& operator++();      //重载前++
	Date operator++(int);    //重载后++
private:
	friend ostream& operator<<(ostream& out, const Date& d); //定义为友元
	int year;
	int month;
	int day;
	static const int days[];  //每月天数
	void increment();         //日期合理增1
};
const int Date::days[] = {31,28,31,30,31,30,31,31,30,31,30,31};  //每月天数
//判断是否为闰年
bool Date::leapYear(int y)
{
	if( y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
	{   return true;   }else{
		return false;
	}
}
//判断是否为月末
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
	//合理的年月日设置
	year = (y >= 1900 && y <= 2100)? y:1900;
	month = (m > 0 && m < 13)? m:1;
	if(month == 2 && leapYear(year)){
		day = (d > 0 && d < 30)? d:1;
	}else{
		day = (d > 0 && d <= days[month])? d:1;
	}
}
//日期加1
void Date::increment()
{
	//年末
	if(month == 12 && day == 30){
		year ++;
		month = 1;
		day = 1;
	}
	//月末
	else if(endOfMonth(day)){
		day = 1;
		month ++;
	}
	//其他
	else{
		day ++;
	}
}
//前++
Date& Date::operator++()
{
	increment();
	return *this;
}
//后++
Date Date::operator++(int)
{
	Date temp = *this;
	increment();
	return temp;
}

//输出重载为普通函数
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

