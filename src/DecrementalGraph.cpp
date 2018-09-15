#include "DecrementalGraph.h"
#include <iostream>
#include<set>
#include<stdlib.h>
#include<algorithm>
#include <utility>
#include "ETT.h"
#include <cmath>
#include "ETTQueries.h"
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
    //TODO: indexel�s logN m�ret?-e a t�mb, vagy logN-ig indexelhet??
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
        F.insert(u, v);                          // F-be besz�rjuk, �sszek�tve u-t �s v-t
    }

}

void DecGraph::remove(int u, int v, ETForest F) {
    if (u == v) return;
    if (v < u) std::swap(u, v);
    if (level.count(std::make_pair(u, v)) == 0) return;
    //kiszedj�k a szintet
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
    ETTreeNode *pv = predecessor(pNode);
    if (pv == nullptr) return pNode;
    //van-e a kulcshoz �rt�k
    if (level.count(std::make_pair(u, pv->nodeId)) > 0) {
        //ha van szedj�k ki a szintet

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
/* itt elv�gezz�k, amit u-val tenni akarunk, pl a r� illeszked? m szint? �leket cs�kkentj�k stb */
    ETTreeNode *pNode = F.first[u];
    ETTreeNode *qNode;
    int v;
    while (pNode != F.last[u]) /* bej�rjuk az u aktu�lis pNode visitje ut�n k�vetkez? cs�csot*/
    {
        qNode = successor(
                pNode);  /*tkp jobbr�l balra is bej�rhatn�nk, ha erre az egy c�lra k�ne a successor -- mindegy */
        v = qNode->nodeId;
        if (level.count(std::make_pair(u, v)) > 0) {
            if (level.find(std::make_pair(u, v))->second <= m) {
                dfsETLimit(v, m, F);
            }
        }
//        if (level(u, v) <= m)  {    /*ha oda tudunk l�pni, akkor bej�rjuk */
//            dfsETLimit(v);}
        pNode = successor(
                F.last[v]); /*ak�r bej�rtuk, ak�r nem, visszal�p�nk u-ra v bej�r�sa ut�n �s n�zz�k a k�vetkez? szomsz�dot */
    }
}

bool DecGraph::dfsETLimit2(int u, int m, int v, ETForest F) {
    ETTreeNode *pNode = firstSeen(u, m, F);
    std::set<GraphNode *>::iterator it;
    int z, w;
    while (pNode != nullptr) {
        w = pNode->nodeId;
/* itt elv�gezz�k pNode->nodeId-vel, amit a cs�csokkal tenni akarunk */
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
    ETTreeNode *pNode = firstSeen(lhs, m, F);  //a f�k bej�r�s�t a legkor�bban l�tott cs�csukb�l ind�tjuk
    ETTreeNode *qNode = firstSeen(rhs, m, F);
    while ((pNode != nullptr) && (qNode != nullptr)) {
        pNode = step(pNode, m, F);
        qNode = step(qNode, m, F);
    }
    if (pNode == nullptr) return lhs;  // lhs f�ja fogyott el el?bb
    return rhs;                         // rhs f�ja fogyott el el?bb
}

ETTreeNode *DecGraph::step(ETTreeNode *pNode, int m, ETForest F) {
    int u = pNode->nodeId;
    int v;
    ETTreeNode *qNode;
    //ha van <=m �les, pNode->nodeId ut�n megl�togatott szomsz�dja, oda l�p�nk
    // itt pNode a cs�cs�nak a first-je
    while (pNode != F.last[u]) {
        qNode = successor(pNode);
        v = qNode->nodeId;
//        if( level(u,v) <= m ) return qNode;
        if (level.count(std::make_pair(u, v)) > 0 && level.find(std::make_pair(u, v))->second <= m) {
            return qNode;
        }
        pNode = successor(F.last[v]);
    }
    //nincs -> visszal�peget�nk felfele a f�ban, am�g utols� gyerekek vagyunk
    //  itt pNode a cs�cs�nak m�r a last-ja
    while (true) {
        qNode = successor(pNode); // innen j�tt�nk p-be, ez a p ut�ni visit, ha ez az �l max m szint?
        if (qNode == nullptr) return nullptr; //esetleg nem is l�tezik
        if (level.count(std::make_pair(u, qNode->nodeId)) > 0 &&
            level.find(std::make_pair(u, qNode->nodeId))->second > m) {
            return nullptr;
        }
//        if( level(u,qNode->nodeId) > m ) return nullptr; //ez m�r neh�z �l apa ir�nyba, v�gezt�nk
        //keres�nk qNode-nak pNode ut�ni gyerek�t, amire le tudunk l�pni
        pNode = qNode;
        u = pNode->nodeId;
        while (pNode != F.last[pNode->nodeId]) {
            qNode = successor(pNode);
            v = qNode->nodeId;
            if (level.count(std::make_pair(u, v)) > 0 && level.find(std::make_pair(u, v))->second <= m) {
                return qNode;
            }
//            if( level(u,v) <= m ) return qNode; //siker�lt tal�lni u apj�nak egy k�vetkez? gyerek�t
            pNode = successor(F.last[v]);   //v-re nem l�phet�nk �t, ugorjuk �t a bej�r�s�t �s next
        }
        //ha itt j�runk, akkor m�r bej�rtuk pNode apj�nak az �sszes gyerek�t, mehet a whiletrue ciklus m�g egyszer
    }
}