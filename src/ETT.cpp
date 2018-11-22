#include "ETT.h"
#include <iostream>
#include "ETTQueries.h"
#include <stack>
#include <cassert>
#include <cmath>
#include "ETTSetter.h"
#include "ETTUpdater.h"

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
bool bid = false;
bool isFirstTime = false;

ETTreeNode::ETTreeNode(int color, int nodeId, int rank, ETTreeNode *parent) :
        parent(parent),
        left(&theNullNode),
        right(&theNullNode),
        color(color),
        nodeId(nodeId),
        rank(rank) {

}

ETForest::ETForest(int n) {
    first = new ETTreeNode *[n];
    last = new ETTreeNode *[n];
    this->N = n;
    double tmpLog = log2(n);
    this->logN = static_cast<int> (ceil(tmpLog));

    for (int i = 0; i < n; ++i) {
        auto node = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, i);
        first[i] = node;
        last[i] = node;
    }
}


ETTreeNode *ETForest::findRoot(int u) {
    ETTreeNode *pNode = this->first[u];
    while (pNode->parent != nullptr) {
        pNode = pNode->parent;
    }
    return pNode;
}


bool ETForest::contains(int u, int v) {
    auto predU = predecessor(first[u]);
    auto predV = predecessor(first[v]);
    return (predU != nullptr && predU->nodeId == v) || (predV != nullptr && predV->nodeId == u);
}


