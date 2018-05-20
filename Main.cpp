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
using namespace std;

int main() {
     DecGraph graph(10);
     GraphNode a(5);
     graph.node[0] = a;
     std::cout <<graph.node[0].N << std::endl;
     std::set<GraphNode*> setem;
     GraphNode b(5);
     GraphNode c(5);
     setem.insert(&b);
     std::cout << setem.size() << std::endl;
     std::cerr << a.neighbours[0].size() << std::endl;
     setem.insert(&c);
     a.neighbours[0] = setem;
     std::cout<<a.neighbours[0].size()<<std::endl;
     for(int i = 0; i < 5; ++i)
     {
         std::cout<<"Az " << i+1<< " neighbour merete: " << a.neighbours[i].size() << std::endl;
     }


 /*   DecGraph graph(10);
    GraphNode a(7);
    GraphNode b(8);
    std::set<GraphNode *> mySet;
    mySet.insert(&a);
    b.neighbours[0] = mySet;
    std::set<GraphNode *>::iterator it = mySet.begin();

    cout << &a << endl;
    cout << (*it)->N << endl;
    cout << (**it).N << endl;
   graph.node[0] = a;
    graph.node[0].neighbours[0].insert(&a); */
//    std::cout<<graph.node[0].neighbours[0].size() << std::endl;
    cout << "insert elott" << endl;

//    auto asd = graph.node[3].neighbours[5].begin();
//    cout << graph.node[3].neighbours[6].size() << endl;
//    cout << (*asd)->N << endl;


//    cout<<"kulcsok szama torles elott "<<graph.level.count(valamipar)<<endl;
//graph.remove(3,6);
//    cout<<"torles utan "<<graph.level.count(valamipar)<<endl;
    //testInsert();

    DecGraph grafom(10);
    ETForest forestem(10);
    Graph simagraf(10);
std::list<std::pair<int,int>> insertList = fillGraph(10);
    std::list<std::pair<int,int>>::iterator insertIt;
    for(insertIt = insertList.begin(); insertIt != insertList.end(); ++insertIt){
        cout<<"elso node: " << insertIt->first<<" masodik node: " << insertIt->second<<endl;
        grafom.insert(insertIt->first,insertIt->second,forestem);
        simagraf.addEdge(insertIt->first,insertIt->second);
    }
    std::list<std::pair<std::pair<int, int>, int>> delquer = createDQ(insertList,10);
    std::list<std::pair<std::pair<int, int>, int>>:: iterator queryIt;
    for(queryIt = delquer.begin(); queryIt != delquer.end(); ++queryIt){
        if(queryIt->second == 0){
            cout<<"torles :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
        }
        else{
            cout<<"query :" << queryIt->first.first << " - " <<queryIt->first.second<<endl;
        }
    }



    return 0;
}
