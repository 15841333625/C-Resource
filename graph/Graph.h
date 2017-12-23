#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
using namespace std;

class Graph;
class listNode;

//ͷ���
class vertexNode{
public:
    int vexinfo;          //�������Ϣ
    listNode* firstin;    //��һ�������뻡����Ϣ
    listNode* firstout;   //��һ��������������Ϣ
public:
    vertexNode(int data = 0){
        vexinfo = data;
        firstin = firstout = NULL;
    }
    void setData(int data){
        vexinfo = data;
    }
};

//ʮ��������
class listNode{
public:
    int tailvex;          //��β�����λ��
    int headvex;          //��ͷ�����λ��
    int arcinfo;          //������Ϣ
    listNode* tnext;      //��β��ͬ����һ����
    listNode* hnext;      //��ͷ��ͬ����һ����
public:
    listNode(int tailvex, int headvex, int data):tailvex(tailvex), headvex(headvex), arcinfo(data){
        tnext = hnext = NULL;
    }
};

//ʮ������洢����
class Graph{
public:
    vertexNode **vertics; //�����
    int vexNum;           //�������
    int edgNum;           //������
    int *mark;            //���ĳ�����Ƿ���ʹ�
public:
    Graph(int num){
        vertics = new vertexNode*[num];
        for(int i = 0; i < num; i ++){
            vertics[i] = new vertexNode(i);
        }
        mark = new int[num];
        vexNum = num;
        edgNum = 0;
    }
    ~Graph();
    void destroy(int v);
    int verticsNum(){              //����ͼ�Ķ������
        return vexNum;
    }
    int edgesNum(){                //����ͼ�ı���
        return edgNum;
    }
    listNode* firstEdge(int oneVertex){      //�����붥��oneVertex������ĵ�һ����
        return vertics[oneVertex]->firstout;
    }
    listNode* nextEdge(listNode* preEdge){   //�������preEdge����ͬ��������oneVertex����һ����
        return preEdge->tnext;
    }
    void setEdge(int fromV, int toV, int weight = 0);   //���һ����
    bool isEdge(listNode* oneEdge){           //�ж�onEdge�Ƿ�Ϊһ����
        return (oneEdge == NULL)?false:true;
    }
    int fromVertex(listNode* oneEdge){        //����oneEdge��ʼ��
        return oneEdge->headvex;
    }
    int toVertex(listNode* oneEdge){          //����oneEdge���յ�
        return oneEdge->tailvex;
    }
    int getWeight(listNode* oneEdge){         //����oneEdge��Ȩ
        return oneEdge->arcinfo;
    }
};

class Dist{
public:
    int length;  //��Դs�ľ���
    int pre;     //ǰ��Ķ���
};

extern void DFS(Graph &g, int v);
extern void BFS(Graph &g, int v);
extern void Dijkstra(Graph &g, int s, Dist* &d);
extern void Floyd(Graph &g, Dist** &d);

#endif // GRAPH_H_INCLUDED
