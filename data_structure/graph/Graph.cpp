#include "Graph.h"
#include <queue>
int const UNVISITED = 0;
int const VISITEDD = 1;
int const VISITEDB = 2;
int const INFINITE = 21474836;

Graph::~Graph(){                                       //����
    delete []mark;
    for(int i = 0; i < vexNum; i ++){                  //����ÿ�������Ӧ�ĳ���
        listNode* pointer = vertics[i]->firstout;
        while(pointer){
            listNode* node = pointer;
            pointer = pointer->tnext;
            delete node;
        }
        delete vertics[i];                             //������Ӧ����
    }
    delete []vertics;                                  //���������
}
void Graph::setEdge(int fromV, int toV, int weight){   //���һ����
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

void DFS(Graph &g, int v){                             //������ȱ���
    g.mark[v] = VISITEDD;
    cout<<g.vertics[v]->vexinfo<<" ";
    for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){
        if(g.mark[g.toVertex(e)] != VISITEDD)
           DFS(g, g.toVertex(e));
    }
}

void BFS(Graph &g, int v){                             //������ȱ���
    queue<int> q;
    g.mark[v] = VISITEDB;
    cout<<g.vertics[v]->vexinfo<<" ";                  //���ʶ���v����������־λ��v�����
    q.push(v);
    while(!q.empty()){                                 //�����������Ԫ��
        int v = q.front();                             //����Ԫ��
        q.pop();                                       //������
        for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){   //����õ����ڵ�ÿһ��δ���ʽ�㶼�����
            if(g.mark[g.toVertex(e)] != VISITEDB){
                g.mark[g.toVertex(e)] = VISITEDB;
                cout<<g.vertics[g.toVertex(e)]->vexinfo<<" ";
                q.push(g.toVertex(e));                 //�����
            }
        }
    }
}

int minVertex(Graph &g, Dist* &d){                     //����d������δ���ʹ������о�����С�Ķ���
    int minv = INFINITE;
    int vertex = -1;                                   //��¼��С���붥����±�
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

void Dijkstra(Graph &g, int s, Dist* &d){               //Dijkstra�㷨
    d = new Dist[g.vexNum];                             //���浽ǰһ������ĳ�����Ϣ
    listNode* pointer = NULL;
    for(int i = 0; i < g.vexNum; i ++){                 //��ʼ��mark���顢d���飬minVertex�����л��õ�mark�������Ϣ
        g.mark[i] = UNVISITED;
        d[i].length = INFINITE;
        d[i].pre = s;
    }
    pointer = g.vertics[s]->firstout;                   //��ʼ��d����
    while(pointer){
        int vex = pointer->tailvex;
        d[vex].length = pointer->arcinfo;
        pointer = pointer->tnext;
    }
    d[s].length = 0;
    for(int i = 0; i < g.vexNum; i ++){
        int v = minVertex(g, d);                        //�ҵ�����s��С�Ķ���
        if(d[v].length == INFINITE){
            cout<<s<<" -> "<<v<<" : INFINITY"<<endl;
            break;
        }
        g.mark[v] = VISITEDB;                           //�Ѹõ�����ѷ�����
        cout<<s<<" -> "<<v<<" : "<<d[v].length<<endl;   //��ӡ���
        //ˢ��d�е�ֵ����Ϊv�ļ���d��ֵ��Ҫ�ı�
        for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){    //ֻҪˢ����v���ڵĵ��ֵ
            if(d[g.toVertex(e)].length > (d[v].length + g.getWeight(e))){
                d[g.toVertex(e)].length = d[v].length + g.getWeight(e);
                d[g.toVertex(e)].pre = v;
            }
        }
    }
    delete [] d;
    d = NULL;
}

void Floyd(Graph &g, Dist** &d){                        //Floyd�㷨
    int i, j, v;
    d = new Dist*[g.vexNum];
    for(i = 0; i < g.vexNum; i ++){                     //����һ����άd���飬��¼��������Ϊʼ������·��
        d[i] = new Dist[g.vexNum];
    }
    for(i = 0; i < g.vexNum; i ++){                     //��ʼ��d����
        for(j = 0; j < g.vexNum; j ++){
            if(i == j){                                 //�Խ��߾���Ϊ�㣬�����ʼ��Ϊ����
                d[i][j].length = 0;
                d[i][j].pre = i;
            }else{
                d[i][j].length = INFINITE;
                d[i][j].pre = -1;
            }
        }
    }
    for(v = 0; v < g.vexNum; v ++){                     //��ÿ������ĳ���������Ӧλ��
        for(listNode* e = g.firstEdge(v); g.isEdge(e); e = g.nextEdge(e)){
            d[v][g.toVertex(e)].length = g.getWeight(e);
            d[v][g.toVertex(e)].pre = v;
        }
    }
    for(v = 0; v < g.vexNum; v ++){                     //����������������·����������v������ d[i][j].length>(d[i][v].length+d[v][j].length)
        for(i = 0; i < g.vexNum; i ++){
            for(j = 0; j < g.vexNum; j ++){
                if(d[i][j].length > (d[i][v].length + d[v][j].length)){
                    d[i][j].length = d[i][v].length + d[v][j].length;
                    d[i][j].pre = d[v][j].pre;
                }
            }
        }
    }
    for(i = 0; i < g.vexNum; i ++){                      //��ӡ���
        for(j = 0; j < g.vexNum; j ++){
            if(d[i][j].length != INFINITE)
                cout<<i<<" -> "<<j<<" : "<<d[i][j].length<<endl;
            else
                cout<<i<<" -> "<<j<<" : INFINITY"<<endl;
        }
    }
    for(i = 0; i < g.vexNum; i ++)                       //����
        delete [] d[i];
        d[i] = NULL;
    delete [] d;
    d = NULL;
}
