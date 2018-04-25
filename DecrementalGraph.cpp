#include "DecrementalGraph.h"
#include <iostream>
#include<set>
#include<stdlib.h>
#include<algorithm>

GraphNode::GraphNode(int N)
{
    this->N = N;
    neighbours = new std::set<GraphNode*>[N];
    std::set<GraphNode*> set;
    for(int i = 0; i < N; ++i)
    {
        this->neighbours[i] =   set;
    }
}

DecGraph::DecGraph(int n)
{
    node = (GraphNode*)malloc(sizeof(GraphNode)*n);
    /*GraphNode a_node(10);
    for(int i = 0; i<n ; ++i){
        this->node[i] =  a_node;
    }*/



}
void DecGraph::insert(int u, int v)
{
    if( u == v ) return;
    if( v < u ) std::swap( u,v );
    //node[u].neighbours[0].insert(new GraphNode(v));
    //node[v].neighbours[0].insert(new GraphNode(u));
    /* legyen elöl a kisebb az utolsó sorban is */
    /*if( G.level.hasKey( ( u,v ) ) ) return;
    if( !G.connected( u, v ) )
    {
      F.join(u,v);                           // F-be beszúrjuk, összekötve u-t és v-t
    } */

}
