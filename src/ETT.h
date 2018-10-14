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

    bool contains(int, int);

    void join(int, int);

    void insert(int, int);

    void remove(int, int);

    ETTreeNode *join(ETTreeNode *, ETTreeNode *, ETTreeNode *);

    std::pair<ETTreeNode *, ETTreeNode *> split(ETTreeNode *);

    void reroot(int);

    //TODO: dob
    ETTreeNode *deleteNode(ETTreeNode *);

    //deletehez
    static ETTreeNode *newDelete(ETTreeNode *);

    static void deleteCase1(ETTreeNode *);

    static void deleteCase2(ETTreeNode *);

    static void deleteCase3(ETTreeNode *);

    static void deleteCase4(ETTreeNode *);

    static void deleteCase5(ETTreeNode *);

    static void deleteCase6(ETTreeNode *);

    static void replaceNode(ETTreeNode *, ETTreeNode *);

    static void verifyProperties(ETTreeNode*);

    static void verifyColor(ETTreeNode* pNode);
    static void verifyRootColor(ETTreeNode* pNode);
    static void verifyRedNodeParentAndChildrenColors(ETTreeNode* pNode);
    static void verifyProperty_4(ETTreeNode* pNode);
    static void verifyBlackRank(ETTreeNode* pNode);
    static void verifyBlackRankHelper(ETTreeNode* pNode,int black_count, int* path_black_count);
    static void verifyRankNumber (ETTreeNode* pNode);
    static void verifyRankNumberHelper(ETTreeNode* pNode);
    void        verifyFirstLast();
    void        firstLastHelper(ETTreeNode* pNode, const int& id,ETTreeNode*& firstSeen, ETTreeNode*& lastSeen);
    static void updateAllRank(ETTreeNode* pNode);
    static void updateHelper(ETTreeNode* pNode);
    //további cuccok
    ETTreeNode *firstSeen(int, int);

} ETForest;
#endif //UNTITLED1_ETT_H
