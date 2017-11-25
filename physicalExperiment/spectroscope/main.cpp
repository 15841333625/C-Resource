#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
using namespace std;
double const PI = 3.1415926;

class Angle{
public:
    int degrees;
    int points;
public:
    Angle(int degree = 0, int point = 0):degrees(degree), points(point){}
    Angle& operator+(Angle& a){     //重载+
        Angle result = *this;
        int carryBit = 0;
        result.points = a.points + points;
        if(result.points >= 60){
            carryBit = 1;
            result.points -= 60;
        }
        result.degrees = ((a.degrees + degrees + carryBit) > 360)?(a.degrees + degrees + carryBit - 360):(a.degrees + degrees + carryBit);
        return result;
    }
    Angle& operator-(Angle& a){     //重载-
        Angle result = *this;
        int borrBit = 0;
        result.points = points - a.points;
        if(result.points <= 0){
            borrBit = 1;
            result.points += 60;
        }
        result.degrees = ((degrees - a.degrees - borrBit) < 0)?(degrees - a.degrees - borrBit + 360):(degrees - a.degrees - borrBit);
        return result;
    }
    Angle& operator/(int i){        //重载/，除常数
        Angle result = *this;
        double point = degrees * 60 + points;
        point = point / i;
        if((point - (int)point) >= 0.5)
            result.points = (int)point % 60 + 1;
        else
            result.points = (int)point % 60;
        result.degrees = (int)point / 60;
        return result;
    }
    Angle& operator*(Angle& a){     //重载*，乘角度
        Angle result = *this;
        int carryBit = 0;
        result.points = points * a.points;
        if(result.points > 60){
            int remainder = result.points % 60;
            carryBit = result.points / 60;
            result.points = remainder;
        }
        result.degrees = degrees * a.degrees + carryBit;
        return result;
    }
    Angle& operator/(Angle& a){     //重载/，除角度
        Angle result = *this;
        int point1 = degrees * 60 + points;
        int point2 = a.degrees * 60 + a.points;
        int point3 = point1 / point2;
        result.degrees = point3 / 60;
        result.points = point3 % 60;
        return result;
    }
    Angle& operator*(double d){     //重载*，乘浮点数
        Angle result = *this;
        double point = degrees * 60 + points;
        point *= d;
        if((point - (int)point) >= 0.5)
            result.points = (int)point % 60 + 1;
        else
            result.points = (int)point % 60;
        result.degrees = (int)point / 60;
        return result;
    }
    Angle& operator|(Angle& a){     //重载|，计算差值的绝对值
        Angle result = *this;
        int point1 = degrees * 60 + points;
        int point2 = a.degrees * 60 + a.points;
        if(point1 > point2){
            int point3 = point1 - point2;
            result.degrees = point3 / 60;
            result.points = point3 % 60;
        }else{
            int point3 = point2 - point1;
            result.degrees = point3 / 60;
            result.points = point3 % 60;
        }
        return result;
    }
};
ostream& operator<<(ostream &out, Angle &a){  //重载输出
    out<<a.degrees<<'^'<<a.points<<'`';
    return out;
}

//开方
Angle sqrtAngle(Angle a){
    Angle result;
    double points = a.degrees * 60 + a.points;
    points = sqrt(points);
    if((points - (int)points) >= 0.5)
            result.points = (int)points % 60 + 1;
    else
        result.points = (int)points % 60;
    result.degrees = (int)points / 60;
    return result;
}

//求顶角及δmin
Angle countPointAngle(Angle f11, Angle f12, Angle f21, Angle f22){
    Angle pointAngle;
    Angle dmin;
    Angle temp1 = f21 - f11;
    Angle temp2 = f22 - f12;
    pointAngle = temp1 + temp2;
    cout<<pointAngle<<endl;
    pointAngle = pointAngle / 4;
    dmin = temp1 + temp2;
    dmin = dmin / 2;
    cout<<"f2  - f1 :  "<<temp1<<endl;
    cout<<"f2' - f1':  "<<temp2<<endl;
    cout<<"dmin     :  "<<dmin<<endl;
    return pointAngle;
}

