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
void testInsert(){
bool *ret;
    ret = (bool*)malloc(sizeof(bool));
    *ret = false;
    srand (time(NULL));
    int n= 100;
    std::list<std::list<struct IQ> > smNodes;
    /*
    Creating 50 iqList to graphs with 100 nodes
    */
    std::cout<<"Creating insert and query lists."<<std::endl;
    int maxinserts = (n*(n-1))/2;
    int max = maxinserts * 0.9;
    int min = maxinserts * 0.7;
    int finalNum = rand()%(max-min+1)+min;
    for(int i = 0; i < 2; ++i)
    {
        smNodes.push_back(createIQ(n, finalNum));
    }
    std::cout<<"List created!"<<std::endl;
    std::cout<<"Running incremental and traditional algorithms."<<std::endl;

    std::clock_t startInc;
    std::clock_t startTrad;
    long double endInc = 0;
    long double endTrad = 0;

    std::list<std::list<struct IQ> >::iterator outerIt;
    for(outerIt = smNodes.begin(); outerIt != smNodes.end(); ++outerIt )
    {
        std::list<struct IQ> innerList = *outerIt;
        Graph inc(n+1);
        Graph trad(n+1);
        DisjointSets d(n);

        startInc = std::clock();
        incrementalAlgorithm(d, inc, innerList);
        endInc += ( std::clock() - startInc ) / (long double) CLOCKS_PER_SEC;
        startTrad = std::clock();
        traditionalAlgorithm(trad, innerList, ret);
        endTrad += (std::clock() - startTrad) / (long double) CLOCKS_PER_SEC;
    }
    std::cout<<"Both algorithms ended!"<<std::endl;
    std::cout<<"Incremental running time: "<< endInc << " sec." << std::endl;
    std::cout<<"Traditional running time: "<< endTrad <<" sec." << std::endl;
    std::cout <<"Program finished!";


    free(ret);





}
