#include "TraditionalAlgorithm.h"
#include "DFS.h"

#include <iostream>

void traditionalAlgorithm(Graph g, std::list <struct IQ> iqlist, bool *ret)
{
    std::list <struct IQ> ::iterator it;
    for(it = iqlist.begin(); it != iqlist.end(); ++it)
    {
        if(it->iq == 0)
        {
            g.addEdge(it->a, it->b);
        }
        else
        {
            queryGraph(g, it->a, it->b, ret);
            // ret tracks if a query for a graph is true or false, and sets to true only if the nodes are in the same component
            *ret = false;
        }
    }
}
