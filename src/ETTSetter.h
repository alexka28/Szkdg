//
// Created by Alex on 2018. 09. 15..
//

#ifndef SZAKDOLGOZAT_ETTSETTER_H
#define SZAKDOLGOZAT_ETTSETTER_H

#include "ETT.h"

void setColorWithRankUpdate(ETTreeNode *, int);

void setParent(ETTreeNode *, ETTreeNode *);

void setLeftChild(ETTreeNode *, ETTreeNode *);

void setRightChild(ETTreeNode *, ETTreeNode *);

void setRank(ETTreeNode *, int);

ETTreeNode *setBackToOneNode(ETTreeNode *);

void setColor(ETTreeNode *, int);

#endif //SZAKDOLGOZAT_ETTSETTER_H
