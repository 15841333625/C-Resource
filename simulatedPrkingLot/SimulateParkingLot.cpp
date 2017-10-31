#include "SimulateParkingLot.h"

int const maxSize = 5;  //ÿ��ջ���5����

//�ж�һ����ų�����ջ�Ƿ�����
bool isFull(stack<Car*> car){
    return (car.size() == maxSize);
}

//����ͣ���� ����Ϊ����ջ�����ã����ƺţ�����ļ�������
void enter(stack<Car*> &cars, string license_plate, ofstream &fout){
    Car *newcar = new Car(license_plate);
    if(!isFull(cars)){                      //���ջδ��
        cars.push(newcar);
        newcar = NULL;
    }else{
        fout<<"Sorry PORSCHE, the lot is full!"<<endl;
    }
}

//�뿪ͣ���� ����Ϊ����ջ�����ã����ƺţ�����ļ�������
void leave(stack<Car*> &cars, string num, ofstream &fout){
    stack<Car*> temp;
    while(!cars.empty() && (cars.top()->getNum() != num)){
        temp.push(cars.top());
        cars.pop();
        temp.top()->addMoveTime();
    }
    if(cars.empty()){
        cout<<"δ�ҵ� "<<num<<endl;
        while(!temp.empty()){
            cars.push(temp.top());
            temp.pop();
            cars.top()->subMoveTime();
        }
    }else{
        //�����д�뵽�ļ���
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

//ģ��ͣ����
void SimulateParkingLot(const char* file_name){
    stack<Car*> cars;                              //��ʾͣ��ͨ��
    ifstream fin(file_name, ios::in);              //�����ȡ���ı��ļ�
    ofstream fout("output.txt", ios::ate);         //����д����ı��ļ������û�о��½�������о����
    char line[1024] = {0};                         //�����ȡһ�е��ı�����
    string license_plate = "";                     //��ų��ƺ�
    string action = "";                            //��ų�������
    if(fin){                                       //������ļ��ɹ�
        while(fin.getline(line, sizeof(line))){    //ѭ����ȡһ�е��ı�����
            stringstream word(line);               //��ÿ���ı��Զ����տո����
            word >> license_plate;                 //��ÿ�����ݷֱ��ŵ�����������
//            word.clear();
            word >> action;
//            word.clear();
            if(action == "arrives"){
                enter(cars, license_plate, fout);  //����ͣ����
            }else if(action == "departs"){
                leave(cars, license_plate, fout);  //�뿪ͣ����
            }else{
                cout<<"���ƺ� "<<license_plate<<" �ĳ�������δ���嶯����"<<endl;
                continue;
            }
        }
    }else{                                         //����ļ��򲻿����ṩ��ʾ��Ϣ
        cout<<"���ļ�ʧ�ܣ�"<<endl;
    }
    fin.clear();                                   //ˢ�»���
    fin.close();                                   //�ر�data�ļ�
    while(!cars.empty()){                          //�����Ȼ��ͣ�����е�������ǰ�ƶ��Ĵ���
        fout<<cars.top()->getNum()<<" was moved "<<cars.top()->getTimes()<<" times while it was here"<<endl;
        Car* tempcar = cars.top();
        cars.pop();
        delete tempcar;
        tempcar = NULL;
    }
    fout.close();                                  //�ر�output�ļ�
}
