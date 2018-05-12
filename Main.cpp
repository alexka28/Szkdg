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
 /*   const int BLACK = 0, RED = 1;
    ETTreeNode *leaf = new ETTreeNode(nullptr, nullptr, nullptr, BLACK);

    ETTreeNode *n1 = new ETTreeNode(nullptr, leaf, leaf, BLACK, 5); //node 5
    ETTreeNode *n2 = new ETTreeNode(nullptr, leaf, leaf, RED, 2); //node 2
    ETTreeNode *n3 = new ETTreeNode(nullptr, leaf, leaf, RED, 8); //node 8
    ETTreeNode *n4 = new ETTreeNode(nullptr, leaf, leaf, BLACK, 1); //node 1
    ETTreeNode *n5 = new ETTreeNode(nullptr, leaf, leaf, BLACK, 3); //node 3
    ETTreeNode *n6 = new ETTreeNode(nullptr, leaf, leaf, BLACK, 6); //node 6
    ETTreeNode *n7 = new ETTreeNode(nullptr, leaf, leaf, BLACK, 16); //node 16
    ETTreeNode *n8 = new ETTreeNode(nullptr, leaf, leaf, RED, 7); //node 7
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
*/




//cout<<"3 rangja: "<<myForest.first[3]->rank << " 5 rangja: " <<myForest.first[5]->rank<< " 6 rangja: " << myForest.first[6]->rank <<endl;

    //cout<<"7 color: "<<myForest.first[7]->color<< " 8 color: " <<myForest.first[8]->color<< " 8 color: " << myForest.first[6]->color <<endl;


    cout << "Forest utan" << endl;
    return 0;
}
