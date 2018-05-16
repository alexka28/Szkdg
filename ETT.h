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
    int N;
    int logN;

    ETForest(int n);

    ETTreeNode *findRoot(int);

    ETTreeNode *findRoot(ETTreeNode *);

    void inOrder(ETTreeNode *);

    bool contains(int, int);

    ETTreeNode *predecessor(ETTreeNode *);

    ETTreeNode *successor(ETTreeNode *);

    ETTreeNode *maximum(ETTreeNode *);

    ETTreeNode *minimum(ETTreeNode *);

    void join(int, int);

    void insert(int, int);

    void remove(int, int);

    ETTreeNode *join(ETTreeNode *, ETTreeNode *, ETTreeNode *);

    std::pair<ETTreeNode *, ETTreeNode *> split(ETTreeNode *);

    void reroot(int);

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

    //deletehez
    ETTreeNode *deleteNode(ETTreeNode *);

    void setColor(ETTreeNode *, int);

    bool oneNode(ETTreeNode *);

    ETTreeNode *setBackToOneNode(ETTreeNode *);

    ETTreeNode *newDelete(ETTreeNode *);

    void deleteCase1(ETTreeNode *);

    void deleteCase2(ETTreeNode *);

    void deleteCase3(ETTreeNode *);

    void deleteCase4(ETTreeNode *);

    void deleteCase5(ETTreeNode *);

    void deleteCase6(ETTreeNode *);

    void replaceNode(ETTreeNode *, ETTreeNode *);
    void setParent(ETTreeNode*,ETTreeNode*);
    void setLeftChild(ETTreeNode*, ETTreeNode*);
    void setRightChild(ETTreeNode*, ETTreeNode*);
    void setRank(ETTreeNode*,int);

} ETForest;
#endif //UNTITLED1_ETT_H
