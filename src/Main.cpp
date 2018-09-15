#include <iostream>
#include "DecrementalGraph.h"
#include<set>
#include "Test.h"
#include <utility>
#include "ETT.h"
#include "CreateDeleteQuery.h"
#include "GraphGen.h"
#include "DFS.h"
#include <list>
#include "TestETT.h"
#include <cassert>
#include <cmath>
#include "ETTQueries.h"

using namespace std;

int main() {

    //insertekhez a teszt
    // testInsert();

//    DecGraph grafom(10);
//    ETForest forestem(10);
//    Graph simagraf(10);
//std::list<std::pair<int,int>> insertList = fillGraph(10);
//    std::list<std::pair<int,int>>::iterator insertIt;
//    for(insertIt = insertList.begin(); insertIt != insertList.end(); ++insertIt){
//        cout<<"elso node: " << insertIt->first<<" masodik node: " << insertIt->second<<endl;
//        grafom.insert(insertIt->first,insertIt->second,forestem);
//        simagraf.addEdge(insertIt->first,insertIt->second);
//    }
//    std::list<std::pair<std::pair<int, int>, int>> delquer = createDQ(insertList,10);
//    std::list<std::pair<std::pair<int, int>, int>>:: iterator queryIt;
//    for(queryIt = delquer.begin(); queryIt != delquer.end(); ++queryIt){
//        if(queryIt->second == 0){
//            cout<<"torles :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
//        }
//        else{
//            cout<<"query :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
//        }
//    }

//    ETTreeNode *a1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 10); //10
//    ETTreeNode *a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, BLACK, 8); //8
//    ETTreeNode *a3 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 6); //6
//    ETTreeNode *a4 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 9); //9
//    ETTreeNode *a5 = new ETTreeNode(a1, &theNullNode, &theNullNode, BLACK, 15); // 15
//    ETTreeNode *a6 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 12); // 12
//    ETTreeNode *a7 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 18); // 18
//
//    a1->left = a2;
//    a1->right = a5;
//    a1->rank = 2;
//
//    a2->left =a3;
//    a2->right = a4;
//    a2->rank = 1;
//
//    a3->parent = a2;
//    a3->rank = 0;
//
//    a4->parent = a2;
//    a4->rank = 0;
//
//    a5->left = a6;
//    a5->right = a7;
//    a5->rank = 1;
//
//    a6->parent = a5;
//    a6->rank = 0;
//
//    a7->parent = a5;
//    a7->rank = 0;
//    //Expected output
//    ETTreeNode *b1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 10); //10
//    ETTreeNode *b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, BLACK, 8); //8
//    ETTreeNode *b3 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 6); //6
//    ETTreeNode *b4 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 9); //9
//    ETTreeNode *b5 = new ETTreeNode(b1, &theNullNode, &theNullNode, BLACK, 15); // 15
//    ETTreeNode *b6 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 12); // 12
//    ETTreeNode *b7 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 18); // 18
//
//    b1->left = b2;
//    b1->right = b5;
//    b1->rank = 2;
//
//    b2->left =b3;
//    b2->right = b4;
//    b2->rank = 1;
//
//    b3->parent = b2;
//    b3->rank = 0;
//
//    b4->parent = b2;
//    b4->rank = 0;
//
//    b5->left = b6;
//    b5->right = b7;
//    b5->rank = 1;
//
//    b6->parent = b5;
//    b6->rank = 0;
//
//    b7->parent = b5;
//    b7->rank = 0;
//    ETForest::newDelete(a3);
//    b2->left = &theNullNode;
//    cout<<"elso fa inorderje:"<<endl;
//    ETForest::inOrder(ETForest::findRoot(a1));
//    cout<<"masodik fa inorderje:"<<endl;
//    ETForest::inOrder(ETForest::findRoot(b1));
//    ETForest::newDelete(a2);
//    b1->left = b4;
//    b4->parent = b1;
//    b4->color = BLACK;
//    b4->rank = 1;
//    cout<<"elso fa inorderje:"<<endl;
//    ETForest::inOrder(ETForest::findRoot(a1));
//    cout<<"masodik fa inorderje:"<<endl;
//    ETForest::inOrder(ETForest::findRoot(b1));
    DecGraph graph(10);
    ETForest forest(10);


    graph.insert(3, 4, forest);

    graph.insert(3, 7, forest);


    graph.insert(6, 4, forest);


    graph.insert(1, 0, forest);
    inOrder(forest.findRoot(3));
//    cout << graph.connected(3,4, forest) <<endl;
//
//    cout << graph.connected(7,3, forest) <<endl;
//
//    cout << graph.connected(6,4, forest) <<endl;
//
//    cout << graph.connected(3,6, forest) <<endl;
//
//    cout << graph.connected(6,7, forest) <<endl;
//
//    cout << graph.connected(4,7, forest) <<endl;
    graph.insert(8, 6, forest);

    cout << endl << graph.connected(3, 4, forest) << endl;

    cout << graph.connected(7, 3, forest) << endl;

    cout << graph.connected(6, 4, forest) << endl;

    cout << graph.connected(3, 6, forest) << endl;

    cout << graph.connected(6, 7, forest) << endl;

    cout << graph.connected(4, 7, forest) << endl;
    cout << graph.connected(7, 8, forest) << endl;
    inOrder(forest.findRoot(3));
    /**************************************************************************************************
     **                                             TESTDATA                                         **
     **************************************************************************************************

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
     ************************************************************************************************************/



    return 0;
}
