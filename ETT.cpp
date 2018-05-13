#include <iostream>
#include "ETT.h"
#include <utility>

const int BLACK = 0, RED = 1, DOUBLE_BLACK = 2;

ETTreeNode::ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color) {
    this->parent = parent;
    this->left = left;
    this->right = right;
    this->color = color;
    this->rank = 0;
}

ETTreeNode::ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color, int nodeId) {
    this->parent = parent;
    this->left = left;
    this->right = right;
    this->color = color;
    this->nodeId = nodeId;
    this->rank = 1;

}

//egy üres node
ETTreeNode theNullNode(nullptr, nullptr, nullptr, BLACK);

ETForest::ETForest(int n) {
    first = new ETTreeNode *[n];
    last = new ETTreeNode *[n];


    ETTreeNode *n1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 5); //node 5
    ETTreeNode *n2 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 2); //node 2
    ETTreeNode *n3 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 8); //node 8
    ETTreeNode *n4 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 1); //node 1
    ETTreeNode *n5 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 3); //node 3
    ETTreeNode *n6 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 6); //node 6
    ETTreeNode *n7 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 16); //node 16
    ETTreeNode *n8 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 7); //node 7
    n1->left = n2;
    n1->right = n3;
    n1->rank = 2;
    n2->parent = n1;
    n2->left = n4;
    n2->right = n5;
    n2->rank = 2;
    n3->parent = n1;
    n3->left = n6;
    n3->right = n7;
    n3->rank = 2;
    n4->parent = n2;
    n4->rank = 1;
    n5->parent = n2;
    n5->rank = 1;
    n6->parent = n3;
    n6->right = n8;
    n6->rank = 1;
    n7->parent = n3;
    n7->rank = 1;
    n8->parent = n6;
    n8->rank = 1;

    for (int i = 0; i < n; ++i) {
        ETTreeNode *node = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, i);

        first[i] = node;
        last[i] = node;
    }
    /* first[0] = n1;
     last[0] = n1;
     first[1] = n2;
     last[1] = n2;
     first[2] = n3;
     last[2] = n3;
     first[3] = n4;
     last[3] = n4;
     first[4] = n5;
     last[4] = n5;
     first[5] = n6;
     last[5] = n6;
     first[6] = n7;
     last[6] = n7; */
    inOrder(n1);
    std::cout << "T1: " << std::endl;
    std::pair<ETTreeNode *, ETTreeNode *> spl = split(n6);
    inOrder(findRoot(spl.first));
    std::cout << "T2: " << std::endl;
    inOrder(findRoot(spl.second));


}

void ETForest::inOrder(ETTreeNode *pNode) {
    if (pNode != nullptr && pNode != &theNullNode && pNode->left != &theNullNode) {
        inOrder(pNode->left);
    }
    if (pNode != nullptr) { std::cout << pNode->nodeId << std::endl; }

    if (pNode != nullptr && pNode != &theNullNode && pNode->right != &theNullNode) {
        inOrder(pNode->right);
    }
}

ETTreeNode *ETForest::findRoot(int u) {
    ETTreeNode *pNode = this->first[u];
    while (pNode->parent != nullptr) {

        pNode = pNode->parent;

    }

    return pNode;
}

ETTreeNode *ETForest::findRoot(ETTreeNode *u) {
    ETTreeNode *pNode = u;
    while (pNode->parent != nullptr) {

        pNode = pNode->parent;

    }

    return pNode;
}

bool ETForest::contains(int u, int v) {
//TODO: uncommentelni ha kesz
    /* return  F.predecessor( F.first[u] ) -> nodeId == v  // ha létezik; null-check is kell
             ||F.predecessor( F.first[v] ) -> nodeId == u*/
}

ETTreeNode *ETForest::predecessor(ETTreeNode *pNode) {
    if (pNode->left != &theNullNode) {
        return maximum(pNode->left);
    }
    while (pNode->parent != nullptr && pNode->parent->left == pNode) {
        pNode = pNode->parent;
    }
    return pNode->parent;
}

ETTreeNode *ETForest::successor(ETTreeNode *pNode) {
    if (pNode->right != &theNullNode) {
        return minimum(pNode->right);
    }
    while (pNode->parent != nullptr && pNode->parent->right == pNode) {
        pNode = pNode->parent;
    }
    return pNode->parent;
}

ETTreeNode *ETForest::maximum(ETTreeNode *pNode) {
    while (pNode->right != &theNullNode) {
        pNode = pNode->right;
    }
    return pNode;
}

ETTreeNode *ETForest::minimum(ETTreeNode *pNode) {
    while (pNode->left != &theNullNode) {
        pNode = pNode->left;
    }
    return pNode;
}

