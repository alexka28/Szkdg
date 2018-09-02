#ifndef UNTITLED1_ETT_H_INCLUDED

#define UNTITLED1_ETT_H_INCLUDED

#include <utility>

static constexpr int BLACK = 0, RED = 1, DOUBLE_BLACK = 2;


typedef struct ETTreeNode {
    ETTreeNode *parent;                 // ős a fában, ha nullptr, akkor ez egy gyökér
    ETTreeNode *left, *right;           // gyerekek a fában
    int color;                          // BLACK vagy RED 0 =Black, 1=red
    int nodeId;                         // a csúcs
    int rank;                           // a fekete csúcsok száma gyökér-levél úton
    ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color);

    ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color, int nodeId);
} ETTreeNode;


//global változó, értékadás az ETT.cpp-ben
extern ETTreeNode theNullNode;


typedef struct ETForest {
    ETTreeNode **first;
    ETTreeNode **last;
    int N;
    int logN;

    ETForest(int n);

    ETTreeNode *findRoot(int);

   static ETTreeNode *findRoot(ETTreeNode *);

  static  void inOrder(ETTreeNode *);

    bool contains(int, int);

    static ETTreeNode *predecessor(ETTreeNode *);

    static ETTreeNode *successor(ETTreeNode *);

    static ETTreeNode *maximum(ETTreeNode *);

    static ETTreeNode *minimum(ETTreeNode *);

    void join(int, int);

    void insert(int, int);

    void remove(int, int);

    ETTreeNode *join(ETTreeNode *, ETTreeNode *, ETTreeNode *);

    std::pair<ETTreeNode *, ETTreeNode *> split(ETTreeNode *);

    void reroot(int);

    static void rotateLeft(ETTreeNode *);

    static void rotateRight(ETTreeNode *);

    static void updateRank(ETTreeNode *);

    static void repair(ETTreeNode *);

    static ETTreeNode *uncle(ETTreeNode *);

    static ETTreeNode *sibling(ETTreeNode *);


    static bool isLeft(ETTreeNode *);

    static bool zigzig(ETTreeNode *);

    static bool zigzag(ETTreeNode *);

    static bool zagzig(ETTreeNode *);

    static bool zagzag(ETTreeNode *);

    //deletehez
    ETTreeNode *deleteNode(ETTreeNode *);

    static void setColor(ETTreeNode *, int);

    static bool oneNode(ETTreeNode *);

    static ETTreeNode *setBackToOneNode(ETTreeNode *);

    static ETTreeNode *newDelete(ETTreeNode *);

    static void deleteCase1(ETTreeNode *);

    static void deleteCase2(ETTreeNode *);

    static void deleteCase3(ETTreeNode *);

    static void deleteCase4(ETTreeNode *);

    static void deleteCase5(ETTreeNode *);

    static void deleteCase6(ETTreeNode *);

    static void replaceNode(ETTreeNode *, ETTreeNode *);

    static void setParent(ETTreeNode *, ETTreeNode *);

    static void setLeftChild(ETTreeNode *, ETTreeNode *);

    static void setRightChild(ETTreeNode *, ETTreeNode *);

    static void setRank(ETTreeNode *, int);

    //további cuccok
    ETTreeNode *firstSeen(int, int);

} ETForest;
#endif //UNTITLED1_ETT_H
