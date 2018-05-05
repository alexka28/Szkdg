#include <iostream>
#include "ETT.h"

const int BLACK = 0, RED = 1;

ETTreeNode::ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color) {
    this->parent = parent;
    this->left = left;
    this->right = right;
    this->color = color;
}

ETTreeNode::ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color, int nodeId) {
    this->parent = parent;
    this->left = left;
    this->right = right;
    this->color = color;
    this->nodeId = nodeId;
}

//egy üres node
ETTreeNode theNullNode(nullptr, nullptr, nullptr, 0);

ETForest::ETForest(int n) {
    first = new ETTreeNode *[n];
    last = new ETTreeNode *[n];
    for (int i = 0; i < n; ++i) {
        ETTreeNode *node = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, i);
        first[i] = node;
        last[i] = node;
    }

}

ETTreeNode *ETForest::findRoot(int u) {
    ETTreeNode *pNode = this->first[u];
    while (pNode->parent != nullptr) {

        pNode = pNode->parent;

    }

    return pNode;
}

bool ETForest::contains(int u, int v) {
    /* return  F.predecessor( F.first[u] ) -> nodeId == v  // ha létezik; null-check is kell
             ||F.predecessor( F.first[v] ) -> nodeId == u*/
}

void ETForest::join(int u, int v) {
    ETTreeNode *root1 = findRoot(u);
    ETTreeNode *root2 = findRoot(v);
    int bh1 = root1->rank;
    int bh2 = root2->rank;

    if (bh1 >= bh2) {
        //keressük meg root1 maxját
        while (root1->right != &theNullNode) {
            root1 = root1->right;
        }
        //ha megvan ragasszuk hozzá a root2-t
        root1->right = root2;

        root2->parent = root1;

        //TODO: szinek javítása
    } else {
        while (root2->right != nullptr) {
            root2 = root2->right;
        }
        root2->right = root1;
        root1->parent = root2;
        //TODO: szinek javítása
    }


}

void ETForest::rotateLeft(ETTreeNode *pNode) {
    ETTreeNode *x = pNode->left,
            *y = pNode->right,
            *z = y->left,
            *w = y->right;
    z->parent = pNode;
    y->parent = pNode->parent;
    y->left = pNode;
    if (pNode->parent != nullptr)
        if (pNode == pNode->parent->left)
            pNode->parent->left = y;
        else
            pNode->parent->right = y;
    pNode->parent = y;
    pNode->right = z;
    updateRank(pNode);
}

//TODO: nullNode check
void ETForest::rotateRight(ETTreeNode *pNode) {
    ETTreeNode *x = pNode->right,
            *y = pNode->left,
            *z = y->right,
            *w = y->left;
    z->parent = pNode;
    y->parent = pNode->parent;
    y->right = pNode;
    if (pNode->parent != nullptr)
        if (pNode == pNode->parent->left)
            pNode->parent->left = y;
        else
            pNode->parent->right = y;
    pNode->parent = y;
    pNode->left = z;
    updateRank(pNode);
}

void ETForest::updateRank(ETTreeNode *pNode) {
    pNode->rank = pNode->color == BLACK ? pNode->left->rank : pNode->left->rank + 1;
    updateRank(pNode->parent);
}

void ETForest::repair(ETTreeNode *pNode) {
    if (pNode->color == BLACK) return;         // done
    if (pNode->parent == nullptr) {
        pNode->color = BLACK;
        return;
    }         // done
    if (pNode->parent->color == BLACK) return; // done
// tehát pNode és apja is piros, fix needed. apja nem lehet a gyökér, mert az fekete
    if (uncle(pNode)->color == RED) {
// piros a csúcs apja és nagybátyja is -> nagyapjuk nem -> ezek hárman cseréljenek színt
        pNode->parent->color = uncle(pNode)->color = BLACK;
        pNode->parent->parent->color = RED;
        repair(pNode->parent->parent);      //lehet a nagyapa elromlott
    }
// ha cikkcakk, forgatunk, hogy cikkcikk legyen, ha meg cakkcikk, akkor hogy cakkcakk legyen
    if (zigzag(pNode)) {
        rotateLeft(pNode->parent);
        pNode = pNode->left;
    } else if (zagzig(pNode)) {
        rotateRight(pNode->parent);
        pNode = pNode->right;
    }
// most vagy cikkcakk, vagy cakkcikk, forgatunk és színezünk és done
    pNode->parent->color = BLACK;
    pNode->parent->parent->color = RED;
    if (zigzig(pNode)) {
        rotateRight(pNode->parent->parent);
    } else {
        rotateLeft(pNode->parent->parent);
    }
}

ETTreeNode *ETForest::uncle(ETTreeNode *pNode) {
    return sibling(pNode->parent);
}

ETTreeNode *ETForest::sibling(ETTreeNode *pNode) {
    if (isLeft(pNode)) return pNode->parent->right;
    return pNode->parent->left;
}

bool ETForest::isLeft(ETTreeNode *pNode) {
    return (pNode->parent->left == pNode);  //lehet pár helyen elfér egy-egy null check btw
}

bool ETForest::zigzig(ETTreeNode *pNode) { return pNode->parent->parent->left->left == pNode; }

bool ETForest::zigzag(ETTreeNode *pNode) { return pNode->parent->parent->left->right == pNode; }

bool ETForest::zagzig(ETTreeNode *pNode) { return pNode->parent->parent->right->left == pNode; }

bool ETForest::zagzag(ETTreeNode *pNode) { return pNode->parent->parent->right->right == pNode; }
