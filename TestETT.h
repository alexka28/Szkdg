//
// Created by Alex on 2018. 07. 28..
//

#ifndef UNTITLED1_TESTETT_H
#define UNTITLED1_TESTETT_H

#include "ETT.h"
#include <list>
#include <map>
namespace TestETT{
    typedef struct Node{
        int nodeId;
        int color;
        int rank;
    }Node;
    int compare(const ETTreeNode*, const ETTreeNode*);
    void inOrderSampleTree(const ETTreeNode*, std::list<Node>&);
    void inOrderNormalTree(const ETTreeNode*, std::list<Node>&, std::map<const ETTreeNode*, int>&, int&);
    bool isNullNode(const ETTreeNode*);
    const ETTreeNode* findRootForTest(const ETTreeNode*);


}


#endif //UNTITLED1_TESTETT_H
