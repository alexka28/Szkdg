//
// Created by Alex on 2018. 09. 15..
//

#ifndef SZAKDOLGOZAT_ETTQUERIES_H
#define SZAKDOLGOZAT_ETTQUERIES_H

#include "ETT.h"



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


#endif //SZAKDOLGOZAT_ETTQUERIES_H
