#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <string>

//������ʵ����Car��Car������Ҫ��ų��ĳ��ƺ���Ϣ�Լ����ƶ��Ĵ�����
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
