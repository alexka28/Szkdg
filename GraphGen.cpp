#include "GraphGen.h"
Graph::Graph(int V)
{
    this->V = V;
    adj = new std::list<int>[V];
}

// method to add an undirected edge
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::deleteEdge(int v, int w) {
    adj[v].remove(w);
    adj[w].remove(v);
}
int Graph::getV()
{
    return this->V;
}
std::list<int>* Graph::getList()
{
    return adj;
}
