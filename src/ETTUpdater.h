//
// Created by Alex on 2018. 09. 15..
//

#ifndef SZAKDOLGOZAT_ETTUPDATER_H
#define SZAKDOLGOZAT_ETTUPDATER_H

#include "ETT.h"

void rotateLeft(ETTreeNode *);

void rotateRight(ETTreeNode *);

void updateRank(ETTreeNode *);

void repair(ETTreeNode *);

void rotateLeftWoRankUpdate(ETTreeNode *);

void rotateRightWoRankUpdate(ETTreeNode *);

#endif //SZAKDOLGOZAT_ETTUPDATER_H
