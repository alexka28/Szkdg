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

    DecGraph grafom(10);
    ETForest forestem(10);
    Graph simagraf(10);
std::list<std::pair<int,int>> insertList = fillGraph(10);
    std::list<std::pair<int,int>>::iterator insertIt;
    for(insertIt = insertList.begin(); insertIt != insertList.end(); ++insertIt){
        cout<<"elso node: " << insertIt->first<<" masodik node: " << insertIt->second<<endl;
        grafom.insert(insertIt->first,insertIt->second,forestem);
        simagraf.addEdge(insertIt->first,insertIt->second);
        bool ret = false;
        assert(queryGraph(simagraf,insertIt->first, insertIt->second, &ret));
        ret = false;
        queryGraph(simagraf,insertIt->first, insertIt->second, &ret);
        assert(ret);
        forestem.verifyFirstLast();
        assert(forestem.verifyProperties(forestem.findRoot(insertIt->first)));
        assert(grafom.connected(insertIt->first, insertIt->second, forestem));
    }




    std::list<std::pair<std::pair<int, int>, int>> delquer = createDQ(insertList,10);
    std::list<std::pair<std::pair<int, int>, int>>:: iterator queryIt;
    for(queryIt = delquer.begin(); queryIt != delquer.end(); ++queryIt){
        if(queryIt->second == 0){
            cout<<"torles :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
            grafom.remove(queryIt->first.first, queryIt->first.second, forestem);
            forestem.verifyProperties(forestem.findRoot(queryIt->first.first));
            forestem.verifyProperties(forestem.findRoot(queryIt->first.second));
            forestem.verifyFirstLast();
            simagraf.deleteEdge(queryIt->first.first, queryIt->first.second);

        }
        else{
           bool ret = false;
            auto asd = grafom.connected(queryIt->first.first, queryIt->first.second, forestem);
            assert(queryGraph(simagraf, queryIt->first.first, queryIt->first.second, &ret) == asd);
            cout<<"query :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
        }
    }



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
        n2->rank = 1;
        n3->parent = n1;
        n3->left = n6;
        n3->right = n7;
        n3->rank = 1;
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
        n8->rank = 0;
        ETForest::verifyProperties(n1);
     ************************************************************************************************************/



    return 0;
}
