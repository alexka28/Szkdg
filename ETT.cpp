#include <iostream>
#include "ETT.h"
#include <utility>
#include <stack>
#include <cassert>

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
    this->N = n;
//TODO: logN-t számolni!
    this->logN = n;

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
    //  deleteNode(n7);
//    newDelete(n5);
//    std::cout << "delete: " << n2->nodeId << std::endl;
//    inOrder(findRoot(n1));
//    std::pair<ETTreeNode *, ETTreeNode *> spl1 = split(n8);
//std::cout<<"masodik split T1:"<<std::endl;
//inOrder(findRoot(spl1.first));
//    std::cout<<"masodik split T2:"<<std::endl;
//inOrder(findRoot(spl1.second));
//
//
//
//    std::pair<ETTreeNode *, ETTreeNode *> spl2 = split(n3);
//    std::cout<<"harmadik split T1:"<<std::endl;
//    inOrder(findRoot(spl2.first));
//    std::cout<<"harmadik split T2:"<<std::endl;
//    inOrder(findRoot(spl2.second));
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
        setLeftChild(u, x);
        setRightChild(u, y);
        setParent(x, u);
        setParent(y, u);
        setColor(u, BLACK);
        updateRank(u);
        //TODO: törölni
        // u->left = x;
//        u->right = y;
//        if (x != &theNullNode) {
//            x->parent = u;
//        }
//        if (y != &theNullNode) {
//            y->parent = u;
//        }

        //u->color = BLACK;

    } else if (x->rank < y->rank) {

        ETTreeNode *N;
        //ha az y még egy elemű fa, akkor elég a bal fiát u-ra állítani
        if (x == &theNullNode && oneNode(y)) {
            setLeftChild(y, u);
            setParent(u, y);
            setColor(u, RED);
            setRank(u, 0);
            repair(u);
        }
            //TODO: fixálni ha nullNodeot teszünk be
        else if (x == &theNullNode && !oneNode(y)) {
            //y->left != &theNullNode
            //y->rank != 1 && y->color != BLACK
            while (y->rank != 1 || y->color != BLACK) {
                y = y->left;
            }
            N = y;
            //ha ba oldalt nullNode van, akkor csak tegyük be az u-t mint egy elemű fánál és done
            if (N->left == &theNullNode) {
                setLeftChild(N, u);
                setParent(u, N);
                setColor(u, RED);
                setRank(u, 0);
                repair(u);
            }
                //TODO: ha van gyerek
            else {
                N = N->left;
                setLeftChild(N, u);
                setParent(u, N);
                setColor(u, RED);
                setRank(u, 0);
                repair(u);
                updateRank(u);

            }


        }
            //ha nem nullNode-ot kell joinolni
        else {
            while (y->rank != x->rank) {
                y = y->left;
            }
            N = y;
            if (y->color != BLACK) {
                N = y->left;

            }
            setParent(u, N->parent);
            setLeftChild(N->parent, u);
            setParent(N, u);
            setRightChild(u, N);
            setLeftChild(u, x);
            setParent(x, u);
            setColor(u, RED);
            repair(u);
//            u->parent = N->parent;
//            if (N != &theNullNode) {
//                N->parent->left = u;
//                N->parent = u;
//            }

//
//            u->right = N;
//            u->left = x;
//
//            x->parent = u;
//            u->color = RED;
//            repair(u);


        }
    } //x > y
    else {
        ETTreeNode *N;
        //ha x még egy elemű fa, akkor elég a jobb fiát u-ra beállítani
        if (y == &theNullNode && oneNode(x)) {
            setRightChild(x, u);
            setParent(u, x);
            setColor(u, RED);
            setRank(u, 0);
            repair(u);
        } else if (y == &theNullNode && !oneNode(x)) {
            //x->right != &theNullNode
            //x->rank != 1 && x->color != BLACK
            //TODO: éselés volt...
            while (x->rank != 1 || x->color != BLACK) {

                x = x->right;
            }

            N = x;
            //ha nullNode a jobb gyerek, akkor csak simán behúzzuk u-t jobbra mint egy elemű fánál és done
            if (N->right == &theNullNode) {
                setRightChild(N, u);
                setParent(u, N);
                setColor(u, RED);
                setRank(u, 0);
                repair(u);
            } else {
                N = N->right;
                setRightChild(N, u);
                setParent(u, N);
                setColor(u, RED);
                setRank(u, 0);
                repair(u);
                updateRank(u);

            }


            /*
            setRightChild(x, u);
            setParent(u, x);
            setColor(u, RED);
            setRank(u, 0);
            repair(u);*/
//            x->right = u;
//            u->parent = x;
            //x->left = y; itt is felülírodna
//            u->color = RED;
//            u->rank = 0;
//            repair(u);
            //updateRank(u);



        } else {
            while (x->rank != y->rank) {
                x = x->right;
            }
            N = x;
            if (x->color != BLACK) {
                N = x->right;
            }
            setParent(u, N->parent);
            setRightChild(N->parent, u);
            setParent(N, u);
            setRightChild(u, y);
            setLeftChild(u, N);
            setParent(y, u);
            setColor(u, RED);
            repair(u);
//            u->parent = N->parent;
//            if (N != &theNullNode) {
//                N->parent->right = u;
//                N->parent = u;
//            }
//
//            u->right = y;
//            u->left = N;
//
//            y->parent = u;
//            u->color = RED;
//            repair(u);

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
    setParent(z, pNode);
    setParent(y, pNode->parent);
    setLeftChild(y, pNode);
//    z->parent = pNode;
//    y->parent = pNode->parent;
//    y->left = pNode;
    if (pNode->parent != nullptr)
        if (pNode == pNode->parent->left)
            setLeftChild(pNode->parent, y);
//            pNode->parent->left = y;
        else
            setRightChild(pNode->parent, y);
//            pNode->parent->right = y;
    setParent(pNode, y);
    setRightChild(pNode, z);
//    pNode->parent = y;
//    pNode->right = z;
    updateRank(pNode);
}

//TODO: nullNode check
void ETForest::rotateRight(ETTreeNode *pNode) {
    ETTreeNode *x = pNode->right,
            *y = pNode->left,
            *z = y->right,
            *w = y->left;
    setParent(z, pNode);
    setParent(y, pNode->parent);
    setRightChild(y, pNode);
//    z->parent = pNode;
//    y->parent = pNode->parent;
//    y->right = pNode;
    if (pNode->parent != nullptr)
        if (pNode == pNode->parent->left)
            setLeftChild(pNode->parent, y);
//            pNode->parent->left = y;
        else
            setRightChild(pNode->parent, y);
//            pNode->parent->right = y;
    setParent(pNode, y);
    setLeftChild(pNode, z);
//    pNode->parent = y;
//    pNode->left = z;
    updateRank(pNode);
}

void ETForest::updateRank(ETTreeNode *pNode) {
    if (pNode != nullptr && pNode != &theNullNode) {
        pNode->rank = pNode->color == RED ? pNode->left->rank : pNode->left->rank + 1;
        updateRank(pNode->parent);
    }

}

void ETForest::repair(ETTreeNode *pNode) {
    if (pNode->color == BLACK) return;         // done
    if (pNode->parent == nullptr) {
        setColor(pNode, BLACK);
//        pNode->color = BLACK;
        return;
    }         // done

    if (pNode->parent->color == BLACK) return; // done
// tehát pNode és apja is piros, fix needed. apja nem lehet a gyökér, mert az fekete
    if (uncle(pNode) != nullptr && uncle(pNode)->color == RED) {
// piros a csúcs apja és nagybátyja is -> nagyapjuk nem -> ezek hárman cseréljenek színt
        pNode->parent->color = uncle(pNode)->color = BLACK;
        pNode->parent->parent->color = RED;
        repair(pNode->parent->parent);      //lehet a nagyapa elromlott
        return;
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
        setColor(pNode->parent->parent, RED);
//        pNode->parent->parent->color = RED;
    }

    if (zigzig(pNode)) {
        rotateRight(pNode->parent->parent);
    } else {
        if (pNode->parent->parent != nullptr) {
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
    if (pNode != &theNullNode && pNode != nullptr) {
        pNode->color = color;
        return;
    }

}

void ETForest::insert(int u, int v) {

    ETTreeNode *T1 = first[v];
    ETTreeNode *uNode = new ETTreeNode(nullptr, &theNullNode, &theNullNode, last[u]->color, last[u]->nodeId);
    uNode->rank = last[u]->rank;

    if (minimum(T1)->nodeId != v) {
        reroot(v);
        T1 = findRoot(T1);
    }
    if (minimum(last[u])->nodeId != u) {
        reroot(u);
    }
    //állítsuk vissza gyökérre

    std::pair<ETTreeNode *, ETTreeNode *> spl = split(last[u]);
    ETTreeNode *T2 = spl.first;
    ETTreeNode *T3 = spl.second;

    ETTreeNode *T4 = join(T2, uNode, T1);
    std::cout<<"U: "<<u<< " V: " <<v<<std::endl;
    inOrder(T4);
    std::cout<<"------------------"<<std::endl;
    //keressük meg T3 minimális nodeját
    ETTreeNode *minNode = minimum(T3);
    //töröljük ki és mentsük el a törölt nodeot
    minNode = newDelete(minNode);
    if (minNode->left == &theNullNode && minNode->right == &theNullNode && minNode->parent == nullptr) {

        T3 = &theNullNode;
        setBackToOneNode(minNode);
    } else {
        minNode->parent = nullptr;
        minNode->left = &theNullNode;
        minNode->right = &theNullNode;
    }
    T4 = join(T4, minNode, T3);
    if (first[minNode->nodeId] == minNode) {
        first[minNode->nodeId] = uNode;
    }
    std::cout << "T4 inorder: " << std::endl;
    inOrder(T4);
}

void ETForest::remove(int u, int v) {
    ETTreeNode *T0, *T1, *T2, *T3, *T4, *vNode;
    if (predecessor(first[v]) != nullptr && predecessor(first[v])->nodeId == u) {
        std::swap(u, v);
    }
    vNode = new ETTreeNode(nullptr, &theNullNode, &theNullNode, last[v]->color, last[v]->nodeId);
    vNode->rank = last[v]->rank;
    ETTreeNode *akarmi = findRoot(first[u]);

    std::pair<ETTreeNode *, ETTreeNode *> firstSplitResult = split(first[u]);
    T0 = firstSplitResult.first;
    T1 = firstSplitResult.second;

    std::cout << "inorder: T0: " << std::endl;
    inOrder(T0);
    std::cout << "inorder: T1: " << std::endl;
    inOrder(findRoot(T1));
    std::pair<ETTreeNode *, ETTreeNode *> secondSplitResult = split(last[u]);
    //kisebb egyenlőek ->T3-ba
    T3 = secondSplitResult.first;
    T2 = secondSplitResult.second;
    std::cout << "inorder: T2: " << std::endl;
    inOrder(T2);
    std::cout << "inorder: T3: " << std::endl;
    inOrder(T3);
    ETTreeNode *minT2, *maxT0;

    if (oneNode(T2)) {
        minT2 = T2;
        T2 = &theNullNode;

    } else {
        minT2 = newDelete(minimum(T2));
        minT2 = setBackToOneNode(minT2);
    }

    if (oneNode(T0)) {
        maxT0 = T0;
        T0 = &theNullNode;
    } else {
        maxT0 = newDelete(maximum(T0));
        maxT0 = setBackToOneNode(maxT0);
    }
    T4 = join(T0, vNode, T2);
    std::cout << "uj inorder" << std::endl;
    inOrder(T4);
}

void ETForest::reroot(int u) {
    ETTreeNode *pNode = first[u];
    int it = 1;
    std::stack<ETTreeNode *> nodeStack;
    //tegyük bele pNode-ot a verembe
    nodeStack.push(pNode);
    //megkeressük pNode megelőzőjét nullNodera sosem tud lépni, ha csúcsnak nincs megelőzője akkor nullptr-t ad vissza
    pNode = predecessor(pNode);

    while (pNode != nullptr && predecessor(pNode) != nullptr) {
        nodeStack.push(pNode);
        pNode = predecessor(pNode);
        ++it;
    }
    //TODO:: it > this->N
    if (it > this->N) {
        ETTreeNode *T1, *T2, *T3, *T4;
        std::pair<ETTreeNode *, ETTreeNode *> tmp = split(first[u]);
        T1 = tmp.first;
        T2 = tmp.second;
        if (oneNode(T2)) {
            T2 = &theNullNode;
            std::cout << "T2 egy elemu fa" << std::endl;
        } else {
            newDelete(maximum(T2));
        }
        //deleteNode(maximum(T2));
        ETTreeNode *w;
        if (oneNode(T1)) {
            w = T1;
            T1 = &theNullNode;
        } else {
            w = newDelete(minimum(T1));
            w = setBackToOneNode(w);
        }


        T3 = join(T2, w, T1);
        T4 = join(T3, new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, u), &theNullNode);
        ETTreeNode **firstcpy;
        ETTreeNode **lastcpy;
        firstcpy = new ETTreeNode *[this->N];
        lastcpy = new ETTreeNode *[this->N];
        for (int i = 0; i < this->N; ++i) {
            firstcpy[i] = nullptr;
            lastcpy[i] = nullptr;
        }
        ETTreeNode *tmpT4 = T4;
        tmpT4 = minimum(tmpT4);
        firstcpy[tmpT4->nodeId] = tmpT4;
        lastcpy[tmpT4->nodeId] = tmpT4;

        while ((tmpT4 = successor(tmpT4)) != nullptr) {
            if (firstcpy[tmpT4->nodeId] == nullptr) {
                firstcpy[tmpT4->nodeId] = tmpT4;

            }
            lastcpy[tmpT4->nodeId] = tmpT4;
        }

        for (int i = 0; i < this->N; ++i) {
            if (firstcpy[i] != nullptr) {
                first[i] = firstcpy[i];
            }
            if (lastcpy[i] != nullptr) {
                last[i] = lastcpy[i];
            }
        }

    } else {
        while (!nodeStack.empty()) {
            ETTreeNode *pop = nodeStack.top();
            nodeStack.pop();
            u = pop->nodeId;
            ETTreeNode *T1, *T2, *T3, *T4, *uLast;
            std::pair<ETTreeNode *, ETTreeNode *> tmp = split(first[u]);
            T1 = tmp.first;
            T2 = tmp.second;
            if (oneNode(T2)) {
                std::cout << "T2 egy egy elemű fa" << std::endl;
                T2 = &theNullNode;
            } else {
                newDelete(maximum(T2));
            }
            //TODO: nullptr min
            ETTreeNode *w;
            if (oneNode(T1)) {
                w = T1;
                T1 = &theNullNode;

            } else {
                w = newDelete(minimum(T1));
                w = setBackToOneNode(w);
            }


            T3 = join(T2, w, T1);
            uLast = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, u);
            ETTreeNode *uLastSeen = last[u];
            ETTreeNode *uSucc = successor(uLastSeen);


            if (uSucc != last[uSucc->nodeId]) {
                ETTreeNode *tmporal = last[uSucc->nodeId];
                std::cout << "nem jo :(" << std::endl;

            } else {
                std::cout << "hurrá" << std::endl;
            }

            T4 = join(T3, uLast, &theNullNode);

            ETTreeNode *uLastPred = predecessor(uLast);

            int uParent = uSucc->nodeId;

            first[uParent] = uSucc;
            last[uParent] = uLastPred;
            last[u] = uLast;
        }
    }
}

bool ETForest::oneNode(ETTreeNode *pNode) {
    if (pNode->parent == nullptr && pNode->right == &theNullNode && pNode->left == &theNullNode) {
        return true;
    }
    return false;
}

ETTreeNode *ETForest::setBackToOneNode(ETTreeNode *pNode) {
    pNode->parent = nullptr;
    pNode->right = &theNullNode;
    pNode->left = &theNullNode;
}

ETTreeNode *ETForest::deleteNode(ETTreeNode *node) {
    if (node == &theNullNode)
        return &theNullNode;
    if (node == findRoot(node->nodeId) && node->left == &theNullNode && node->right == &theNullNode) {
        ETTreeNode *oneNode = node;
        node = &theNullNode;
        return oneNode;
    }

    if (node->color == RED || node->left->color == RED || node->right->color == RED) {
        ETTreeNode *child = node->left != &theNullNode ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            //delete (node);
            return node;
        } else {
            node->parent->right = child;
            if (child != nullptr && child != &theNullNode)
                child->parent = node->parent;
            setColor(child, BLACK);
            //delete (node);
            return node;
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
                        // break;
                    }
                }
            }
        }
        if (node->parent != nullptr && node == node->parent->left)
            node->parent->left = nullptr;
        else if (node->parent != nullptr)
            node->parent->right = nullptr;
        //delete (node);
        setColor(root, BLACK);
        return node;
    }
}