ETTreeNode *ETForest::join(ETTreeNode *x, ETTreeNode *j, ETTreeNode *y) {


    if (x->rank == y->rank) {
        setLeftChild(j, x);
        setRightChild(j, y);
        setParent(x, j);
        setParent(y, j);
        setColor(j, BLACK);
        updateRank(j);


    } else if (x->rank < y->rank) {

        ETTreeNode *A;
        //ha az y még egy elemű fa, akkor elég a bal fiát j-re állítani
        if (x == &theNullNode && isOneNode(y)) {
            if (y->color == RED) {
                y->color = BLACK;
                y->rank = 1;
            }
            setLeftChild(y, j);
            setParent(j, y);
            setColor(j, RED);
            setRank(j, 0);
            repair(j);
            updateRank(j);
        } else if (x == &theNullNode && !isOneNode(y)) {
            if (y->color == RED) {
                y->color = BLACK;
                ++y->rank;
            }
            while (y->rank != 1 || y->color != BLACK) {
                y = y->left;
            }
            A = y;
            //ha bal oldalt nullNode van, akkor csak tegyük be az j-t mint egy elemű fánál és done
            if (A->left == &theNullNode) {
                assert(A->right == &theNullNode || (A->right->color == RED && A->right->rank == 0));
                setLeftChild(A, j);
                setParent(j, A);
                setColor(j, RED);
                setRank(j, 0);
                repair(j);
                updateRank(j);
            } else {
                A = A->left;
                assert(A->right == &theNullNode || (A->right->color == RED && A->right->rank == 0));
                setLeftChild(A, j);
                setParent(j, A);
                setColor(j, RED);
                setRank(j, 0);
                repair(j);
                updateRank(j);

            }


        }
            //ha nem nullNode-ot kell joinolni
        else {
            if (y->color == RED) {
                y->color = BLACK;
                ++y->rank;
            }
            bool isNullNode = false;
            if (isOneNode(x) && x->color == RED) {
                assert(x->rank == 0);
                while (y->rank != x->rank + 1) {
                    y = y->left;
                }
                if (y->left != &theNullNode) {
                    y = y->left;
                }
                if (y->color == BLACK && y->left != &theNullNode) {
                    y = y->left;
                } else if (y->color == BLACK && y->left == &theNullNode) {
                    isNullNode = true;
                } else {
                    assert(y->color == RED && y->rank == 0);
                }
            } else {
                while (y->rank != x->rank) {
                    y = y->left;
                }
            }

            A = y;


            if (isNullNode) {
                A->left = j;
                j->parent = A;
                j->right = &theNullNode;
                j->left = x;
                x->parent = j;
//case 1
                if (A->right->color == RED) {
                    setColor(j, BLACK);
                    setColor(A->right, BLACK);
                    setColor(A, RED);
                    assert(A->right->rank == 0);
                    ++A->right->rank;
                    j->rank = 1;
                    A->rank = 1;

                    repair(A);
                    updateRank(A);
                }
                    //case 2.3
                else if (j->right->color == BLACK && x->color == RED) {
                    setColor(A, RED);
                    setColor(j, BLACK);
                    setRank(A, 0);
                    setRank(j, 1);
                    rotateRight(A);
                    updateRank(j);
                }

            } else {

                assert(A->parent->color == BLACK);
                auto B = A->parent;
                auto Br = B->right;
                assert(Br != A);
                assert(B->left == A);

                setParent(j, A->parent);
                setLeftChild(A->parent, j);
                setParent(A, j);
                setRightChild(j, A);
                setLeftChild(j, x);
                setParent(x, j);
                //case 1
                if (B->right->color == RED) {
                    setColor(j, BLACK);
                    setColor(B->right, BLACK);
                    setColor(B, RED);
                    setRank(j, x->rank + 1);
                    setRank(Br, j->rank);
                    setRank(B, j->rank);
                    assert(B->left == j);
                    repair(B);
                    updateRank(j);
                }
                    //case 2
                else {
                    //sub 2.1
                    if (A->color == BLACK && x->color == BLACK) {
                        setColor(j, RED);
                        updateRank(j);
                    }
                        //sub 2.2
                    else if (A->color == RED && x->color == RED) {
                        setColor(x, BLACK);
                        setColor(j, RED);
                        setRank(x, B->rank);
                        setRank(j, B->rank);
                        rotateRight(B);
                        assert(j->right == B);
                        assert(j->left == x);
                        repair(j);
                    }
                        //sub 2.3
                    else if (A->color == BLACK && x->color == RED) {
                        setColor(j, BLACK);
                        setColor(B, RED);
                        setRank(B, x->rank);
                        setRank(j, B->rank + 1);
                        rotateRight(B);
                    }
                        //sub 2.4
                    else if (A->color == RED && x->color == BLACK) {
                        rotateLeftWoRankUpdate(j);
                        rotateRightWoRankUpdate(B);
                        setColor(B, RED);
                        setColor(j, RED);
                        setColor(A, BLACK);
                        setRank(B, Br->rank);
                        setRank(j, B->rank);
                        setRank(A, A->left->rank + 1);
                        assert(A->left == j);
                        assert(A->right == B);
                        updateRank(A);
                    }
                }


            }
        }


    } //x > y
    else {
        ETTreeNode *A;
        //ha x még egy elemű fa, akkor elég a jobb fiát u-ra beállítani
        if (y == &theNullNode && isOneNode(x)) {
            if (x->color == RED) {
                x->color = BLACK;
                x->rank = 1;
            }
            setRightChild(x, j);
            setParent(j, x);
            setColor(j, RED);
            setRank(j, 0);
            repair(j);
            updateRank(j);
        } else if (y == &theNullNode && !isOneNode(x)) {
            if (x->color == RED) {
                x->color = BLACK;
                ++x->rank;
            }
            while (x->rank != 1 || x->color != BLACK) {

                x = x->right;
            }

            A = x;
            //ha nullNode a jobb gyerek, akkor csak simán behúzzuk u-t jobbra mint egy elemű fánál és done
            if (A->right == &theNullNode) {
                assert(A->left == &theNullNode || (A->left->rank == 0 && A->left->color == RED));
                setRightChild(A, j);
                setParent(j, A);
                setColor(j, RED);
                setRank(j, 0);
                repair(j);
                updateRank(j);
            } else {
                A = A->right;
                assert(A->left == &theNullNode || (A->left->rank == 0 && A->left->color == RED));
                setRightChild(A, j);
                setParent(j, A);
                setColor(j, RED);
                setRank(j, 0);
                repair(j);
                updateRank(j);

            }


        } else {
            bool isNullNode = false;
            if (x->color == RED) {
                x->color = BLACK;
                ++x->rank;
            }
            if (isOneNode(y) && y->color == RED) {
                assert(y->rank == 0);
                while (x->rank != y->rank + 1) {
                    x = x->right;
                }
                if (x->right != &theNullNode) {
                    x = x->right;
                }
                if (x->color == BLACK && x->right != &theNullNode) {
                    x = x->right;
                } else if (x->color == BLACK && x->right == &theNullNode) {
                    isNullNode = true;
                } else {
                    assert(x->color == RED && x->rank == 0);
                }
            } else {
                while (x->rank != y->rank) {
                    x = x->right;
                }
            }


            A = x;

            if (isNullNode) {
                assert(A->color == BLACK && A->rank == 1 && A->right == &theNullNode);
                A->right = j;
                j->parent = A;
                j->left = &theNullNode;
                j->right = y;
                y->parent = j;
                //case 1
                if (A->left->color == RED) {
                    setColor(j, BLACK);
                    setColor(A->left, BLACK);
                    setColor(A, RED);
                    assert(A->left->rank == 0);
                    ++A->left->rank;
                    j->rank = 1;
                    A->rank = 1;

                    repair(A);
                    updateRank(A);
                }
                    //case 2.3 other cases dont need bcuz y always red and A child is always black (nullnode)
                else if (j->left->color == BLACK && y->color == RED) {
                    setColor(A, RED);
                    setColor(j, BLACK);
                    setRank(A, 0);
                    setRank(j, 1);
                    rotateLeft(A);
                    updateRank(j);
                }

            } else {


                assert(A->parent->color == BLACK);
                auto B = A->parent;
                assert(B->left != A);
                setParent(j, A->parent);
                setRightChild(A->parent, j);
                setParent(A, j);
                setRightChild(j, y);
                setLeftChild(j, A);
                setParent(y, j);
                //case 1
                if (B->left->color == RED) {
                    setColor(j, BLACK);
                    setColor(B->left, BLACK);
                    setColor(B, RED);
                    setRank(B->left, B->left->rank + 1);
                    setRank(j, B->left->rank);
                    repair(B);
                    updateRank(B);
                }
                    //case 2
                else {
                    //case 2.1
                    if (A->color == BLACK && y->color == BLACK) {
                        setColor(j, RED);
                        updateRank(j);
                    }
                        //case 2.2
                    else if (A->color == RED && y->color == RED) {
                        setColor(B, BLACK);
                        setColor(y, BLACK);
                        setColor(j, RED);
                        setRank(B, B->left->rank + 1);
                        setRank(y, B->rank);
                        setRank(j, j->left->rank);
                        rotateLeft(B);
                        assert(j->left == B);
                        assert(j->right == y);
                        repair(j);
                        updateRank(j);
                    } else if (A->color == BLACK && y->color == RED) {
                        setColor(B, RED);
                        setColor(j, BLACK);
                        setRank(B, B->left->rank);
                        setRank(j, j->left->rank + 1);
                        rotateLeft(B);
                        assert(j->left == B);
                        assert(j->right == y);
                        updateRank(j);
                    } else if (A->color == RED && y->color == BLACK) {
                        rotateRightWoRankUpdate(j);
                        rotateLeftWoRankUpdate(B);
                        setColor(j, RED);
                        setColor(A, BLACK);
                        setColor(B, RED);
                        setRank(A, A->left->rank + 1);
                        setRank(B, B->left->rank);
                        setRank(j, B->rank);
                        assert(A->left == B);
                        assert(A->right == j);
                        updateRank(A);
                    }
                }
            }
        }
    }
    return findRoot(j);
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
        setParent(T1->left, T1);
        setParent(T1->right, T1);
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
    if (pNodeRight->color == RED) {
        pNodeRight->color = BLACK;
        ++pNodeRight->rank;
    }
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


void ETForest::insert(int u, int v) {

    auto *T1 = first[v];
    T1 = findRoot(T1);

    auto uNode = new ETTreeNode(nullptr, &theNullNode, &theNullNode, last[u]->color, last[u]->nodeId);
    uNode->rank = last[u]->rank;

    if (ETTMinimum(T1)->nodeId != v) {
        reroot(v);
        T1 = findRoot(T1);
    }

    if (ETTMinimum(last[u])->nodeId != u) {
        reroot(u);
    }
    //állítsuk vissza gyökérre

    std::pair<ETTreeNode *, ETTreeNode *> spl = splitInRemove(last[u]);
    auto T2 = spl.first;
    auto T3 = spl.second;

    ETTreeNode *T4 = join(T2, uNode, T1);


    //keressük meg T3 minimális nodeját
    auto minNode = minimum(T3);
    auto nodeToJoin = new ETTreeNode(nullptr, &theNullNode, &theNullNode, minNode->color, minNode->nodeId);
    nodeToJoin->rank = minNode->rank;

    bool needToUpdate = false;
    bool needToUpdateL = false;
    if (first[u] == minNode) {
        needToUpdate = true;
    }

    if (isOneNode(T3)) {
        nodeToJoin = T3;
        T3 = &theNullNode;
    }
        //ha T3 és a minNode ugyan oda mutat, akkor a törlés nem tudja ténylegesen a minNode-ot törölni, hiszen akkor a saját címét kéne módosítania
        //erre jó megoldás lehet, ha a törlésnek átadjuk ptr refként a T3-at és ott hasonlítjuk össze a minNoddal és ott végezzük el ezt a műveletet
        //ebben az esetben T3-nak csak jobb gyerek van (hiszen ő a minimum)
    else if (T3 == minNode) {
        if (last[u] == T3) {
            last[u] = nodeToJoin;
        }
        T3 = T3->right;
        setColorWithRankUpdate(T3, BLACK);
    }
        //egyébként pedig törölhetünk
    else {
        if (last[u] == minNode) {
            needToUpdateL = true;
        }
        newDelete(minNode);
    }

    T4 = join(T4, nodeToJoin, T3);
    if (needToUpdate) {
        first[u] = uNode;
    }
    if (needToUpdateL) {
        last[u] = nodeToJoin;
    }
}

void ETForest::remove(int u, int v) {
    ETTreeNode *T0, *T1, *T2, *T3, *T4, *vNode;
    if (predecessor(first[v]) != nullptr && predecessor(first[v])->nodeId == u) {
        std::swap(u, v);
    }
    vNode = new ETTreeNode(nullptr, &theNullNode, &theNullNode, last[v]->color, last[v]->nodeId);
    vNode->rank = last[v]->rank;


    auto firstSplitResult = splitInRemove(first[u]);
    T0 = firstSplitResult.first;
    T1 = firstSplitResult.second;
    T0 = findRoot(T0);
    T1 = findRoot(T1);

    assert(maximum(findRoot(T0))->nodeId == v);


    assert(minimum(T1) == first[u]);
    assert(findRoot(first[u]) == findRoot(last[u]));
    assert(findRoot(last[v]) == findRoot(first[u]));
    auto secondSplit = successor(last[u]);
    assert(secondSplit != nullptr);

    auto secondSplitResult = splitInRemove(secondSplit);
    //kisebb egyenlőek ->T3-ba
    T3 = secondSplitResult.first;
    T2 = secondSplitResult.second;

    T2 = findRoot(T2);
    T3 = findRoot(T3);


    ETTreeNode *minT2, *maxT0;

    if (isOneNode(T2)) {
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
        minT2 = minimum(T2);
        auto tmpNode = new ETTreeNode(nullptr, &theNullNode, &theNullNode, minT2->color, minT2->nodeId);
        tmpNode->rank = minT2->rank;
        if (minT2 == last[v]) {
            last[v] = tmpNode;
        }
        newDelete(minT2);
        minT2 = tmpNode;
        T2 = findRoot(T2);
    }

    if (isOneNode(T0)) {
        assert(T0->nodeId == v);
        maxT0 = T0;
        first[v] = maxT0;
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
        maxT0 = maximum(T0);
        auto tmpNode = new ETTreeNode(nullptr, &theNullNode, &theNullNode, maxT0->color, maxT0->nodeId);
        tmpNode->rank = maxT0->rank;
        if (maxT0 == first[v]) {
            first[v] = tmpNode;
        }
        newDelete(maxT0);
        maxT0 = tmpNode;
        T0 = findRoot(T0);
    }
    T4 = join(T0, vNode, T2);

    T3 = findRoot(T3);
    auto minT3 = minimum(T3);
    auto maxT3 = maximum(T3);
    assert(minT3->nodeId == u);
    assert(maxT3->nodeId == u);
    first[u] = minT3;
    last[u] = maxT3;
    if (isOneNode(T4)) {
        first[v] = last[v] = vNode;
    }
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
    if (it > this->logN) {
        ETTreeNode *T1, *T2, *T3, *T4;
        std::pair<ETTreeNode *, ETTreeNode *> tmp = split(first[u]);
        T1 = tmp.first;
        T2 = tmp.second;

        if (isOneNode(T2)) {
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

        if (isOneNode(T1)) {
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
            w = minimum(T1);
            newDelete(w);
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
            if (isOneNode(T2)) {
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

            ETTreeNode *w;
            if (isOneNode(T1)) {
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
                w = minimum(T1);
                newDelete(w);
                w = setBackToOneNode(w);
                T1 = findRoot(T1);
            }

            T3 = join(T2, w, T1);

            uLast = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, u);
            ETTreeNode *uLastSeen = last[u];
            ETTreeNode *uSucc = successor(uLastSeen);


            T4 = join(T3, uLast, &theNullNode);

            ETTreeNode *uLastPred = predecessor(uLast);

            if (uSucc != nullptr) {
                int uParent = uSucc->nodeId;
                first[uParent] = uSucc;
                last[uParent] = uLastPred;
            }

            last[u] = uLast;
        }
    }
}


void ETForest::newDelete(ETTreeNode *n) {
    ETTreeNode *child;
    ETTreeNode *originalNode = nullptr;
    ETTreeNode *originalNodeParent = nullptr;
    ETTreeNode *originalNodeLChild = nullptr;
    ETTreeNode *originalNodeRChild = nullptr;
    int originalNodeColor;
    int originalNodeRank;
    bool originalIsLeft;
    ETTreeNode *nodeToDelete = nullptr;
    ETTreeNode *nodeToDeleteParent = nullptr;
    ETTreeNode *nodeToDeleteLChild = nullptr;
    ETTreeNode *nodeToDeleteRChild = nullptr;
    int nodeToDeleteColor;
    int nodeToDeleteRank;
    bool nodeToDeleteIsLeft;
    if (n == &theNullNode) {
        return;
    }

    if (n->left != &theNullNode && n->right != &theNullNode) {

        ETTreeNode *pred = maximum(n->left);
        //n->nodeId = pred->nodeId;
        originalNode = n;
        originalNodeParent = n->parent;
        originalNodeLChild = n->left;
        originalNodeRChild = n->right;
        originalNodeColor = n->color;
        originalNodeRank = n->rank;
        originalIsLeft = isLeft(n);

        nodeToDelete = pred;
        nodeToDeleteParent = pred->parent;
        nodeToDeleteLChild = pred->left;
        nodeToDeleteRChild = pred->right;
        nodeToDeleteColor = pred->color;
        nodeToDeleteRank = pred->rank;
        nodeToDeleteIsLeft = isLeft(pred);
        //kössük be az eredeti node helyére a törlendőt
        if (originalIsLeft) {
            setLeftChild(originalNodeParent, nodeToDelete);

        } else {
            setRightChild(originalNodeParent, nodeToDelete);
        }

        if (pred->parent != originalNode) {
            setLeftChild(nodeToDelete, originalNodeLChild);
            setRightChild(nodeToDelete, originalNodeRChild);
            setParent(originalNodeLChild, nodeToDelete);
            setParent(originalNodeRChild, nodeToDelete);
        } else if (nodeToDeleteIsLeft) {
            setLeftChild(nodeToDelete, originalNode);
            setRightChild(nodeToDelete, originalNodeRChild);
            setParent(originalNode, nodeToDelete);
            setParent(originalNodeRChild, nodeToDelete);
        } else {
            setLeftChild(nodeToDelete, originalNodeLChild);
            setRightChild(nodeToDelete, originalNode);
            setParent(originalNodeLChild, nodeToDelete);
            setParent(originalNode, nodeToDelete);
        }
        setParent(nodeToDelete, originalNodeParent);


        setColor(nodeToDelete, originalNodeColor);
        setRank(nodeToDelete, originalNodeRank);

        //itt pedig az eredetileg törlésre kijelölt node-ot fogjuk a predecessor helyére bekötni, így valóban őt töröljük ki végül
        if (nodeToDeleteIsLeft) {
            setLeftChild(nodeToDeleteParent, originalNode);
        } else {
            setRightChild(nodeToDeleteParent, originalNode);
        }
        if (originalNode->parent != nodeToDelete) {
            setParent(originalNode, nodeToDeleteParent);
        }

        setLeftChild(originalNode, nodeToDeleteLChild);
        setRightChild(originalNode, nodeToDeleteRChild);
        setParent(nodeToDeleteLChild, originalNode);
        setParent(nodeToDeleteRChild, originalNode);
        setColor(originalNode, nodeToDeleteColor);
        setRank(originalNode, nodeToDeleteRank);


        n = originalNode;
    }

    assert(n->left == &theNullNode || n->right == &theNullNode);

    child = n->right == &theNullNode ? n->left : n->right;

    if (n->color == BLACK) {

//        n->color = child->color;
        setColorWithRankUpdate(n, child->color);
        deleteCase1(n);

    }

    replaceNode(n, child);
    //rankupdate mivel lehet, hogy valamelyik forgatás rosszul állítja be a rankokat
    if (child != &theNullNode) {
        updateRank(child);
    } else {
        updateRank(n->parent);
    }
    setBackToOneNode(n);
    n = nullptr;
    return;
}

void ETForest::deleteCase1(ETTreeNode *n) {
    if (n->parent == &theNullNode || n->parent == nullptr)

        return;

    else

        deleteCase2(n);
}

void ETForest::deleteCase2(ETTreeNode *n) {
    if (sibling(n)->color == RED) {

        setColorWithRankUpdate(n->parent, RED);
        setColorWithRankUpdate(sibling(n), BLACK);

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


        setColorWithRankUpdate(sibling(n), RED);

        deleteCase1(n->parent);

    } else

        deleteCase4(n);
}

void ETForest::deleteCase4(ETTreeNode *n) {
    if (n->parent->color == RED && sibling(n)->color == BLACK &&

        sibling(n)->left->color == BLACK && sibling(n)->right->color == BLACK) {


        setColorWithRankUpdate(sibling(n), RED);
        setColorWithRankUpdate(n->parent, BLACK);

    } else

        deleteCase5(n);
}

void ETForest::deleteCase5(ETTreeNode *n) {
    if (n == n->parent->left && sibling(n)->color == BLACK &&

        sibling(n)->left->color == RED && sibling(n)->right->color == BLACK) {



        setColorWithRankUpdate(sibling(n), RED);
        setColorWithRankUpdate(sibling(n)->left, BLACK);

        rotateRight(sibling(n));

    } else if (n == n->parent->right && sibling(n)->color == BLACK &&

               sibling(n)->right->color == RED && sibling(n)->left->color == BLACK) {


        setColorWithRankUpdate(sibling(n), RED);
        setColorWithRankUpdate(sibling(n)->right, BLACK);

        rotateLeft(sibling(n));

    }

    deleteCase6(n);
}

void ETForest::deleteCase6(ETTreeNode *n) {

    setColorWithRankUpdate(sibling(n), n->parent->color);
    setColorWithRankUpdate(n->parent, BLACK);

    if (n == n->parent->left) {
        ETTreeNode *siblingRChild = sibling(n)->right;
        assert (siblingRChild->color == RED);
        siblingRChild->color = BLACK;
        rotateLeft(n->parent);
        updateRank(siblingRChild);

    } else {
        ETTreeNode *siblingLChild = sibling(n)->left;
        assert (siblingLChild->color == RED);
        siblingLChild->color = BLACK;
        rotateRight(n->parent);
        updateRank(siblingLChild);
    }
}

void ETForest::replaceNode(ETTreeNode *oldn, ETTreeNode *newn) {

    if (oldn->parent == nullptr) {
        newn->parent = nullptr;
        setColorWithRankUpdate(newn, BLACK);

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

bool ETForest::verifyProperties(ETTreeNode *pNode) {
    bool isValid = true;

    verifyColor(findRoot(pNode), isValid);

    verifyRootColor(findRoot(pNode), isValid);

    verifyRedNodeParentAndChildrenColors(findRoot(pNode), isValid);

    verifyBlackRank(findRoot(pNode), isValid);

    verifyRankNumber(findRoot(pNode), isValid);

    return isValid;
}

void ETForest::verifyColor(ETTreeNode *pNode, bool &isValid) {
    if (pNode == nullptr) {
        return;
    }
    assert (pNode->color == RED || pNode->color == BLACK);
    if (pNode->color != RED && pNode->color != BLACK) {
        isValid = false;
    }

    verifyColor(pNode->left, isValid);
    verifyColor(pNode->right, isValid);
}

void ETForest::verifyRootColor(ETTreeNode *root, bool &isValid) {
    assert (root->color == BLACK);
    if (root->color != BLACK) {
        isValid = false;
    }
}

void ETForest::verifyRedNodeParentAndChildrenColors(ETTreeNode *pNode, bool &isValid) {

    if (pNode == nullptr) {
        return;
    }

    if (pNode->color == RED) {
        assert (pNode->left->color == BLACK);
        assert (pNode->right->color == BLACK);
        assert (pNode->parent != nullptr);
        assert (pNode->parent->color == BLACK);
        if (pNode->left->color != BLACK || pNode->right->color != BLACK ||
            (pNode->parent != nullptr && pNode->parent->color != BLACK)) {
            isValid = false;
        }
    }

    verifyRedNodeParentAndChildrenColors(pNode->left, isValid);
    verifyRedNodeParentAndChildrenColors(pNode->right, isValid);
}

void ETForest::verifyBlackRank(ETTreeNode *pNode, bool &isValid) {
    int black_count_path = -1;

    verifyBlackRankHelper(pNode, 0, &black_count_path, isValid);
}

void ETForest::verifyBlackRankHelper(ETTreeNode *pNode, int black_count, int *path_black_count, bool &isValid) {

    if (pNode == nullptr) {
        if (*path_black_count == -1) {
            *path_black_count = black_count;
        } else {
            assert (black_count == *path_black_count);
            if (black_count != *path_black_count) {
                isValid = false;
            }
        }
        return;
    }
    if (pNode->color == BLACK) {
        black_count++;
    }


    verifyBlackRankHelper(pNode->left, black_count, path_black_count, isValid);
    verifyBlackRankHelper(pNode->right, black_count, path_black_count, isValid);
}


void ETForest::verifyRankNumber(ETTreeNode *pNode, bool &isValid) {
    if (pNode == nullptr || pNode == &theNullNode) {
        return;
    }
    if (pNode->left != &theNullNode) {
        verifyRankNumber(pNode->left, isValid);
    }
    if (pNode->right != &theNullNode) {
        verifyRankNumber(pNode->right, isValid);
    }
    verifyRankNumberHelper(pNode, isValid);
}


void ETForest::verifyRankNumberHelper(ETTreeNode *pNode, bool &isValid) {
    if (pNode == nullptr) {
        return;
    }
    if (pNode->color == BLACK) {
        if (pNode->rank != pNode->left->rank + 1) {
            isValid = false;
        }
        assert(pNode->rank == pNode->left->rank + 1);
    } else {
        if (pNode->rank != pNode->left->rank) {
            isValid = false;
        }
        assert(pNode->rank == pNode->left->rank);

    }
    verifyRankNumberHelper(pNode->parent, isValid);

}

void ETForest::verifyFirstLast() {
    ETTreeNode *pNode;
    ETTreeNode *firstSeen = nullptr;
    ETTreeNode *lastSeen = nullptr;
    for (int i = 0; i < this->N; ++i) {
        pNode = this->first[i];
        assert(i == pNode->nodeId);
        pNode = findRoot(pNode);
        auto lastPNode = this->last[i];
        lastPNode = findRoot(lastPNode);
        assert(pNode == lastPNode);
        firstLastHelper(pNode, i, firstSeen, lastSeen);
        assert(firstSeen == first[i]);
        assert(lastSeen == last[i]);
        firstSeen = nullptr;
        lastSeen = nullptr;
    }
}

void ETForest::firstLastHelper(ETTreeNode *pNode, const int &id, ETTreeNode *&firstSeen, ETTreeNode *&lastSeen) {
    if (pNode != nullptr && pNode != &theNullNode && pNode->left != &theNullNode) {
        firstLastHelper(pNode->left, id, firstSeen, lastSeen);
    }
    if (pNode != nullptr && pNode->nodeId == id) {
        if (firstSeen == nullptr) {
            firstSeen = pNode;
        }
        lastSeen = pNode;
    }

    if (pNode != nullptr && pNode != &theNullNode && pNode->right != &theNullNode) {
        firstLastHelper(pNode->right, id, firstSeen, lastSeen);
    }
}


void ETForest::print(ETTreeNode *pNode) {
    print(pNode, 0);
}

void ETForest::print(ETTreeNode *pNode, int indent) {
    if (pNode != &theNullNode) {
        print(pNode->right, indent + 1);
        for (int i = 0; i < indent; i++) {
            std::cout << "    ";
        }
        std::cout << ((pNode->color == BLACK) ? "b[" : "r[") << pNode->nodeId << "]" << std::endl;
        print(pNode->left, indent + 1);
    }
}



void ETForest::verifyNodesAreTwoSideConnected(ETTreeNode *pNode) {
    if (pNode != nullptr && pNode != &theNullNode && pNode->left != &theNullNode) {
        assert(pNode == pNode->left->parent);
        verifyNodesAreTwoSideConnected(pNode->left);
    }
    if (pNode != nullptr && pNode != &theNullNode && pNode->right != &theNullNode) {
        assert(pNode == pNode->right->parent);
        verifyNodesAreTwoSideConnected(pNode->right);
    }

}

void ETForest::verify2SideConnection() {
    for (int i = 0; i < this->N; ++i) {
        verifyNodesAreTwoSideConnected(findRoot(first[i]));
    }
}


std::pair<ETTreeNode *, ETTreeNode *> ETForest::splitInRemove(ETTreeNode *pNode) {
    //saveljük el a parentjét és, hogy jobb vagy bal gyerek-e
    ETTreeNode *parent = pNode->parent;
    ETTreeNode *T1;
    bool isLeftNode = isLeft(pNode);
    //T1 létrehozása, ő a pNode bal gyereke
    if (pNode->left == &theNullNode) {
        T1 = &theNullNode;
    } else {
        auto pLeft = pNode->left;
        T1 = new ETTreeNode(nullptr, pNode->left->left, pNode->left->right, pNode->left->color,
                            pNode->left->nodeId);
        T1->rank = pNode->left->rank;
        setParent(T1->left, T1);
        setParent(T1->right, T1);
        if (first[pLeft->nodeId] == pLeft) {
            first[pLeft->nodeId] = T1;
        }
        if (last[pLeft->nodeId] == pLeft) {
            last[pLeft->nodeId] = T1;
        }
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
    if (pNodeRight->color == RED) {
        pNodeRight->color = BLACK;
        ++pNodeRight->rank;
    }
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