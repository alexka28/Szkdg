//
// Created by Alex on 2018. 09. 15..
//

#include "ETTSetter.h"
#include "ETTUpdater.h"

void setColorWithRankUpdate(ETTreeNode *pNode, int color) {
    if (pNode != &theNullNode && pNode != nullptr) {
        pNode->color = color;
        updateRank(pNode);
    }
}

void setParent(ETTreeNode *set, ETTreeNode *toSet) {
    if (set != &theNullNode && set != nullptr && toSet != &theNullNode) {
        set->parent = toSet;
    }
}

void setRightChild(ETTreeNode *set, ETTreeNode *toSet) {
    if (set != &theNullNode && set != nullptr && toSet != nullptr) {
        set->right = toSet;
    }
}

void setLeftChild(ETTreeNode *set, ETTreeNode *toSet) {
    if (set != &theNullNode && set != nullptr && toSet != nullptr) {
        set->left = toSet;
    }
}

void setRank(ETTreeNode *set, int r) {
    if (set != &theNullNode && set != nullptr) {
        set->rank = r;
    }
}

ETTreeNode *setBackToOneNode(ETTreeNode *pNode) {
    pNode->parent = nullptr;
    pNode->right = &theNullNode;
    pNode->left = &theNullNode;
    return pNode;
}

void setColor(ETTreeNode *pNode, int color) {
    if (pNode != &theNullNode && pNode != nullptr) {
        pNode->color = color;
    }
}