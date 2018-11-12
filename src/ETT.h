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
    ETTreeNode(int color, int nodeId, int rank, ETTreeNode * parent = nullptr); //unit tesztekhez

} ETTreeNode;


//global változó, értékadás az ETT.cpp-ben
extern ETTreeNode theNullNode;
extern bool bid;
extern bool isFirstTime;

typedef struct ETForest {
    ETTreeNode **first;
    ETTreeNode **last;
    int N;
    int logN;

    ETForest(int n);

    ETTreeNode *findRoot(int);

    static ETTreeNode *findRoot(ETTreeNode *);

    bool contains(int, int);

    void insert(int, int);

    void remove(int, int);

    ETTreeNode *join(ETTreeNode *, ETTreeNode *, ETTreeNode *);

    std::pair<ETTreeNode *, ETTreeNode *> split(ETTreeNode *);

    void reroot(int);

    //deletehez
    static void newDelete(ETTreeNode *);

    static void deleteCase1(ETTreeNode *);

    static void deleteCase2(ETTreeNode *);

    static void deleteCase3(ETTreeNode *);

    static void deleteCase4(ETTreeNode *);

    static void deleteCase5(ETTreeNode *);

    static void deleteCase6(ETTreeNode *);

    static void replaceNode(ETTreeNode *, ETTreeNode *);

    static bool verifyProperties(ETTreeNode*);

    static void verifyColor(ETTreeNode* pNode, bool& isValid);
    static void verifyRootColor(ETTreeNode* root, bool& isValid);
    static void verifyRedNodeParentAndChildrenColors(ETTreeNode* pNode, bool& isValid);
    static void verifyBlackRank(ETTreeNode* pNode, bool& isValid);
    static void verifyBlackRankHelper(ETTreeNode* pNode,int black_count, int* path_black_count, bool& isValid);
    static void verifyRankNumber (ETTreeNode* pNode, bool& isValid);
    static void verifyRankNumberHelper(ETTreeNode* pNode, bool& isValid);
    void        verifyFirstLast();
    void        firstLastHelper(ETTreeNode* pNode, const int& id,ETTreeNode*& firstSeen, ETTreeNode*& lastSeen);
    void        verifyNodesAreTwoSideConnected(ETTreeNode* pNode);
    void        verify2SideConnection();
//    static void updateAllRank(ETTreeNode* pNode);
//    static void updateHelper(ETTreeNode* pNode);
    static void print(ETTreeNode* pNode);
    static void print(ETTreeNode* pNode, int indent);

} ETForest;
#endif //UNTITLED1_ETT_H
