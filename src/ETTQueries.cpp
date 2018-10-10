//
// Created by Alex on 2018. 09. 15..
//

#include "ETTQueries.h"
#include <iostream>

ETTreeNode *predecessor(ETTreeNode *pNode) {
    if (pNode->left != &theNullNode) {
        return maximum(pNode->left);
    }
    while (pNode->parent != nullptr && pNode->parent->left == pNode) {
        pNode = pNode->parent;
    }
    return pNode->parent;
}

ETTreeNode *successor(ETTreeNode *pNode) {
    if (pNode->right != &theNullNode) {
        return minimum(pNode->right);
    }
    while (pNode->parent != nullptr && pNode->parent->right == pNode) {
        pNode = pNode->parent;
    }
    return pNode->parent;
}

ETTreeNode *maximum(ETTreeNode *pNode) {
    while (pNode->right != &theNullNode) {
        pNode = pNode->right;
    }
    return pNode;
}

ETTreeNode *minimum(ETTreeNode *pNode) {
    while (pNode->left != &theNullNode) {
        pNode = pNode->left;
    }
    return pNode;
}


ETTreeNode *uncle(ETTreeNode *pNode) {
    return sibling(pNode->parent);
}

ETTreeNode *sibling(ETTreeNode *pNode) {
    if (pNode->parent != nullptr) {
        if (isLeft(pNode))return pNode->parent->right;
        return pNode->parent->left;
    } else {
        return nullptr;
    }

}

bool isLeft(ETTreeNode *pNode) {
    if (pNode->parent != nullptr) {
        return (pNode->parent->left == pNode);
    } else {
        return false;
    }
    //lehet pár helyen elfér egy-egy null check btw
}

bool zigzig(ETTreeNode *pNode) {
    if (pNode->parent->parent != nullptr) {
        return pNode->parent->parent->left->left == pNode;
    } else { return false; }
}

bool zigzag(ETTreeNode *pNode) {
    if (pNode->parent->parent != nullptr) {
        return pNode->parent->parent->left->right == pNode;
    } else {
        return false;
    }
}

bool zagzig(ETTreeNode *pNode) {
    if (pNode->parent->parent != nullptr) {
        return pNode->parent->parent->right->left == pNode;
    } else {
        return false;
    }
}

bool zagzag(ETTreeNode *pNode) {
    return pNode->parent->parent->right->right == pNode;
}

bool isOneNode(ETTreeNode *pNode) {
    if (pNode->parent == nullptr && pNode->right == &theNullNode && pNode->left == &theNullNode) {
        return true;
    }
    return false;
}


void inOrder(ETTreeNode *pNode) {
    if (pNode != nullptr && pNode != &theNullNode && pNode->left != &theNullNode) {
        inOrder(pNode->left);
    }
    if (pNode != nullptr) { std::cout << pNode->nodeId << "-"; }

    if (pNode != nullptr && pNode != &theNullNode && pNode->right != &theNullNode) {
        inOrder(pNode->right);
    }
}

ETTreeNode* ETTMinimum(ETTreeNode* pNode){
    pNode = ETForest::findRoot(pNode);
    pNode = minimum(pNode);
    return pNode;
}


ETTreeNode* ETForest::findRoot(ETTreeNode *u) {
    ETTreeNode *pNode = u;
    while (pNode->parent != nullptr) {
        pNode = pNode->parent;
    }
    return pNode;
}