#include "ETT.h"

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
        ETTreeNode *node = new ETTreeNode(nullptr, &theNullNode, &theNullNode, 0, i);
        first[i] = node;
        last[i] = node;
    }

}
