#include "DFS.h"
#include "GraphGen.h"
bool queryGraph(Graph g, int v, int f, bool *ret)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[g.getV()];
    for(int i = 0; i < g.getV(); i++)
    {
        visited[i] = false;
    }

    DFSUtil(g, v, visited, f, ret);

    return *ret;
}

bool DFSUtil(Graph g, int v, bool visited[], int f, bool *ret)
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices
    // adjacent to this vertex
    std::list<int>::iterator i;

    for(i = g.getList()[v].begin(); i != g.getList()[v].end(); ++i)
    {
        if(*i == f)
        {
            *ret = true;

        }
        if(!visited[*i])
        {
            DFSUtil(g, *i, visited, f, ret);
        }

    }
}
