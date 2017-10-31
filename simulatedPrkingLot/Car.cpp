#include "Car.h"

Car::Car(std::string num):number(num){
    move_times = 0;
}
void Car::addMoveTime(){
    move_times ++;
}
void Car::subMoveTime(){
    move_times --;
}
int Car::getTimes(){
    return move_times;
}
std::string Car::getNum(){
    return number;
}
