#ifndef DECREMENTALGRAPH_H_INCLUDED
#define DECREMENTALGRAPH_H_INCLUDED
#include <set>
#include<map>
#include<utility>


typedef struct GraphNode
{ int N;
  std::set< GraphNode* > *neighbours;
  GraphNode(int N);
}GraphNode;
typedef struct DecGraph
{
GraphNode *node;
std::map< std::pair<int, int> , int > level;
DecGraph(int n);
void insert(int, int);
}DecGraph;


#endif // DECREMENTALGRAPH_H_INCLUDED
