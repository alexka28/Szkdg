#include "GraphGen.h"
bool Graph::queryGraph(int v, int f, bool *ret)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
    }

     DFSUtil(v, visited, f, ret);

return *ret;
}

bool Graph::DFSUtil(int v, bool visited[], int f, bool *ret)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices
    // adjacent to this vertex
    std::list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if(*i == f)
        {
            *ret = true;

        }
        if(!visited[*i])
        {
            DFSUtil(*i, visited, f, ret);
        }

    }
    //return false;
}

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
