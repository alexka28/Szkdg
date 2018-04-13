#ifndef DECREMENTALGRAPH_H_INCLUDED
#define DECREMENTALGRAPH_H_INCLUDED
#include <set>
typedef struct GraphNode
{ int N;
  std::set< GraphNode* > *neighbours;
  GraphNode(int N);
}GraphNode;


#endif // DECREMENTALGRAPH_H_INCLUDED
