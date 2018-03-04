#include <iostream>
#include "UniFind.h"
#include <time.h>
#include <stdlib.h>
#include "CreateInsertQuery.h"
#include "GraphGen.h"

//a simple example creating a graph, a disjoint set, a list of inserts and queries
int main()
{
    Graph g(101);
    DisjointSets d(100);
    std::list <struct IQ> iqlist;
    iqlist = createIQ(100, 5000);
    bool *ret;
    ret = (bool*)malloc(sizeof(bool));
    *ret = false;
    std::list <struct IQ> ::iterator it;
    for(it = iqlist.begin(); it != iqlist.end(); ++it)
    {
        //an insert or on graph it's addedge
        if(it->iq == 0)
        {
            d.insert(it->a, it->b);
            g.addEdge(it->a, it->b);
        }
        //a query
        else
        {
            d.query(it->a, it->b);
            g.queryGraph(it->a, it->b, ret);
            //ret tracks if a query for a graph is true or false, and sets to true only if the nodes are in the same component
            *ret = false;

        }
    }

free(ret);
    return 0;
}
