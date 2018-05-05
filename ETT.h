#ifndef UNTITLED1_ETT_H
#define UNTITLED1_ETT_H
typedef struct ETTreeNode {
    ETTreeNode *parent;              // ős a fában, ha nullptr, akkor ez egy gyökér
    ETTreeNode *left, *right;        // gyerekek a fában
    int color;                // BLACK vagy RED 0 =Black, 1=red
    int nodeId;               // a csúcs
    int rank;                 // a fekete csúcsok száma gyökér-levél úton
    ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color);

    ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color, int nodeId);
} ETTreeNode;


typedef struct ETForest {
    ETTreeNode **first;
    ETTreeNode **last;

    ETForest(int n);

    ETTreeNode *findRoot(int);

    bool contains(int, int);

    void join(int, int);

    void rotateLeft(ETTreeNode *);

    void rotateRight(ETTreeNode *);

    void updateRank(ETTreeNode *);

    void repair(ETTreeNode *);

    ETTreeNode *uncle(ETTreeNode *);

    ETTreeNode *sibling(ETTreeNode *);

    bool isLeft(ETTreeNode *);

    bool zigzig(ETTreeNode *);

    bool zigzag(ETTreeNode *);

    bool zagzig(ETTreeNode *);

    bool zagzag(ETTreeNode *);

} ETForest;
#endif //UNTITLED1_ETT_H
