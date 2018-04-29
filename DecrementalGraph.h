#ifndef DECREMENTALGRAPH_H_INCLUDED
#define DECREMENTALGRAPH_H_INCLUDED
#include <set>
#include<map>
#include<utility>
#include <vector>

typedef struct GraphNode
{ int N;
  std::set< GraphNode* > *neighbours;
  GraphNode(int N);
}GraphNode;
typedef struct DecGraph
{int logN;
std::vector<GraphNode> node;
std::map< std::pair<int, int> , int > level;
DecGraph(int n);
bool connected(int, int);
void insert(int, int);
void remove(int,int);
}DecGraph;


#endif // DECREMENTALGRAPH_H_INCLUDED