//求不确定度
Angle countUncertainty(Angle a[], int length){
    Angle Uncertainty;
    double n = length;                          //测量次数
    double v = n - 1;                           //自由度
    double tp = 1.959 + 2.406 / ( v - 1.064 );  //概率因子
    Angle averag;                               //角度平均值
    Angle sum;
    Angle s;
    Angle Ua;                                   //A类不确定度
    Angle Ub(0,1);                              //B类不确定度，为1'
    Angle U;
    //计算A类不确定度
    //计算平均值
    for(int i = 0; i < length; i ++)
        sum = sum + a[i];
    averag = sum / length;
    cout<<"n :"<<n<<endl;
    cout<<"t :"<<tp<<endl;
    cout<<"average :"<<averag<<endl;
    //计算s
    sum.degrees = 0;
    sum.points = 0;
    for(int i = 0; i < length; i ++){
        Angle difference = a[i] | averag;      //求差取绝对值
        Angle dif = difference * difference;
        sum =  dif + sum;
    }
    sum = sum / (length - 1);
    s = sqrtAngle(sum);
    cout<<"s :"<<s<<endl;
    //公式
    Ua = s * (tp / sqrt(n));
    cout<<"Ua "<<Ua<<endl;
    cout<<"Ub "<<Ub<<endl;
    sum = Ub * Ub;
    U = Ua * Ua;
    U = U + sum;
    U = sqrtAngle(U);
    cout<<"U  "<<U<<endl;
    return U;
}

//角度制变弧度制
double turnToRadian(Angle a){
    double angle = a.degrees + (double)a.points / 60.0;
    return (angle * PI / 180);
}

//求棱镜折射率
double countRefractivity(Angle a, Angle dmin){
    double aRad = turnToRadian(a);
    cout<<"aRad "<<aRad<<endl;
    double dminRad = turnToRadian(dmin);
    cout<<"dminRad "<<dminRad<<endl;
    return (sin((aRad + dminRad) / 2)) / (sin(aRad / 2));
}

//求折射率不确定度
double countRefracUncert(Angle a, Angle dmin, Angle Ua, Angle Udmin, double n){
    double aRadian = turnToRadian(a);
    double dminRad = turnToRadian(dmin);
    double UaRadia = turnToRadian(Ua);
    cout<<"Ua "<<UaRadia;
    double UdminRa = turnToRadian(Udmin);
    cout<<"Udmin "<<UdminRa<<endl;
    double temp1 = 1 / tan((dminRad + aRadian) / 2);
    double temp2 = temp1 - (1 / tan(aRadian / 2));
    double temp3 = pow(temp2, 2) * pow(UaRadia, 2) + pow(temp1, 2) * pow(UdminRa, 2);
    cout<<temp1<<endl;
    cout<<temp2<<endl;
    cout<<temp3<<endl;
    return sqrt(temp3) * n / 2;
}

int main()
{
//    while(1){
//        int f[4][2];
//        for(int i = 0; i < 4; i ++){
//            for(int j = 0; j < 2; j ++)
//                cin>>f[i][j];           //顺序Ø1°,Ø1`;Ø2°,Ø2`;Ø1'°,Ø1'`;Ø2'°,Ø2'
//        }
//        Angle f11(f[0][0], f[0][1]);    //Ø1
//        Angle f21(f[1][0], f[1][1]);    //Ø2
//        Angle f12(f[2][0], f[2][1]);    //Ø1'
//        Angle f22(f[3][0], f[3][1]);    //Ø2'
//        Angle c;
//        c = countPointAngle(f11, f12, f21, f22);
//        cout<<"a        :  "<<c<<endl;
////        cout<<"DONE: "<<endl;
////        cin>>DONE;
//    }

//    int f[5][2];
//    Angle a[5];
//    Angle U;
//    for(int i = 0; i < 5; i ++){
//        for(int j = 0; j < 2; j ++)
//            cin>>f[i][j];
//    }
//    for(int i = 0; i < 5; i ++){
//        a[i].degrees = f[i][0];
//        a[i].points = f[i][1];
//    }
//    U = countUncertainty(a, 5);

    Angle dmin;
    Angle a;
    Angle Ua;
    Angle Udmin;
    double n;
    double unCertainty;
    scanf("%d %d %d %d %d %d %d %d", &a.degrees, &a.points, &dmin.degrees, &dmin.points, &Ua.degrees, &Ua.points, &Udmin.degrees, &Udmin.points);
    n = countRefractivity(a, dmin);
    unCertainty = countRefracUncert(a, dmin, Ua, Udmin, n);
    cout<<n<<endl;
    cout<<unCertainty<<endl;
    return 0;
}
