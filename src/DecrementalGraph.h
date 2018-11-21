#ifndef DECREMENTALGRAPH_H_INCLUDED
#define DECREMENTALGRAPH_H_INCLUDED

#include <set>
#include<map>
#include<utility>
#include <vector>
#include "ETT.h"

typedef struct GraphNode {
    int N;
    int id;
    std::set<GraphNode *> *neighbours;

    GraphNode(int N);
} GraphNode;
typedef struct DecGraph {
    int logN;
    std::vector<GraphNode> node;
    std::map<std::pair<int, int>, int> level;

    DecGraph(int n);

    bool connected(int, int, ETForest);

    void insert(int, int, ETForest);

    void remove(int, int, ETForest& F);

    ETTreeNode *firstSeen(int, int, ETForest&);

    ETTreeNode *firstSeen(ETTreeNode *, int, ETForest&);

    void dfsETLimit(int u, int m, ETForest);

    bool dfsETLimit2(int u, int m,int, ETForest&);

    ETTreeNode *getSmallerTree(ETTreeNode *lhs, ETTreeNode *rhs, int m, ETForest&);

    ETTreeNode *step(ETTreeNode *pNode, int m, ETForest& F);
} DecGraph;


#endif // DECREMENTALGRAPH_H_INCLUDED
