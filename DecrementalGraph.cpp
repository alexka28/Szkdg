#include "DecrementalGraph.h"
#include <iostream>
#include<set>
GraphNode::GraphNode(int N)
{
    this->N = N;
    neighbours = new std::set<GraphNode*>[N];
    std::set<GraphNode*> set;
   for(int i = 0; i < N; ++i)
    {
        this->neighbours[i] =   set;
    }
}
