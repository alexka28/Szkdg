#include "DecrementalGraph.h"
#include <iostream>
#include<set>
#include<stdlib.h>
#include<algorithm>
#include <utility>
#include "ETT.h"
#include <cmath>
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
    double tmpLog = log2(n);
    this->logN = ceil(tmpLog);
    node = std::vector<GraphNode>();

//TODO: instead of 10 count logN
    GraphNode a_node(logN);

    for (int i = 0; i < n; ++i) {
        this->node.push_back(a_node);
    }


}

bool DecGraph::connected(int u, int v, ETForest F) {
    return F.findRoot(u) == F.findRoot(v);
}

void DecGraph::insert(int u, int v, ETForest F) {
    if (u == v) return;
    if (v < u) std::swap(u, v);
    if (level.count(std::make_pair(u, v)) > 0) { return; }
//beszurjuk logN szinttel, valamint a map-be is felvesszuk logN szinttel
    //TODO: indexelés logN méret?-e a tömb, vagy logN-ig indexelhet??
    GraphNode *uNode = new GraphNode(logN);
    GraphNode *vNode = new GraphNode(logN);
    uNode->id = u;
    vNode->id = v;
    node[u].neighbours[logN - 1].insert(vNode);
    node[v].neighbours[logN - 1].insert(uNode);
    std::pair<int, int> key(u, v);
    std::pair<std::pair<int, int>, int> key_value(key, this->logN);
    level.insert(key_value);


    if (!connected(u, v, F)) {
        F.insert(u, v);                          // F-be beszúrjuk, összekötve u-t és v-t
    }

}

void DecGraph::remove(int u, int v, ETForest F) {
    if (u == v) return;
    if (v < u) std::swap(u, v);
    if (level.count(std::make_pair(u, v)) == 0) return;
    //kiszedjük a szintet
    int k = level.find(std::make_pair(u, v))->second;
    level.erase(std::make_pair(u, v));
    if (F.contains(u, v)) { return; }
    F.remove(u, v);

    ETTreeNode *smallerTree;
    int biggerTreeId;
    for (int m = k; m < logN; ++m) {
        smallerTree = getSmallerTree(F.first[u], F.first[v], k, F);
        if (smallerTree->nodeId == u) {
            biggerTreeId = v;
        } else {
            biggerTreeId = u;
        }
        if (dfsETLimit2(smallerTree->nodeId, m, biggerTreeId, F)) {
            break;
        }
    }
}

ETTreeNode *DecGraph::firstSeen(int u, int m, ETForest F) {
    ETTreeNode *pNode = F.first[u];
    ETTreeNode *pv = F.predecessor(pNode);
    if (pv == nullptr) return pNode;
    //van-e a kulcshoz érték
    if (level.count(std::make_pair(u, pv->nodeId)) > 0) {
        //ha van szedjük ki a szintet

        if (level.find(std::make_pair(u, pv->nodeId))->second > m) {
            return pNode;
        }
    }
    return firstSeen(pv->nodeId, m, F);

}

ETTreeNode *DecGraph::firstSeen(ETTreeNode *pNode, int m, ETForest F) {
    return firstSeen(pNode->nodeId, m, F);
}

void DecGraph::dfsETLimit(int u, int m, ETForest F) {
/* itt elvégezzük, amit u-val tenni akarunk, pl a rá illeszked? m szint? éleket csökkentjük stb */
    ETTreeNode *pNode = F.first[u];
    ETTreeNode *qNode;
    int v;
    while (pNode != F.last[u]) /* bejárjuk az u aktuális pNode visitje után következ? csúcsot*/
    {
        qNode = F.successor(
                pNode);  /*tkp jobbról balra is bejárhatnánk, ha erre az egy célra kéne a successor -- mindegy */
        v = qNode->nodeId;
        if (level.count(std::make_pair(u, v)) > 0) {
            if (level.find(std::make_pair(u, v))->second <= m) {
                dfsETLimit(v, m, F);
            }
        }
//        if (level(u, v) <= m)  {    /*ha oda tudunk lépni, akkor bejárjuk */
//            dfsETLimit(v);}
        pNode = F.successor(
                F.last[v]); /*akár bejártuk, akár nem, visszalépünk u-ra v bejárása után és nézzük a következ? szomszédot */
    }
}

