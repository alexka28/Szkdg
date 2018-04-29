#include "DecrementalGraph.h"
#include <iostream>
#include<set>
#include<stdlib.h>
#include<algorithm>
#include <utility>

/**
 * constructor for GraphNode
 * @param N: number of the neighbour levels
 */
GraphNode::GraphNode(int N) {
    this->N = N;
    neighbours = new std::set<GraphNode *>[N];
    std::set<GraphNode *> set;
    for (int i = 0; i < N; ++i) {
        this->neighbours[i] = set;
    }
}

DecGraph::DecGraph(int n) {
    this->logN = n;
    node = std::vector<GraphNode>();

//TODO: instead of 10 count logN
    GraphNode a_node(10);

    for (int i = 0; i < n; ++i) {
        this->node.push_back(a_node);
    }


}

bool DecGraph::connected(int, int) {
    //TODO: Et Forest
    //F.findRoot( F.first[u] ) == F.findRoot( F.first[v] )
}

void DecGraph::insert(int u, int v) {
    if (u == v) return;
    if (v < u) std::swap(u, v);
    if (level.count(std::make_pair(u, v)) > 0) { return; }
//beszurjuk logN szinttel, valamint a map-be is felvesszuk logN szinttel
    //TODO: indexelés logN méret?-e a tömb, vagy logN-ig indexelhet??
    node[u].neighbours[logN - 1].insert(new GraphNode(v));
    node[v].neighbours[logN - 1].insert(new GraphNode(u));
    std::pair<int, int> key(u, v);
    std::pair<std::pair<int, int>, int> key_value(key, this->logN);
    level.insert(key_value);
    //TODO: ET Forestet megirni, az alapjan a connected(u,v) fgv-t megirni
    /*
    if( !G.connected( u, v ) )
    {
      F.join(u,v);                           // F-be besz?rjuk, ?sszek?tve u-t ?s v-t
    } */

}

void DecGraph::remove(int u, int v) {
    if (u == v) return;
    if (v < u) std::swap(u, v);
    if (level.count(std::make_pair(u, v)) == 0) return;
    //kiszedjük a szintet
    int k = level.find(std::make_pair(u, v))->second;
    level.erase(std::make_pair(u, v));

    /* TODO: Et Forest ha kész
    if( !F.hasEdge( u, v ) ) return;
    F.remove( u, v );
    for( m := k .. logN )
    */
}