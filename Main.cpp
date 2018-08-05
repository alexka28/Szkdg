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
    ETTreeNode *theNull = new ETTreeNode(nullptr, nullptr, nullptr, 0, 0);
    ETTreeNode *a1 = new ETTreeNode(nullptr, nullptr, nullptr, 0, 1);
    ETTreeNode *a2 = new ETTreeNode(nullptr, nullptr, nullptr, 1, 2);
    ETTreeNode *a3 = new ETTreeNode(nullptr, nullptr, nullptr, 1, 3);

    a1->left = a2;
    a1->right = a3;
    a1->rank = 1;

    a2->parent = a1;
    a2->rank = 0;
    a2->left = theNull;
    a2->right = theNull;
    a3->parent = a1;
    a3->rank = 0;
    a3->left = theNull;
    a3->right = theNull;

    ETTreeNode *b1 = new ETTreeNode(nullptr, nullptr, nullptr, 0, 1);
    ETTreeNode *b2 = new ETTreeNode(nullptr, nullptr, nullptr, 1, 2);
    ETTreeNode *b3 = new ETTreeNode(nullptr, nullptr, nullptr, 1, 3);

    b1->left = b2;
    b1->right = b3;
    b1->rank = 1;


    b2->parent = b1;
    b2->rank = 0;
    b2->left = theNull;
    b2->right = theNull;
    b3->parent = b1;
    b3->rank = 0;
    b3->left = theNull;
    b3->right = theNull;


    if (TestETT::compare(TestETT::findRootForTest(a2), b1) == 0) {
        cout << "ket fa egyenlo" << endl;
    } else {
        cout << "ket fa kulonbozo" << endl;
    }


    return 0;
}
