#ifndef GRAPHGEN_H_INCLUDED
#define GRAPHGEN_H_INCLUDED
#include <list>
class Graph
{
    int V;    // No. of vertices

    std::list<int> *adj; // Pointer to an array containing adjacency lists
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);
    int getV();
    std::list<int>* getList();
    void deleteEdge(int v, int w);
};

#endif // GRAPHGEN_H_INCLUDED
