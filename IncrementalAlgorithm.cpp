#include "UniFind.h"
#include "GraphGen.h"
#include "CreateInsertQuery.h"
#include <iostream>
#include "DFS.h"


void incrementalAlgorithm(DisjointSets d,Graph g, std::list <struct IQ> iqlist)
{
    std::list <struct IQ> ::iterator it;
    for(it = iqlist.begin(); it != iqlist.end(); ++it)
    {
        if(it->iq == 0)
        {
            d.insert(it->a, it->b);
            g.addEdge(it->a, it->b);
        }
        else
        {
            d.query(it->a, it->b);

        }
    }
}
