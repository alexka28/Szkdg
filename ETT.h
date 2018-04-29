#ifndef UNTITLED1_ETT_H
#define UNTITLED1_ETT_H
typedef struct ETTreeNode
{
    ETTreeNode *parent;              // ős a fában, ha nullptr, akkor ez egy gyökér
    ETTreeNode *left, *right;        // gyerekek a fában
    int      color;                // BLACK vagy RED 0 =Black, 1=red
    int        nodeId;               // a csúcs
    int        rank;                 // a fekete csúcsok száma gyökér-levél úton
    ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color);
    ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color, int nodeId);
} ETTreeNode;


typedef struct ETForest
{
    ETTreeNode* *first;
    ETTreeNode* *last;
    ETForest(int n);
} ETForest;
#endif //UNTITLED1_ETT_H
