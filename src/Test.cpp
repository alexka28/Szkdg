#include "Test.h"
#include <iostream>
#include "UniFind.h"
#include <time.h>
#include <stdlib.h>
#include "CreateInsertQuery.h"
#include "GraphGen.h"
#include <ctime>
#include "TraditionalAlgorithm.h"
#include "IncrementalAlgorithm.h"
#include "ETT.h"
#include "DecrementalGraph.h"
#include "CreateDeleteQuery.h"
#include "DFS.h"
#include <cassert>

void testInsert() {
    bool *ret;
    ret = (bool *) malloc(sizeof(bool));
    *ret = false;
    srand(time(NULL));
    int n = 100;
    std::list<std::list<struct IQ> > smNodes;
    /*
    Creating 50 iqList to graphs with 100 nodes
    */
    std::cout << "Creating insert and query lists." << std::endl;
    int maxinserts = (n * (n - 1)) / 2;
    int max = maxinserts * 0.9;
    int min = maxinserts * 0.7;
    int finalNum = rand() % (max - min + 1) + min;
    for (int i = 0; i < 50; ++i) {
        smNodes.push_back(createIQ(n, finalNum));
    }
    std::cout << "List created!" << std::endl;
    std::cout << "Running incremental and traditional algorithms." << std::endl;

    std::clock_t startInc;
    std::clock_t startTrad;
    long double endInc = 0;
    long double endTrad = 0;

    std::list<std::list<struct IQ> >::iterator outerIt;
    for (outerIt = smNodes.begin(); outerIt != smNodes.end(); ++outerIt) {
        std::list<struct IQ> innerList = *outerIt;
        Graph inc(n + 1);
        Graph trad(n + 1);
        DisjointSets d(n);

        startInc = std::clock();
        incrementalAlgorithm(d, inc, innerList);
        endInc += (std::clock() - startInc) / (long double) CLOCKS_PER_SEC;
        startTrad = std::clock();
        traditionalAlgorithm(trad, innerList, ret);
        endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
    }
    std::cout << "Both algorithms ended!" << std::endl;
    std::cout << "Incremental running time: " << endInc << " sec." << std::endl;
    std::cout << "Traditional running time: " << endTrad << " sec." << std::endl;
    std::cout << "Program finished!";


    free(ret);

}

void testDelete(const int& numberOfNodes, const int& numberOfTests) {
    int n = numberOfNodes;
    std::clock_t startDec;
    std::clock_t startTrad;
    long double endDec = 0;
    long double endTrad = 0;
    for (int i = 1; i <= numberOfTests; ++i) {
        DecGraph decGraph(n);
        ETForest forest(n);
        Graph graph(n);
        std::list<std::pair<int, int>> insertList = fillGraph(n);
        std::list<std::pair<int, int>>::iterator insertIt;

        std::cout << "Teszt: " << i << std::endl;
        for (insertIt = insertList.begin(); insertIt != insertList.end(); ++insertIt) {
            decGraph.insert(insertIt->first, insertIt->second, forest);
            graph.addEdge(insertIt->first, insertIt->second);
        }


        auto delquer = createDQ(insertList, n);

        for (auto queryIt = delquer.begin(); queryIt != delquer.end(); ++queryIt) {
            if (queryIt->second == 0) {
                startDec = std::clock();
                decGraph.remove(queryIt->first.first, queryIt->first.second, forest);
                endDec += (std::clock() - startDec) / (long double) CLOCKS_PER_SEC;

                startTrad = std::clock();
                graph.deleteEdge(queryIt->first.first, queryIt->first.second);
                endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
            } else {
                bool ret = false;
                startDec = std::clock();
                decGraph.connected(queryIt->first.first, queryIt->first.second, forest);
                endDec += (std::clock() - startDec) / (long double) CLOCKS_PER_SEC;

                startTrad = std::clock();
                queryGraph(graph, queryIt->first.first, queryIt->first.second, &ret);
                endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;

            }
        }
    }
    std::cout << "dekremental ossz : " << endDec << std::endl;
    std::cout << "hagyomanyos ossz: " << endTrad << std::endl;
    std::cout << "dekremental atlag: " << endDec / numberOfTests << std::endl;
    std::cout << "hagyomanyos atlag: " << endTrad / numberOfTests << std::endl;

}

void testDeleteWithVerify(const int& numberOfNodes, const int& numberOfTests) {
    int n = numberOfNodes;
    std::clock_t startDec;
    std::clock_t startTrad;
    long double endDec = 0;
    long double endTrad = 0;
    for (int i = 1; i <= numberOfTests; ++i) {
        DecGraph decGraph(n);
        ETForest forest(n);
        Graph graph(n);
        std::list<std::pair<int, int>> insertList = fillGraph(n);
        std::list<std::pair<int, int>>::iterator insertIt;

        std::cout << "Teszt: " << i << std::endl;
        for (insertIt = insertList.begin(); insertIt != insertList.end(); ++insertIt) {
//        cout<<" testInsertEdge(" << insertIt->first<<"," << insertIt->second<<",decGraph,forest);" <<endl;
            decGraph.insert(insertIt->first, insertIt->second, forest);
            graph.addEdge(insertIt->first, insertIt->second);
            bool ret = false;
            assert(queryGraph(graph, insertIt->first, insertIt->second, &ret));
            forest.verifyFirstLast();
            assert(forest.verifyProperties(forest.findRoot(insertIt->first)));
            assert(forest.verifyProperties(forest.findRoot(insertIt->second)));
            assert(decGraph.connected(insertIt->first, insertIt->second, forest));
        }


        auto delquer = createDQ(insertList, n);

        for (auto queryIt = delquer.begin(); queryIt != delquer.end(); ++queryIt) {
            if (queryIt->second == 0) {
//            cout<<"torles :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
                startDec = std::clock();
                decGraph.remove(queryIt->first.first, queryIt->first.second, forest);
                endDec += (std::clock() - startDec) / (long double) CLOCKS_PER_SEC;
                forest.verifyProperties(forest.findRoot(queryIt->first.first));
                forest.verifyProperties(forest.findRoot(queryIt->first.second));
                forest.verifyFirstLast();
                startTrad = std::clock();
                graph.deleteEdge(queryIt->first.first, queryIt->first.second);
                endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
                auto isConnected = decGraph.connected(queryIt->first.first, queryIt->first.second, forest);
                bool ret = false;
                assert(queryGraph(graph, queryIt->first.first, queryIt->first.second, &ret) == isConnected);
            } else {
                bool ret = false;
                startDec = std::clock();
                auto isConnected = decGraph.connected(queryIt->first.first, queryIt->first.second, forest);
                endDec += (std::clock() - startDec) / (long double) CLOCKS_PER_SEC;
                startTrad = std::clock();
                auto dfsResult = queryGraph(graph, queryIt->first.first, queryIt->first.second, &ret);
                assert(dfsResult == isConnected);
                endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
//            cout<<"query :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
            }
        }
    }
    std::cout << "dekremental ossz : " << endDec << std::endl;
    std::cout << "hagyomanyos ossz: " << endTrad << std::endl;
    std::cout << "dekremental atlag: " << endDec / numberOfTests << std::endl;
    std::cout << "hagyomanyos atlag: " << endTrad / numberOfTests << std::endl;

}