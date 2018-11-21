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
#include <ctime>
using namespace std;

int main() {

    //insertekhez a teszt
    // testInsert();
int n = 50;
    DecGraph grafom(n);
    ETForest forestem(n);
    Graph simagraf(n);
std::list<std::pair<int,int>> insertList = fillGraph(n);
    std::list<std::pair<int,int>>::iterator insertIt;
    std::cout<<"lista kesz!"<<std::endl;
    for(insertIt = insertList.begin(); insertIt != insertList.end(); ++insertIt){
        cout<<" testInsertEdge(" << insertIt->first<<"," << insertIt->second<<",graph,forest);" <<endl;
        grafom.insert(insertIt->first,insertIt->second,forestem);
        simagraf.addEdge(insertIt->first,insertIt->second);
        bool ret = false;
        assert(queryGraph(simagraf,insertIt->first, insertIt->second, &ret));
        assert(ret);
        forestem.verifyFirstLast();
        assert(forestem.verifyProperties(forestem.findRoot(insertIt->first)));
        assert(forestem.verifyProperties(forestem.findRoot(insertIt->second)));
        assert(grafom.connected(insertIt->first, insertIt->second, forestem));
    }




    auto delquer = createDQ(insertList,n);
    std::clock_t startDec;
    std::clock_t startTrad;
    long double endDec = 0;
    long double endTrad = 0;
    for(auto queryIt = delquer.begin(); queryIt != delquer.end(); ++queryIt){
        if(queryIt->second == 0){
            cout<<"torles :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
            startDec = std::clock();
            grafom.remove(queryIt->first.first, queryIt->first.second, forestem);
            endDec += ( std::clock() - startDec ) / (long double) CLOCKS_PER_SEC;
            forestem.verifyProperties(forestem.findRoot(queryIt->first.first));
            forestem.verifyProperties(forestem.findRoot(queryIt->first.second));
            forestem.verifyFirstLast();
            startTrad = std::clock();
            simagraf.deleteEdge(queryIt->first.first, queryIt->first.second);
            endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
            auto asd = grafom.connected(queryIt->first.first, queryIt->first.second, forestem);
            bool ret = false;
            assert(queryGraph(simagraf, queryIt->first.first, queryIt->first.second, &ret) == asd);
        }
        else{
           bool ret = false;
            startDec = std::clock();
            auto asd = grafom.connected(queryIt->first.first, queryIt->first.second, forestem);
            endDec += ( std::clock() - startDec ) / (long double) CLOCKS_PER_SEC;
            startTrad = std::clock();
            assert(queryGraph(simagraf, queryIt->first.first, queryIt->first.second, &ret) == asd);
            endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
            cout<<"query :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
        }
    }
    std::cout <<"dekremental : "<<endDec<<std::endl;
    std::cout<<"hagyomanyos: " <<endTrad<<std::endl;



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
