#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
using namespace std;

class Graph;
class listNode;

//头结点
class vertexNode{
public:
    int vexinfo;          //顶点的信息
    listNode* firstin;    //第一条关联入弧的信息
    listNode* firstout;   //第一条关联出弧的信息
public:
    vertexNode(int data = 0){
        vexinfo = data;
        firstin = firstout = NULL;
    }
    void setData(int data){
        vexinfo = data;
    }
};

//十字链表结点
class listNode{
public:
    int tailvex;          //弧尾顶点的位置
    int headvex;          //弧头顶点的位置
    int arcinfo;          //弧的信息
    listNode* tnext;      //弧尾相同的下一条弧
    listNode* hnext;      //弧头相同的下一条弧
public:
    listNode(int tailvex, int headvex, int data):tailvex(tailvex), headvex(headvex), arcinfo(data){
        tnext = hnext = NULL;
    }
};

//十字链表存储数据
class Graph{
public:
    vertexNode **vertics; //顶点表
    int vexNum;           //顶点个数
    int edgNum;           //边条数
    int *mark;            //标记某定点是否访问过
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
    int verticsNum(){              //返回图的顶点个数
        return vexNum;
    }
    int edgesNum(){                //返回图的边数
        return edgNum;
    }
    listNode* firstEdge(int oneVertex){      //返回与顶点oneVertex相关联的第一条边
        return vertics[oneVertex]->firstout;
    }
    listNode* nextEdge(listNode* preEdge){   //返回与边preEdge有相同关联顶点oneVertex的下一条边
        return preEdge->tnext;
    }
    void setEdge(int fromV, int toV, int weight = 0);   //添加一条边
    bool isEdge(listNode* oneEdge){           //判断onEdge是否为一条边
        return (oneEdge == NULL)?false:true;
    }
    int fromVertex(listNode* oneEdge){        //返回oneEdge的始点
        return oneEdge->headvex;
    }
    int toVertex(listNode* oneEdge){          //返回oneEdge的终点
        return oneEdge->tailvex;
    }
    int getWeight(listNode* oneEdge){         //返回oneEdge的权
        return oneEdge->arcinfo;
    }
};

class Dist{
public:
    int length;  //与源s的距离
    int pre;     //前面的顶点
};

extern void DFS(Graph &g, int v);
extern void BFS(Graph &g, int v);
extern void Dijkstra(Graph &g, int s, Dist* &d);
extern void Floyd(Graph &g, Dist** &d);

#endif // GRAPH_H_INCLUDED
