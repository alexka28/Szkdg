#ifndef GRAPHGEN_H_INCLUDED
#define GRAPHGEN_H_INCLUDED
#include <list>
class Graph
{
    int V;    // No. of vertices

    // Pointer to an array containing adjacency lists
    std::list<int> *adj;

    // A function used by DFS
    bool DFSUtil(int v, bool visited[], int f, bool *ret);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);
    //a bool ptr to track the query
    bool queryGraph(int v, int f, bool *ret);
};


#endif // GRAPHGEN_H_INCLUDED
