#include "Graph.h"
#include <queue>
int const UNVISITED = 0;
int const VISITEDD = 1;
int const VISITEDB = 2;
int const INFINITE = 21474836;

Graph::~Graph(){                                       //析构
    delete []mark;
    for(int i = 0; i < vexNum; i ++){                  //析构每个顶点对应的出边
        listNode* pointer = vertics[i]->firstout;
        while(pointer){
            listNode* node = pointer;
            pointer = pointer->tnext;
            delete node;
        }
        delete vertics[i];                             //析构相应顶点
    }
    delete []vertics;                                  //析构顶点表
}
void Graph::setEdge(int fromV, int toV, int weight){   //添加一条边
    listNode * lnode = new listNode(toV, fromV, weight);
    if(vertics[fromV]->firstout == NULL)
        vertics[fromV]->firstout = lnode;
    else{
        listNode *pointer = vertics[fromV]->firstout;
        while(pointer->tnext)
            pointer = pointer->tnext;
        pointer->tnext = lnode;
    }
    if(vertics[toV]->firstin == NULL)
        vertics[toV]->firstin = lnode;
    else{
        listNode *pointer = vertics[toV]->firstin;
        while(pointer->hnext)
            pointer = pointer->hnext;
        pointer->hnext = lnode;
    }
    edgNum ++;
}

void DFS(Graph &g, int v){                             //深度优先遍历
    g.mark[v] = VISITEDD;
    cout<<g.vertics[v]->vexinfo<<" ";
    for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){
        if(g.mark[g.toVertex(e)] != VISITEDD)
           DFS(g, g.toVertex(e));
    }
}

void BFS(Graph &g, int v){                             //广度优先遍历
    queue<int> q;
    g.mark[v] = VISITEDB;
    cout<<g.vertics[v]->vexinfo<<" ";                  //访问顶点v，并标记其标志位，v入队列
    q.push(v);
    while(!q.empty()){                                 //如果队列仍有元素
        int v = q.front();                             //顶部元素
        q.pop();                                       //出队列
        for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){   //将与该点相邻的每一个未访问结点都入队列
            if(g.mark[g.toVertex(e)] != VISITEDB){
                g.mark[g.toVertex(e)] = VISITEDB;
                cout<<g.vertics[g.toVertex(e)]->vexinfo<<" ";
                q.push(g.toVertex(e));                 //入队列
            }
        }
    }
}

int minVertex(Graph &g, Dist* &d){                     //搜索d数组中未访问过顶点中距离最小的顶点
    int minv = INFINITE;
    int vertex = -1;                                   //记录最小距离顶点的下标
    for(int i = 0; i < g.vexNum; i ++){
        if(g.mark[i] == UNVISITED){
            if(minv >= d[i].length){
                minv = d[i].length;
                vertex = i;
            }
        }
    }
    return vertex;
}

void Dijkstra(Graph &g, int s, Dist* &d){               //Dijkstra算法
    d = new Dist[g.vexNum];                             //保存到前一个顶点的长度信息
    listNode* pointer = NULL;
    for(int i = 0; i < g.vexNum; i ++){                 //初始化mark数组、d数组，minVertex函数中会用到mark数组的信息
        g.mark[i] = UNVISITED;
        d[i].length = INFINITE;
        d[i].pre = s;
    }
    pointer = g.vertics[s]->firstout;                   //初始化d数组
    while(pointer){
        int vex = pointer->tailvex;
        d[vex].length = pointer->arcinfo;
        pointer = pointer->tnext;
    }
    d[s].length = 0;
    for(int i = 0; i < g.vexNum; i ++){
        int v = minVertex(g, d);                        //找到距离s最小的顶点
        if(d[v].length == INFINITE){
            cout<<s<<" -> "<<v<<" : INFINITY"<<endl;
            break;
        }
        g.mark[v] = VISITEDB;                           //把该点加入已访问组
        cout<<s<<" -> "<<v<<" : "<<d[v].length<<endl;   //打印输出
        //刷新d中的值，因为v的加入d的值需要改变
        for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){    //只要刷新与v相邻的点的值
            if(d[g.toVertex(e)].length > (d[v].length + g.getWeight(e))){
                d[g.toVertex(e)].length = d[v].length + g.getWeight(e);
                d[g.toVertex(e)].pre = v;
            }
        }
    }
    delete [] d;
    d = NULL;
}

void Floyd(Graph &g, Dist** &d){                        //Floyd算法
    int i, j, v;
    d = new Dist*[g.vexNum];
    for(i = 0; i < g.vexNum; i ++){                     //生成一个二维d数组，记录各个顶点为始点的最短路径
        d[i] = new Dist[g.vexNum];
    }
    for(i = 0; i < g.vexNum; i ++){                     //初始化d数组
        for(j = 0; j < g.vexNum; j ++){
            if(i == j){                                 //对角线距离为零，否则初始化为无穷
                d[i][j].length = 0;
                d[i][j].pre = i;
            }else{
                d[i][j].length = INFINITE;
                d[i][j].pre = -1;
            }
        }
    }
    for(v = 0; v < g.vexNum; v ++){                     //将每个顶点的出边填到矩阵对应位置
        for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){
            d[v][g.toVertex(e)].length = g.getWeight(e);
            d[v][g.toVertex(e)].pre = v;
        }
    }
    for(v = 0; v < g.vexNum; v ++){                     //如果两个顶点间的最短路径经过顶点v，则有 d[i][j].length>(d[i][v].length+d[v][j].length)
        for(i = 0; i < g.vexNum; i ++){
            for(j = 0; j < g.vexNum; j ++){
                if(d[i][j].length > (d[i][v].length + d[v][j].length)){
                    d[i][j].length = d[i][v].length + d[v][j].length;
                    d[i][j].pre = d[v][j].pre;
                }
            }
        }
    }
    for(i = 0; i < g.vexNum; i ++){                      //打印输出
        for(j = 0; j < g.vexNum; j ++){
            if(d[i][j].length != INFINITE)
                cout<<i<<" -> "<<j<<" : "<<d[i][j].length<<endl;
            else
                cout<<i<<" -> "<<j<<" : INFINITY"<<endl;
        }
    }
    for(i = 0; i < g.vexNum; i ++)                       //析构
        delete [] d[i];
        d[i] = NULL;
    delete [] d;
    d = NULL;
}
