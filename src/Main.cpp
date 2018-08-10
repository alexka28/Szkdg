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

    ETTreeNode *a1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 1);
    ETTreeNode *a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 2);
    ETTreeNode *a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;


    ETTreeNode *b1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 1);
    ETTreeNode *b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 2);
    ETTreeNode *b3 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 3);

    b1->left = b2;
    b1->right = b3;

    b2->rank = 0;
    b3->rank = 0;


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


    if (TestETT::compare(TestETT::findRootForTest(a2), b1) == 0) {
        cout << "ket fa egyenlo" << endl;
    } else {
        cout << "ket fa kulonbozo" << endl;
    }
    return 0;
}
