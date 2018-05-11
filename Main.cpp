#include <iostream>
#include "DecrementalGraph.h"
#include<set>
#include "Test.h"
#include <utility>
#include "ETT.h"

using namespace std;

int main() {
    /* DecGraph graph(10);
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
     }*/


    DecGraph graph(10);
    GraphNode a(7);
    GraphNode b(8);
    std::set<GraphNode *> mySet;
    mySet.insert(&a);
    b.neighbours[0] = mySet;
    std::set<GraphNode *>::iterator it = mySet.begin();

    cout << &a << endl;
    cout << (*it)->N << endl;
    cout << (**it).N << endl;
//    graph.node[0] = a;
//    graph.node[0].neighbours[0].insert(&a);
//    std::cout<<graph.node[0].neighbours[0].size() << std::endl;
    cout << "insert elott" << endl;

//    auto asd = graph.node[3].neighbours[5].begin();
//    cout << graph.node[3].neighbours[6].size() << endl;
//    cout << (*asd)->N << endl;
//   std::pair<int, int> valamipar (3,6);
//cout<<graph.level.find(valamipar)->second;
//    cout<<"kulcsok szama torles elott "<<graph.level.count(valamipar)<<endl;
//graph.remove(3,6);
//    cout<<"torles utan "<<graph.level.count(valamipar)<<endl;
    //testInsert();
    cout << "Forest elott" << endl;
    ETForest myForest(10);
    /* graph.insert(3, 5, myForest);
     graph.insert(3, 6, myForest);
     graph.insert(3, 7, myForest);
     graph.insert(3, 8, myForest);
     graph.insert(2,3, myForest);*/
    //graph.insert(3, 6, myForest);
    //ETTreeNode *node=myForest.findRoot(3);
    //cout<<graph.connected(3,5,myForest)<<endl;
    ETTreeNode *level = new ETTreeNode(nullptr, nullptr, nullptr, 1, 0);
    ETTreeNode *elso = new ETTreeNode(nullptr, level, level, 0, 1);
    ETTreeNode *masodik = new ETTreeNode(elso, level, level, 1, 2);
    elso->right = masodik;
    ETTreeNode *parent = masodik->parent;
    ETTreeNode *root = parent;
    cout << "parent nodeid: " << parent->nodeId <<endl;
    cout << "root nodeid: " << root->nodeId<<endl;
    parent = parent->parent;
    if(root == nullptr){
        cout<<"parent mostmar nullptr" <<endl;
    }
    else{
        cout<<"root nem nullptr"<<endl;
    }



//cout<<"3 rangja: "<<myForest.first[3]->rank << " 5 rangja: " <<myForest.first[5]->rank<< " 6 rangja: " << myForest.first[6]->rank <<endl;

    //cout<<"7 color: "<<myForest.first[7]->color<< " 8 color: " <<myForest.first[8]->color<< " 8 color: " << myForest.first[6]->color <<endl;


    cout << "Forest utan" << endl;
    return 0;
}
