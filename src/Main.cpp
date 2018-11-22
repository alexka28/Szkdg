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
int n = 100;
    std::clock_t startDec;
    std::clock_t startTrad;
    long double endDec = 0;
    long double endTrad = 0;
for(int i = 1; i <= 5; ++i){
    DecGraph grafom(n);
    ETForest forestem(n);
    Graph simagraf(n);
    std::list<std::pair<int,int>> insertList = fillGraph(n);
    std::list<std::pair<int,int>>::iterator insertIt;
//    std::cout<<"lista kesz!"<<std::endl;
    std::cout<<"Teszt: "<< i << std::endl;
    for(insertIt = insertList.begin(); insertIt != insertList.end(); ++insertIt){
//        cout<<" testInsertEdge(" << insertIt->first<<"," << insertIt->second<<",graph,forest);" <<endl;
        grafom.insert(insertIt->first,insertIt->second,forestem);
        simagraf.addEdge(insertIt->first,insertIt->second);
//        bool ret = false;
//        assert(queryGraph(simagraf,insertIt->first, insertIt->second, &ret));
//        assert(ret);
//        forestem.verifyFirstLast();
//        assert(forestem.verifyProperties(forestem.findRoot(insertIt->first)));
//        assert(forestem.verifyProperties(forestem.findRoot(insertIt->second)));
//        assert(grafom.connected(insertIt->first, insertIt->second, forestem));
    }




    auto delquer = createDQ(insertList,n);

    for(auto queryIt = delquer.begin(); queryIt != delquer.end(); ++queryIt){
        if(queryIt->second == 0){
//            cout<<"torles :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
            startDec = std::clock();
            grafom.remove(queryIt->first.first, queryIt->first.second, forestem);
            endDec += ( std::clock() - startDec ) / (long double) CLOCKS_PER_SEC;
//            forestem.verifyProperties(forestem.findRoot(queryIt->first.first));
//            forestem.verifyProperties(forestem.findRoot(queryIt->first.second));
//            forestem.verifyFirstLast();
            startTrad = std::clock();
            simagraf.deleteEdge(queryIt->first.first, queryIt->first.second);
            endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
//            auto asd = grafom.connected(queryIt->first.first, queryIt->first.second, forestem);
//            bool ret = false;
//            assert(queryGraph(simagraf, queryIt->first.first, queryIt->first.second, &ret) == asd);
        }
        else{
            bool ret = false;
            startDec = std::clock();
            auto asd = grafom.connected(queryIt->first.first, queryIt->first.second, forestem);
            endDec += ( std::clock() - startDec ) / (long double) CLOCKS_PER_SEC;
            startTrad = std::clock();
            queryGraph(simagraf, queryIt->first.first, queryIt->first.second, &ret);
            // assert(queryGraph(simagraf, queryIt->first.first, queryIt->first.second, &ret) == asd);
            endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
//            cout<<"query :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
        }
    }
}
    std::cout <<"dekremental ossz : "<<endDec<<std::endl;
    std::cout<<"hagyomanyos ossz: " <<endTrad<<std::endl;
    std::cout <<"dekremental atlag: "<<endDec/5<<std::endl;
    std::cout<<"hagyomanyos atlag: " <<endTrad/5<<std::endl;

    return 0;
}