//TODO: fix join
void ETForest::join(int u, int v) {
    ETTreeNode *root1 = findRoot(u);
    ETTreeNode *root2 = findRoot(v);
    int bh1 = root1->rank;
    int bh2 = root2->rank;

    if (bh1 >= bh2) {
        //keressük meg root1 maxját
        while (root1->right != &theNullNode) {
            root1 = root1->right;
        }
        //ha megvan ragasszuk hozzá a root2-t
        root1->right = root2;

        root2->parent = root1;
        root2->color = RED;
        repair(root2);


    } else {
        while (root2->right != nullptr) {
            root2 = root2->right;
        }
        root2->right = root1;
        root1->parent = root2;
        root1->color = RED;
        repair(root1);
//updateRank(root1);

    }


}

ETTreeNode *ETForest::join(ETTreeNode *x, ETTreeNode *u, ETTreeNode *y) {


    if (x->rank == y->rank) {
        u->left = x;
        u->right = y;
        if(x != &theNullNode){
            x->parent = u;
        }
        if(y != &theNullNode){
            y->parent = u;
        }
        u->color = BLACK;
        updateRank(u);
    } else if (x->rank < y->rank) {

        ETTreeNode *N = y;
        if (x == &theNullNode) {
            while (y->left != &theNullNode) {
                y = y->left;
            }
            u->rank = 1;
            y->left = u;
            y->right = x;
            u->parent = y;

            u->color = RED;
            repair(u);
            //updateRank(u);

        } else {
            while (y->rank != x->rank) {
                y = y->left;
            }
            N = y;
            if (y->color != BLACK) {
                N = y->left;

            }
            u->parent = N->parent;
            if (N != &theNullNode) {
                N->parent->left = u;
                N->parent = u;
            }


            u->right = N;
            u->left = x;

            x->parent = u;
            u->color = RED;
            repair(u);


        }
    } //x > y
    else {
        ETTreeNode *N;
        if (y == &theNullNode) {
            while (x->right != &theNullNode) {

                x = x->right;
            }
           u->rank = 1;
            x->right = u;
            u->parent = x;
            x->left = y;
            u->color = RED;
            repair(u);
            //updateRank(u);



        } else {
            while (x->rank != y->rank) {
                x = x->right;
            }
            N = x;
            if (x->color != BLACK) {
                N = x->right;
            }
            u->parent = N->parent;
            if (N != &theNullNode) {
                N->parent->right = u;
                N->parent = u;
            }

            u->right = y;
            u->left = N;

            y->parent = u;
            u->color = RED;
            repair(u);

        }


    }
    return findRoot(u);
}

std::pair<ETTreeNode *, ETTreeNode *> ETForest::split(ETTreeNode *pNode) {
    //saveljük el a parentjét és, hogy jobb vagy bal gyerek-e
    ETTreeNode *parent = pNode->parent;
    ETTreeNode *T1;
    bool isLeftNode = isLeft(pNode);
    //T1 létrehozása, ő a pNode bal gyereke
    if (pNode->left == &theNullNode) {
        T1 = &theNullNode;
    } else {
        T1 = new ETTreeNode(nullptr, pNode->left->left, pNode->left->right, pNode->left->color,
                            pNode->left->nodeId);
        T1->rank = pNode->left->rank;
    }

//mentsük el a jobb részfát
    ETTreeNode *pNodeRight = pNode->right;
    //valszleg a szülőjét nem árt nullptr-re rakni
    pNodeRight->parent = nullptr;
    //pNode visszaállítása 1 elemű fára
    pNode->right = &theNullNode;
    pNode->left = &theNullNode;
    pNode->parent = nullptr;
    // T2 létrehozása, pNode már gyerekek nélkül és a jobb részfa
    //itt a pNodeRight miatt lehet, hogy a rootja a teljes fa rootja, ha nincs nullptr-re rakva
    ETTreeNode *T2 = join(&theNullNode, pNode, pNodeRight);

    while (parent != nullptr) {
        if (isLeftNode) {
            ETTreeNode *subTree = parent->right;
            ETTreeNode *root = parent;
            isLeftNode = isLeft(parent);
            parent = parent->parent;

            root->left = &theNullNode;
            root->right = &theNullNode;
            T2->parent = nullptr;
            root->parent = nullptr;
            subTree->parent = nullptr;
            T2 = join(T2, root, subTree);


        } else {
            ETTreeNode *subTree = parent->left;
            ETTreeNode *root = parent;
            isLeftNode = isLeft(parent);
            parent = parent->parent;

            root->left = &theNullNode;
            root->right = &theNullNode;

            T1->parent = nullptr;
            root->parent = nullptr;
            subTree->parent = nullptr;

            T1 = join(subTree, root, T1);

        }
    }
    if (T1->color == RED) {
        T1->color = BLACK;
        updateRank(T1);
    }
    if (T2->color == RED) {
        T2->color = BLACK;
      updateRank(T2);
    }
    std::pair<ETTreeNode *, ETTreeNode *> T1T2(T1, T2);
    return T1T2;

}

void ETForest::rotateLeft(ETTreeNode *pNode) {
    ETTreeNode *x = pNode->left,
            *y = pNode->right,
            *z = y->left,
            *w = y->right;
    z->parent = pNode;
    y->parent = pNode->parent;
    y->left = pNode;
    if (pNode->parent != nullptr)
        if (pNode == pNode->parent->left)
            pNode->parent->left = y;
        else
            pNode->parent->right = y;
    pNode->parent = y;
    pNode->right = z;
    updateRank(pNode);
}

