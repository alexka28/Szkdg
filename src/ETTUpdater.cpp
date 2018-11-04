//
// Created by Alex on 2018. 09. 15..
//

#include "ETTUpdater.h"
#include "ETTSetter.h"
#include "ETTQueries.h"

void rotateLeft(ETTreeNode *pNode) {
    ETTreeNode *x = pNode->left,
            *y = pNode->right,
            *z = y->left,
            *w = y->right;
    setParent(z, pNode);
    setParent(y, pNode->parent);
    setLeftChild(y, pNode);

    if (pNode->parent != nullptr) {
        if (pNode == pNode->parent->left) {
            setLeftChild(pNode->parent, y);
        } else {
            setRightChild(pNode->parent, y);
        }
    }

    setParent(pNode, y);
    setRightChild(pNode, z);
    updateRank(pNode);
}

//TODO: nullNode check
void rotateRight(ETTreeNode *pNode) {
    ETTreeNode *x = pNode->right,
            *y = pNode->left,
            *z = y->right,
            *w = y->left;
    setParent(z, pNode);
    setParent(y, pNode->parent);
    setRightChild(y, pNode);

    if (pNode->parent != nullptr) {
        if (pNode == pNode->parent->left) {
            setLeftChild(pNode->parent, y);
        } else {
            setRightChild(pNode->parent, y);
        }
    }

    setParent(pNode, y);
    setLeftChild(pNode, z);
    updateRank(pNode);
}

void updateRank(ETTreeNode *pNode) {
    if (pNode != nullptr && pNode != &theNullNode) {
       pNode->rank = pNode->color == RED ? pNode->left->rank : pNode->left->rank + 1;

        updateRank(pNode->parent);
    }

}

void repair(ETTreeNode *pNode) {
    if (pNode->color == BLACK) return;         // done
    if (pNode->parent == nullptr) {
        setColor(pNode, BLACK);
        return;
    }         // done

    if (pNode->parent->color == BLACK) return; // done
// tehát pNode és apja is piros, fix needed. apja nem lehet a gyökér, mert az fekete
    if (uncle(pNode) != nullptr && uncle(pNode)->color == RED) {
// piros a csúcs apja és nagybátyja is -> nagyapjuk nem -> ezek hárman cseréljenek színt
        pNode->parent->color = uncle(pNode)->color = BLACK;
        pNode->parent->parent->color = RED;
        //állítsuk be apa, nagybácsi, nagyapa rangját
        setRank(pNode->parent, pNode->parent->rank + 1);
        setRank(uncle(pNode), uncle(pNode)->rank + 1);
        //mivel nagyapa piros, ezért az ő rankja biztosan a bal gyerekének a rankja lesz
        setRank(pNode->parent->parent, pNode->parent->parent->left->rank);
        repair(pNode->parent->parent);      //lehet a nagyapa elromlott
        return;
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
    if (pNode->parent->parent != nullptr) {
        setColor(pNode->parent->parent, RED);
//        pNode->parent->parent->color = RED;
    }

    if (zigzig(pNode)) {
        rotateRight(pNode->parent->parent);
    } else {
        if (pNode->parent->parent != nullptr) {
            rotateLeft(pNode->parent->parent);
        }
    }

}