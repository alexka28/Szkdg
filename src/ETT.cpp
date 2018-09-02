#include <iostream>
#include "ETT.h"
#include <stack>
#include <cassert>
#include <cmath>

ETTreeNode::ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color) :
        parent(parent),
        left(left),
        right(right),
        color(color),
        rank(0) {
}

ETTreeNode::ETTreeNode(ETTreeNode *parent, ETTreeNode *left, ETTreeNode *right, int color, int nodeId) :
        parent(parent),
        left(left),
        right(right),
        color(color),
        nodeId(nodeId),
        rank(1) {
}

ETTreeNode theNullNode(nullptr, nullptr, nullptr, BLACK);

ETForest::ETForest(int n) {
    first = new ETTreeNode *[n];
    last = new ETTreeNode *[n];
    this->N = n;
    double tmpLog = log2(n);
    this->logN = ceil(tmpLog);

    for (int i = 0; i < n; ++i) {
        ETTreeNode *node = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, i);

        first[i] = node;
        last[i] = node;
    }


}

void ETForest::inOrder(ETTreeNode *pNode) {
    if (pNode != nullptr && pNode != &theNullNode && pNode->left != &theNullNode) {
        inOrder(pNode->left);
    }
    if (pNode != nullptr) { std::cout << pNode->nodeId << "-"; }

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
    ETTreeNode *predU, *predV;
    predU = predecessor(first[u]);
    predV = predecessor(first[v]);
    if (predU != nullptr && predU->nodeId == v) {
        return true;
    }
    //TODO: leegyszerűsíthető, ha a felső feltételbe beírjuk vagyolással, mivel mind a kettő trueval tér vissza
    if (predV != nullptr && predV->nodeId == u) {
        return true;
    }
    return false;

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


ETTreeNode *ETForest::join(ETTreeNode *x, ETTreeNode *u, ETTreeNode *y) {


    if (x->rank == y->rank) {
        setLeftChild(u, x);
        setRightChild(u, y);
        setParent(x, u);
        setParent(y, u);
        setColor(u, BLACK);
        updateRank(u);


    } else if (x->rank < y->rank) {

        ETTreeNode *N;
        //ha az y még egy elemű fa, akkor elég a bal fiát u-ra állítani
        if (x == &theNullNode && oneNode(y)) {
            setLeftChild(y, u);
            setParent(u, y);
            setColor(u, RED);
            setRank(u, 0);
            repair(u);
            updateRank(u);
        } else if (x == &theNullNode && !oneNode(y)) {

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
                updateRank(u);
            } else {
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
            updateRank(u);


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
            updateRank(u);
        } else if (y == &theNullNode && !oneNode(x)) {

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
                updateRank(u);
            } else {
                N = N->right;
                setRightChild(N, u);
                setParent(u, N);
                setColor(u, RED);
                setRank(u, 0);
                repair(u);
                updateRank(u);

            }


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
            updateRank(u);

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

    if (pNode->parent != nullptr) {
        if (pNode == pNode->parent->left) {
            setLeftChild(pNode->parent, y);
        } else {
            setRightChild(pNode->parent, y);
        }
    }

    setParent(pNode, y);
    setRightChild(pNode, z);
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

    if (pNode->parent != nullptr) {
        if (pNode == pNode->parent->left) {
            setLeftChild(pNode->parent, y);
        } else {
            setRightChild(pNode->parent, y);
        }
    }

    setParent(pNode, y);
    setLeftChild(pNode, z);
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
        return;
    }         // done

    if (pNode->parent->color == BLACK) return; // done
// tehát pNode és apja is piros, fix needed. apja nem lehet a gyökér, mert az fekete
    if (uncle(pNode) != nullptr && uncle(pNode)->color == RED) {
// piros a csúcs apja és nagybátyja is -> nagyapjuk nem -> ezek hárman cseréljenek színt
        pNode->parent->color = uncle(pNode)->color = BLACK;
        pNode->parent->parent->color = RED;
        //állítsuk be apa, nagybácsi, nagyapa rangját
        setRank(pNode->parent, pNode->parent->rank + 1);
        setRank(uncle(pNode), uncle(pNode)->rank + 1);
        //mivel nagyapa piros, ezért az ő rankja biztosan a bal gyerekének a rankja lesz
        setRank(pNode->parent->parent, pNode->parent->parent->left->rank);
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
    //keressük meg T3 minimális nodeját
    ETTreeNode *minNode; //= minimum(T3);
    //töröljük ki és mentsük el a törölt nodeot
    //TODO: check, hogy a minimum nem a root-e!!!!!
//TODO: keressünk ide valami kokkot
    if (oneNode(T3)) {
        minNode = T3;
        T3 = &theNullNode;

    }
        //ha ugyanaz a minimum mint a gyökér és T2 nem oneNode, akkor van egy jobb gyereke, ő lesz az új gyökér
    else if (minimum(T3) == findRoot(T3)) {
       minNode = findRoot(T3);
        T3 = T3->right;
        setParent(T3, nullptr);
        setColor(T3, BLACK);
        setRank(T3, 1);
        setBackToOneNode(minNode);
    } else {
        minNode = newDelete(minimum(T3));
        minNode = setBackToOneNode(minNode);
        T3 = findRoot(T3);
    }























        //minNode = newDelete(minNode);


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


}

void ETForest::remove(int u, int v) {
    ETTreeNode *T0, *T1, *T2, *T3, *T4, *vNode;
    if (predecessor(first[v]) != nullptr && predecessor(first[v])->nodeId == u) {
        std::swap(u, v);
    }
    vNode = new ETTreeNode(nullptr, &theNullNode, &theNullNode, last[v]->color, last[v]->nodeId);
    vNode->rank = last[v]->rank;


    std::pair<ETTreeNode *, ETTreeNode *> firstSplitResult = split(first[u]);
    T0 = firstSplitResult.first;
    T1 = firstSplitResult.second;


    inOrder(findRoot(T1));
    std::pair<ETTreeNode *, ETTreeNode *> secondSplitResult = split(last[u]);
    //kisebb egyenlőek ->T3-ba
    T3 = secondSplitResult.first;
    T2 = secondSplitResult.second;

    inOrder(T3);
    ETTreeNode *minT2, *maxT0;

    if (oneNode(T2)) {
        minT2 = T2;
        T2 = &theNullNode;

    }
        //ha ugyanaz a minimum mint a gyökér és T2 nem oneNode, akkor van egy jobb gyereke, ő lesz az új gyökér
    else if (minimum(T2) == findRoot(T2)) {
        minT2 = findRoot(T2);
        T2 = T2->right;
        setParent(T2, nullptr);
        setColor(T2, BLACK);
        setRank(T2, 1);
        setBackToOneNode(minT2);
    } else {
        minT2 = newDelete(minimum(T2));
        minT2 = setBackToOneNode(minT2);
        T2 = findRoot(T2);
    }

    if (oneNode(T0)) {
        maxT0 = T0;
        T0 = &theNullNode;
    }
        //ha nem egy elemű fa, és a maximuma a gyökér, akkor van egy bal gyereke
    else if (maximum(T0) == findRoot(T0)) {
        maxT0 = findRoot(T0);
        T0 = T0->left;
        setBackToOneNode(T0);
        setColor(T0, BLACK);
        setRank(T0, 1);
        setBackToOneNode(maxT0);

    } else {
        maxT0 = newDelete(maximum(T0));
        maxT0 = setBackToOneNode(maxT0);
        T0 = findRoot(T0);
    }
    T4 = join(T0, vNode, T2);
    if (maxT0 == first[v]) {
        first[v] = vNode;
    }
    if (minT2 == last[v]) {
        last[v] = vNode;
    }

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
    //TODO:: it > this->N vagy logN
    if (it > this->logN) {
        ETTreeNode *T1, *T2, *T3, *T4;
        std::pair<ETTreeNode *, ETTreeNode *> tmp = split(first[u]);
        T1 = tmp.first;
        T2 = tmp.second;
        if (oneNode(T2)) {
            T2 = &theNullNode;
        } else if (maximum(T2) == findRoot(T2)) {
            T2 = T2->left;
            setBackToOneNode(T2);
            setColor(T2, BLACK);
            setRank(T2, 1);
        } else {
            newDelete(maximum(T2));
            T2 = findRoot(T2);
        }
        ETTreeNode *w;
        if (oneNode(T1)) {
            w = T1;
            T1 = &theNullNode;
        } else if (minimum(T1) == findRoot(T1)) {
            w = findRoot(T1);
            T1 = T1->right;
            setParent(T1, nullptr);
            setColor(T1, BLACK);
            setRank(T1, 1);
            setBackToOneNode(w);
        } else {
            w = newDelete(minimum(T1));
            w = setBackToOneNode(w);
            T1 = findRoot(T1);
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
            } else if (maximum(T2) == findRoot(T2)) {
                T2 = T2->left;
                setBackToOneNode(T2);
                setColor(T2, BLACK);
                setRank(T2, 1);


            } else {
                newDelete(maximum(T2));
                findRoot(T2);
            }
            //TODO: nullptr min
            ETTreeNode *w;
            if (oneNode(T1)) {
                w = T1;
                T1 = &theNullNode;

            } else if (minimum(T1) == findRoot(T1)) {
                w = findRoot(T1);
                T1 = T1->right;
                setParent(T1, nullptr);
                setColor(T1, BLACK);
                setRank(T1, 1);
                setBackToOneNode(w);
            } else {
                w = newDelete(minimum(T1));
                w = setBackToOneNode(w);
                T1 = findRoot(T1);
            }


            T3 = join(T2, w, T1);
            uLast = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, u);
            ETTreeNode *uLastSeen = last[u];
            ETTreeNode *uSucc = successor(uLastSeen);

//TODO: ha uSucc nullptr akkor nem tudja kikérni a nodeId-t ami lentebb uParentnél is problémás lesz!
            if (uSucc != last[uSucc->nodeId]) {
                ETTreeNode *tmporal = last[uSucc->nodeId];
                std::cout << "nem jo :(" << std::endl;

            } else {
                std::cout << "hurrá" << std::endl;
            }

            T4 = join(T3, uLast, &theNullNode);

            ETTreeNode *uLastPred = predecessor(uLast);
//TODO: lásd feljebb
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
    return pNode;
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
    //TODO: updateRank
    updateRank(child);

    if (child == &theNullNode) { updateRank(n); }
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
//TODO: updateRank(n->parent);
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
        updateRank(sibling(n)->right);

        rotateLeft(n->parent);

    } else {

        assert (sibling(n)->left->color == RED);

        sibling(n)->left->color = BLACK;
        updateRank(sibling(n)->left);
        rotateRight(n->parent);

    }
}

void ETForest::replaceNode(ETTreeNode *oldn, ETTreeNode *newn) {

    if (oldn->parent == nullptr) {
        newn->parent = nullptr;

    } else {

        if (isLeft(oldn)) {
            setLeftChild(oldn->parent, newn);
        } else {
            oldn->parent->right = newn;
        }


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
