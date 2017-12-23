#include "Graph.h"

int main()
{
//    Graph g(8);
//    g.setEdge(0, 1);
//    g.setEdge(0, 2);
//    g.setEdge(1, 3);
//    g.setEdge(3, 7);
//    g.setEdge(7, 4);
//    g.setEdge(4, 1);
//    g.setEdge(2, 5);
//    g.setEdge(2, 6);
//    g.setEdge(5, 6);
//    DFS(g, 0);
//    cout<<endl;
//    BFS(g, 0);
//    cout<<endl;

    Graph g(6);
    g.setEdge(0, 2, 10);
    g.setEdge(0, 4, 30);
    g.setEdge(0, 5, 100);
    g.setEdge(1, 2, 5);
    g.setEdge(2, 3, 50);
    g.setEdge(3, 5, 10);
    g.setEdge(4, 3, 20);
    Dist *d;
    Dist **dd;
    cout<<"Dijkstra 0:"<<endl;
    Dijkstra(g, 0, d);
    cout<<"Floyd :"<<endl;
    Floyd(g, dd);

    return 0;
}
