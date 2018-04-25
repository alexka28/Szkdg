#include <iostream>
#include "DecrementalGraph.h"
#include<set>
#include "Test.h"

int main()
{
   /* DecGraph graph(10);
    GraphNode a(5);
    graph.node[0] = a;
    std::cout <<graph.node[0].N << std::endl;
    std::set<GraphNode*> setem;
    GraphNode b(5);
    GraphNode c(5);
    setem.insert(&b);
    std::cout << setem.size() << std::endl;
    std::cerr << a.neighbours[0].size() << std::endl;
    setem.insert(&c);
    a.neighbours[0] = setem;
    std::cout<<a.neighbours[0].size()<<std::endl;
    for(int i = 0; i < 5; ++i)
    {
        std::cout<<"Az " << i+1<< " neighbour merete: " << a.neighbours[i].size() << std::endl;
    }*/


    DecGraph graph(10);
    GraphNode a(7);
    GraphNode b(8);
    graph.node[0] = a;
    graph.node[0].neighbours[0].insert(&a);
    std::cout<<graph.node[0].neighbours[0].size() << std::endl;

    testInsert();
    return 0;
}