//TODO: nullNode check
void ETForest::rotateRight(ETTreeNode *pNode) {
    ETTreeNode *x = pNode->right,
            *y = pNode->left,
            *z = y->right,
            *w = y->left;
    z->parent = pNode;
    y->parent = pNode->parent;
    y->right = pNode;
    if (pNode->parent != nullptr)
        if (pNode == pNode->parent->left)
            pNode->parent->left = y;
        else
            pNode->parent->right = y;
    pNode->parent = y;
    pNode->left = z;
    updateRank(pNode);
}

void ETForest::updateRank(ETTreeNode *pNode) {
    if (pNode != nullptr ) {
        pNode->rank = pNode->color == RED ? pNode->left->rank : pNode->left->rank + 1;
        updateRank(pNode->parent);
    }

}

void ETForest::repair(ETTreeNode *pNode) {
    if (pNode->color == BLACK) return;         // done
    if (pNode->parent == nullptr) {
        pNode->color = BLACK;
        return;
    }         // done

    if (pNode->parent->color == BLACK) return; // done
// tehát pNode és apja is piros, fix needed. apja nem lehet a gyökér, mert az fekete
    if (uncle(pNode) != nullptr && uncle(pNode)->color == RED) {
// piros a csúcs apja és nagybátyja is -> nagyapjuk nem -> ezek hárman cseréljenek színt
        pNode->parent->color = uncle(pNode)->color = BLACK;
        pNode->parent->parent->color = RED;
        repair(pNode->parent->parent);      //lehet a nagyapa elromlott
    } else {
        pNode->parent->color = BLACK;
       // pNode->parent->rank = pNode->parent->rank + 1;
    }
// ha cikkcakk, forgatunk, hogy cikkcikk legyen, ha meg cakkcikk, akkor hogy cakkcakk legyen
    if (zigzag(pNode)) {
        rotateLeft(pNode->parent);
        pNode = pNode->left;
    } else if (zagzig(pNode)) {
        rotateRight(pNode->parent);
        pNode = pNode->right;
    }
// most vagy cikkcakk, vagy cakkcikk, forgatunk és színezünk és done
    pNode->parent->color = BLACK;
    if (pNode->parent->parent != nullptr) {
        pNode->parent->parent->color = RED;
    }

    if (zigzig(pNode)) {
        rotateRight(pNode->parent->parent);
    } else {
        if(pNode->parent->parent != nullptr){
            rotateLeft(pNode->parent->parent);
        }
        }

}

ETTreeNode *ETForest::uncle(ETTreeNode *pNode) {
    return sibling(pNode->parent);
}

ETTreeNode *ETForest::sibling(ETTreeNode *pNode) {
    if (pNode->parent != nullptr) {
        if (isLeft(pNode))return pNode->parent->right;
        return pNode->parent->left;
    } else {
        return nullptr;
    }

}

bool ETForest::isLeft(ETTreeNode *pNode) {
    if (pNode->parent != nullptr) {
        return (pNode->parent->left == pNode);
    } else {
        return false;
    }
    //lehet pár helyen elfér egy-egy null check btw
}

bool ETForest::zigzig(ETTreeNode *pNode) {
    if (pNode->parent->parent != nullptr) {
        return pNode->parent->parent->left->left == pNode;
    } else { return false; }
}

bool ETForest::zigzag(ETTreeNode *pNode) {
    if (pNode->parent->parent != nullptr) {
        return pNode->parent->parent->left->right == pNode;
    } else {
        return false;
    }
}

bool ETForest::zagzig(ETTreeNode *pNode) {
    if (pNode->parent->parent != nullptr) {
        return pNode->parent->parent->right->left == pNode;
    } else {
        return false;
    }
}

bool ETForest::zagzag(ETTreeNode *pNode) { return pNode->parent->parent->right->right == pNode; }

void ETForest::setColor(ETTreeNode *pNode, int color) {
    if (pNode == &theNullNode) {
        return;
    }
    pNode->color = color;
}

void ETForest::deleteNode(ETTreeNode *node) {
    if (node == &theNullNode)
        return;

    if (node == findRoot(node->nodeId)) {
        //root = nullptr;
        return;
    }

    if (node->color == RED || node->left->color == RED || node->right->color == RED) {
        ETTreeNode *child = node->left != &theNullNode ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            //delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            //delete (node);
        }
    } else {
        ETTreeNode *sibling = nullptr;
        ETTreeNode *parent = nullptr;
        ETTreeNode *ptr = node;
        ETTreeNode *root = findRoot(node->nodeId);
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != findRoot(ptr->nodeId) && ptr->color == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (sibling->color == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                        setColor(sibling, RED);
                        if (parent->color == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (sibling->right->color == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (sibling->color == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                        setColor(sibling, RED);
                        if (parent->color == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (sibling->left->color == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        //delete (node);
        setColor(root, BLACK);
    }
}