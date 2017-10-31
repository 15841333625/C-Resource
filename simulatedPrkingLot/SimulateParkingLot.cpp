#include "SimulateParkingLot.h"

int const maxSize = 5;  //每个栈存放5辆车

//判断一个存放车辆的栈是否满了
bool isFull(stack<Car*> car){
    return (car.size() == maxSize);
}

//进入停车场 参数为车辆栈的引用，车牌号，输出文件的引用
void enter(stack<Car*> &cars, string license_plate, ofstream &fout){
    Car *newcar = new Car(license_plate);
    if(!isFull(cars)){                      //如果栈未满
        cars.push(newcar);
        newcar = NULL;
    }else{
        fout<<"Sorry PORSCHE, the lot is full!"<<endl;
    }
}

//离开停车场 参数为车辆栈的引用，车牌号，输出文件的引用
void leave(stack<Car*> &cars, string num, ofstream &fout){
    stack<Car*> temp;
    while(!cars.empty() && (cars.top()->getNum() != num)){
        temp.push(cars.top());
        cars.pop();
        temp.top()->addMoveTime();
    }
    if(cars.empty()){
        cout<<"未找到 "<<num<<endl;
        while(!temp.empty()){
            cars.push(temp.top());
            temp.pop();
            cars.top()->subMoveTime();
        }
    }else{
        //将输出写入到文件中
        fout<<cars.top()->getNum()<<" was moved "<<cars.top()->getTimes()<<" times while it was here"<<endl;
        Car* tempcar = cars.top();
        cars.pop();
        delete tempcar;
        tempcar = NULL;
        while(!temp.empty()){
            cars.push(temp.top());
            temp.pop();
        }
    }
}

//模拟停车场
void SimulateParkingLot(const char* file_name){
    stack<Car*> cars;                              //表示停车通道
    ifstream fin(file_name, ios::in);              //定义读取的文本文件
    ofstream fout("output.txt", ios::ate);         //定义写入的文本文件，如果没有就新建，如果有就清空
    char line[1024] = {0};                         //定义读取一行的文本变量
    string license_plate = "";                     //存放车牌号
    string action = "";                            //存放车辆动作
    if(fin){                                       //如果打开文件成功
        while(fin.getline(line, sizeof(line))){    //循环读取一行的文本变量
            stringstream word(line);               //将每行文本自动按照空格分列
            word >> license_plate;                 //将每行数据分别存放到两个变量中
//            word.clear();
            word >> action;
//            word.clear();
            if(action == "arrives"){
                enter(cars, license_plate, fout);  //进入停车场
            }else if(action == "departs"){
                leave(cars, license_plate, fout);  //离开停车场
            }else{
                cout<<"车牌号 "<<license_plate<<" 的车辆存在未定义动作！"<<endl;
                continue;
            }
        }
    }else{                                         //如果文件打不开，提供提示信息
        cout<<"打开文件失败！"<<endl;
    }
    fin.clear();                                   //刷新缓存
    fin.close();                                   //关闭data文件
    while(!cars.empty()){                          //输出仍然在停车场中的汽车当前移动的次数
        fout<<cars.top()->getNum()<<" was moved "<<cars.top()->getTimes()<<" times while it was here"<<endl;
        Car* tempcar = cars.top();
        cars.pop();
        delete tempcar;
        tempcar = NULL;
    }
    fout.close();                                  //关闭output文件
}
