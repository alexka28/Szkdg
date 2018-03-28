#include <iostream>
#include "UniFind.h"
#include <time.h>
#include <stdlib.h>
#include "CreateInsertQuery.h"
#include "GraphGen.h"
#include <ctime>

//a simple example creating a graph, a disjoint set, a list of inserts and queries
int main()
{
    Graph g(101);
    DisjointSets d(100);
    std::list <struct IQ> iqlist;
    iqlist = createIQ(50, 350);
    bool *ret;
    ret = (bool*)malloc(sizeof(bool));
    *ret = false;
    std::list <struct IQ> ::iterator it;

    srand (time(NULL));
 /*   for(it = iqlist.begin(); it != iqlist.end(); ++it)
    {
        //an insert or on graph it's addedge
        if(it->iq == 0)
        {
            d.insert(it->a, it->b);
            g.addEdge(it->a, it->b);
        }
        //a query
        else
        {
            d.query(it->a, it->b);
            g.queryGraph(it->a, it->b, ret);
            if(d.query(it->a, it->b) != g.queryGraph(it->a, it->b, ret)){
                std::cout<<"baj van";
            }
            //ret tracks if a query for a graph is true or false, and sets to true only if the nodes are in the same component
            *ret = false;

        }
    }*/
    std::cout <<"eddig ok?"<<std::endl;
     std::list<std::list<struct IQ> > smNodes;
    //make the iq'-s for testing
    for(int i = 0; i < 3; ++i){
            std::cout <<"végtelen? i: "<< i <<std::endl;
            if(i == 0){
                    int maxinserts = (100*99)/2;
                     int max = maxinserts * 0.9;
                     int min = maxinserts * 0.7;


            int finalNum = rand()%(max-min+1)+min;
                    for(int j = 0; j < 50; ++j){
                        smNodes.push_back(createIQ(100, finalNum));
                    }
       }
    }
std::clock_t start;
    std::clock_t simple;
     long double duration = 0;
long double simpleido = 0;
long double kulonbseg = 0;
int k = 1;
    std::list<std::list<struct IQ> >::iterator kulsoit;
    for(kulsoit = smNodes.begin(); kulsoit != smNodes.end(); ++kulsoit ){
        std::list<struct IQ> belsolist = *kulsoit;
        std::list<struct IQ>::iterator belsoit;
         std::cout<<k++<<" graf"<<std::endl;
        for(belsoit = belsolist.begin(); belsoit != belsolist.end(); ++belsoit){

            if(belsoit->iq == 0)
        {
             start = std::clock();
            d.insert(belsoit->a, belsoit->b);
           duration += ( std::clock() - start ) / (long double) CLOCKS_PER_SEC;

           simple = std::clock();
            g.addEdge(belsoit->a, belsoit->b);
            kulonbseg = (std::clock() - simple) / (long double) CLOCKS_PER_SEC;
            duration += kulonbseg;
            simpleido += kulonbseg;
        }
         else
        {
start = std::clock();
            d.query(belsoit->a, belsoit->b);
duration += ( std::clock() - start ) / (long double) CLOCKS_PER_SEC;


simple = std::clock();
            g.queryGraph(belsoit->a, belsoit->b, ret);
            simpleido += (std::clock() - simple) / (long double) CLOCKS_PER_SEC;
            if(d.query(belsoit->a, belsoit->b) != g.queryGraph(belsoit->a, belsoit->b, ret)){
                std::cout<<"baj van";
            }
        *ret = false;
        }


    }}
  std::cout<<"inc futas: "<< duration <<'\n';
   std::cout<<"simple futas: "<< simpleido <<'\n';
    std::cout <<"done";

free(ret);
    return 0;
}