ETTreeNode *ETForest::newDelete(ETTreeNode *n) {
    ETTreeNode *child;
    ETTreeNode *save = n;

    if (n == &theNullNode)

        return &theNullNode;

    if (n->left != &theNullNode && n->right != &theNullNode) {

        ETTreeNode *pred = predecessor(n);
        n = pred;

    }

    assert(n->left == &theNullNode || n->right == &theNullNode);

    child = n->right == &theNullNode ? n->left : n->right;

    if (n->color == BLACK) {
        setColor(n, child->color);


        deleteCase1(n);

    }
//TODO: ha a predecesszor létezik, akkor cseréljük ki őt is

    replaceNode(n, child);
    return n;

    // verify_properties(t);
}

void ETForest::deleteCase1(ETTreeNode *n) {
    if (n->parent == &theNullNode || n->parent == nullptr)

        return;

    else

        deleteCase2(n);
}

void ETForest::deleteCase2(ETTreeNode *n) {
    if (sibling(n)->color == RED) {

        n->parent->color = RED;

        sibling(n)->color = BLACK;

        if (n == n->parent->left)

            rotateLeft(n->parent);

        else

            rotateRight(n->parent);

    }

    deleteCase3(n);
}

void ETForest::deleteCase3(ETTreeNode *n) {
    if (n->parent->color == BLACK && sibling(n)->color == BLACK &&

        sibling(n)->left->color == BLACK && sibling(n)->right->color == BLACK) {

        sibling(n)->color = RED;

        deleteCase1(n->parent);

    } else

        deleteCase4(n);
}

