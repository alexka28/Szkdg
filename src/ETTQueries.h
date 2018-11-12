//
// Created by Alex on 2018. 09. 15..
//

#ifndef SZAKDOLGOZAT_ETTQUERIES_H
#define SZAKDOLGOZAT_ETTQUERIES_H

#include "ETT.h"
#include <list>


ETTreeNode *predecessor(ETTreeNode *);

ETTreeNode *successor(ETTreeNode *);

ETTreeNode *maximum(ETTreeNode *);

ETTreeNode *minimum(ETTreeNode *);

ETTreeNode *uncle(ETTreeNode *);

ETTreeNode *sibling(ETTreeNode *);

ETTreeNode *ETTMinimum(ETTreeNode *);
bool isLeft(ETTreeNode *);

bool zigzig(ETTreeNode *);

bool zigzag(ETTreeNode *);

bool zagzig(ETTreeNode *);

bool zagzag(ETTreeNode *);

bool isOneNode(ETTreeNode *);


void inOrder(ETTreeNode *);

void inOrder(ETTreeNode* pNode, std::list<int>& treeInOrder);

bool isSameInOrder(const std::list<int>& expectedInOrder, const std::list<int>& treeInOrder);
#endif //SZAKDOLGOZAT_ETTQUERIES_H
