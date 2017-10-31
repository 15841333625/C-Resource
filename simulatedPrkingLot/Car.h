#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <string>

//声明并实现类Car。Car类中需要存放车的车牌号信息以及被移动的次数。
class Car{
public:
    Car(std::string);
    void addMoveTime();
    void subMoveTime();
    int getTimes();
    std::string getNum();
private:
    std::string number;
    int move_times;
};

#endif // CAR_H_INCLUDED
