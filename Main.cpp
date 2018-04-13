#include <iostream>
#include "DecrementalGraph.h"
#include<set>
#include "Test.h"

int main()
{
    GraphNode a(5);
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
    }
    testInsert();
    return 0;
}