void ETForest::deleteCase4(ETTreeNode *n) {
    if (n->parent->color == RED && sibling(n)->color == BLACK &&

        sibling(n)->left->color == BLACK && sibling(n)->right->color == BLACK) {

        sibling(n)->color = RED;

        n->parent->color = BLACK;

    } else

        deleteCase5(n);
}

void ETForest::deleteCase5(ETTreeNode *n) {
    if (n == n->parent->left && sibling(n)->color == BLACK &&

        sibling(n)->left->color == RED && sibling(n)->right->color == BLACK) {

        sibling(n)->color = RED;

        sibling(n)->left->color = BLACK;

        rotateRight(sibling(n));

    } else if (n == n->parent->right && sibling(n)->color == BLACK &&

               sibling(n)->right->color == RED && sibling(n)->left->color == BLACK) {

        sibling(n)->color = RED;

        sibling(n)->right->color = BLACK;

        rotateLeft(sibling(n));

    }

    deleteCase6(n);
}

void ETForest::deleteCase6(ETTreeNode *n) {
    sibling(n)->color = n->parent->color;

    n->parent->color = BLACK;

    if (n == n->parent->left) {

        assert (sibling(n)->right->color == RED);

        sibling(n)->right->color = BLACK;

        rotateLeft(n->parent);

    } else {

        assert (sibling(n)->left->color == RED);

        sibling(n)->left->color = BLACK;

        rotateRight(n->parent);

    }
}

void ETForest::replaceNode(ETTreeNode *oldn, ETTreeNode *newn) {


    if (oldn->parent == nullptr) {
        newn->parent = nullptr;

    } else {

        if (oldn == oldn->parent->left)

            oldn->parent->left = newn;

        else

            oldn->parent->right = newn;

    }

    if (newn != &theNullNode && newn != nullptr) {

        newn->parent = oldn->parent;

    }
}

void ETForest::setParent(ETTreeNode *set, ETTreeNode *toSet) {
    if (set != &theNullNode && set != nullptr && toSet != &theNullNode) {
        set->parent = toSet;
    }
}

void ETForest::setRightChild(ETTreeNode *set, ETTreeNode *toSet) {
    if (set != &theNullNode && set != nullptr && toSet != nullptr) {
        set->right = toSet;
    }
}

void ETForest::setLeftChild(ETTreeNode *set, ETTreeNode *toSet) {
    if (set != &theNullNode && set != nullptr && toSet != nullptr) {
        set->left = toSet;
    }
}

void ETForest::setRank(ETTreeNode *set, int r) {
    if (set != &theNullNode && set != nullptr) {
        set->rank = r;
    }
}