bool DecGraph::dfsETLimit2(int u, int m, int v, ETForest F) {
    ETTreeNode *pNode = firstSeen(u, m, F);
    std::set<GraphNode *>::iterator it;
    int z, w;
    while (pNode != nullptr) {
        w = pNode->nodeId;
/* itt elvégezzük pNode->nodeId-vel, amit a csúcsokkal tenni akarunk */
        if (m > 0) {
            for (it = node[w].neighbours[m].begin(); it != node[w].neighbours[m].end(); ++it) {
                z = (*it)->id;
                node[w].neighbours[m - 1].insert(*it);

                if (w > z) {
                    if (level.count(std::make_pair(z, w)) > 0) {
                        level.erase(std::make_pair(z, w));
                    }
                    level.insert(std::make_pair(std::make_pair(z, w), m - 1));
                } else {
                    if (level.count(std::make_pair(w, z)) > 0) {
                        level.erase(std::make_pair(w, z));
                    }

                    level.insert(std::make_pair(std::make_pair(w, z), m - 1));
                }
                if (F.findRoot(w) != F.findRoot(z) && F.findRoot(v) == F.findRoot(z)) {
                    F.insert(w, z);
                    return true;
                }
                node[w].neighbours[m].erase(*it);
            }
        } else {
            for (it = node[w].neighbours[m].begin(); it != node[w].neighbours[m].end(); ++it) {
                z = (*it)->id;


                if (F.findRoot(w) != F.findRoot(z) && F.findRoot(v) == F.findRoot(z)) {
                    F.insert(w, z);
                    return true;
                }
            }
        }

        pNode = step(pNode, m, F);
    }

    return false;
}

ETTreeNode *DecGraph::getSmallerTree(ETTreeNode *lhs, ETTreeNode *rhs, int m, ETForest F) {
    ETTreeNode *pNode = firstSeen(lhs, m, F);  //a fák bejárását a legkorábban látott csúcsukból indítjuk
    ETTreeNode *qNode = firstSeen(rhs, m, F);
    while ((pNode != nullptr) && (qNode != nullptr)) {
        pNode = step(pNode, m, F);
        qNode = step(qNode, m, F);
    }
    if (pNode == nullptr) return lhs;  // lhs fája fogyott el el?bb
    return rhs;                         // rhs fája fogyott el el?bb
}

ETTreeNode *DecGraph::step(ETTreeNode *pNode, int m, ETForest F) {
    int u = pNode->nodeId;
    int v;
    ETTreeNode *qNode;
    //ha van <=m éles, pNode->nodeId után meglátogatott szomszédja, oda lépünk
    // itt pNode a csúcsának a first-je
    while (pNode != F.last[u]) {
        qNode = F.successor(pNode);
        v = qNode->nodeId;
//        if( level(u,v) <= m ) return qNode;
        if (level.count(std::make_pair(u, v)) > 0 && level.find(std::make_pair(u, v))->second <= m) {
            return qNode;
        }
        pNode = F.successor(F.last[v]);
    }
    //nincs -> visszalépegetünk felfele a fában, amíg utolsó gyerekek vagyunk
    //  itt pNode a csúcsának már a last-ja
    while (true) {
        qNode = F.successor(pNode); // innen jöttünk p-be, ez a p utáni visit, ha ez az él max m szint?
        if (qNode == nullptr) return nullptr; //esetleg nem is létezik
        if (level.count(std::make_pair(u, qNode->nodeId)) > 0 &&
            level.find(std::make_pair(u, qNode->nodeId))->second > m) {
            return nullptr;
        }
//        if( level(u,qNode->nodeId) > m ) return nullptr; //ez már nehéz él apa irányba, végeztünk
        //keresünk qNode-nak pNode utáni gyerekét, amire le tudunk lépni
        pNode = qNode;
        u = pNode->nodeId;
        while (pNode != F.last[pNode->nodeId]) {
            qNode = F.successor(pNode);
            v = qNode->nodeId;
            if (level.count(std::make_pair(u, v)) > 0 && level.find(std::make_pair(u, v))->second <= m) {
                return qNode;
            }
//            if( level(u,v) <= m ) return qNode; //sikerült találni u apjának egy következ? gyerekét
            pNode = F.successor(F.last[v]);   //v-re nem léphetünk át, ugorjuk át a bejárását és next
        }
        //ha itt járunk, akkor már bejártuk pNode apjának az összes gyerekét, mehet a whiletrue ciklus még egyszer
    }
}