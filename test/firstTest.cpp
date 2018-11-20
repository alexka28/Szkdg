//
// Created by Alex on 2018. 08. 10..
//

#include "gtest/gtest.h"
#include "../src/TestETT.h"
#include "../src/DecrementalGraph.h"
#include "../src/ETTQueries.h"

using list = std::list<int>;

void testInsertEdge(int x, int y, DecGraph& graph, ETForest& forest){
    graph.insert(x,y,forest);
    forest.verifyFirstLast();
    forest.verify2SideConnection();
    EXPECT_TRUE(forest.verifyProperties(forest.findRoot(x)));
    EXPECT_TRUE(forest.verifyProperties(forest.findRoot(y)));
    EXPECT_TRUE(graph.connected(x,y, forest));

}

void hitBreakPoint(int x, int y, DecGraph graph, ETForest forest){
    bid = true;
    std::cout<<"Insert("<<x<<", "<<y<<")"<<std::endl; 
    testInsertEdge(x,y,graph,forest);

    isFirstTime = true;
    inOrder(forest.findRoot(x));
    std::cout<<std::endl;
    std::cout<<std::endl;
    bid = false;
}

void testRemoveEdge(int x, int y, DecGraph& graph, ETForest& forest){
    graph.remove(x,y,forest);
    forest.verifyFirstLast();
    forest.verify2SideConnection();
    EXPECT_TRUE(forest.verifyProperties(forest.findRoot(x)));
    EXPECT_TRUE(forest.verifyProperties(forest.findRoot(y)));
}

void testInsertEdgeAndInOrder(int x, int y, DecGraph& graph, ETForest& forest, const std::list<int>& expectedInorder){
    testInsertEdge(x,y,graph,forest);
    std::list<int> treeInOrder;
    inOrder(forest.findRoot(x), treeInOrder);
    assert(expectedInorder.size () == treeInOrder.size());
    assert(isSameInOrder(expectedInorder, treeInOrder));
}

void testRemoveEdgeAndInOrder(const int x, const int y, DecGraph& graph, ETForest forest, const std::list<int>& expectedXInorder, const std::list<int>& expectedYInorder){
    if(forest.contains(x,y)){
        graph.remove(x,y,forest);
        //EXPECT_FALSE(graph.connected(x,y,forest));
        forest.verifyFirstLast();
        forest.verify2SideConnection();
        EXPECT_TRUE(forest.verifyProperties(forest.findRoot(x)));
        EXPECT_TRUE(forest.verifyProperties(forest.findRoot(y)));
        std::list<int> xTreeInOrder, yTreeInOrder;
        inOrder(forest.findRoot(x), xTreeInOrder);
        inOrder(forest.findRoot(y), yTreeInOrder);
//        isFirstTime = true;
//        inOrder(forest.findRoot(y));

        assert(expectedXInorder.size () == xTreeInOrder.size());
        assert(isSameInOrder(expectedXInorder, xTreeInOrder));
        assert(expectedYInorder.size () == yTreeInOrder.size());
        assert(isSameInOrder(expectedYInorder, yTreeInOrder));
    }

}

TEST(CompareTest, CompareTrees) {
    auto a1 = new ETTreeNode(BLACK, 1, 1);
    auto a2 = new ETTreeNode(RED, 2, 0, a1);
    auto a3 = new ETTreeNode(RED, 3, 0, a1);

    a1->left = a2;
    a1->right = a3;

    auto b1 = new ETTreeNode(BLACK, 1, 1);
    auto b2 = new ETTreeNode(RED, 2, 0, b1);
    auto b3 = new ETTreeNode(RED, 3, 0, b1);

    b1->left = b2;
    b1->right = b3;

    EXPECT_TRUE(TestETT::compare(a1, b1) == 0);
}

TEST(CompareTest, CompareUnequalTrees) {
    auto a1 = new ETTreeNode(BLACK, 1, 1);
    auto a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 2);
    auto a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;

    auto b1 = new ETTreeNode(BLACK, 1, 1);
    auto b2 = new ETTreeNode(RED, 2, 0, b1);
    auto b3 = new ETTreeNode(RED, 3, 1, b1);

    b1->left = b2;
    b1->right = b3;

    EXPECT_TRUE(TestETT::compare(a1, b1) != 0);
    EXPECT_FALSE(TestETT::compare(a1, b1) == 0);
}

TEST(BSTDeleteTest, deleteLeaf) {
    //Input
    auto a1 = new ETTreeNode(BLACK, 5, 1);
    auto a2 = new ETTreeNode(RED, 3, 0, a1);
    auto a3 = new ETTreeNode(RED, 8, 0, a1);

    a1->left = a2;
    a1->right = a3;

    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(a1));

    ETForest::newDelete(a2);
    EXPECT_TRUE(ETForest::verifyProperties(a1));
}

TEST(BSTDeleteTest, DeleteOnlyMinThenMax) {
    //Input
    auto a1 = new ETTreeNode(BLACK, 10, 2); //10
    auto a2 = new ETTreeNode(BLACK, 8, 1, a1); //8
    auto a3 = new ETTreeNode(RED, 6, 0, a2); //6
    auto a4 = new ETTreeNode(RED, 9, 0, a2); //9
    auto a5 = new ETTreeNode(BLACK, 15, 1, a1); // 15
    auto a6 = new ETTreeNode(RED, 12, 0, a5); // 12
    auto a7 = new ETTreeNode(RED, 18, 0, a5); // 18

    a1->left = a2;
    a1->right = a5;

    a2->left = a3;
    a2->right = a4;

    a5->left = a6;
    a5->right = a7;

    //Verify Input
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));
    //Expected output
    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));

    ETForest::newDelete(a2);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));
}

TEST(BSTDeleteTest, DeleteRoot) {
    auto a1 = new ETTreeNode(BLACK, 5, 1);
    auto a2 = new ETTreeNode(RED, 2, 0, a1);
    auto a3 = new ETTreeNode(RED, 1, 0, a1);

    a1->right = a2;
    a1->left = a3;

    //Verify Input
    ETForest::verifyProperties(a1);
    //Verify deletes
    ETForest::newDelete(a1);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a2)));

    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a2)));
}

TEST(BSTDeleteTest, CheckDeleteCase6_Right) {
    auto a1 = new ETTreeNode(BLACK, 3, 2);
    auto a2 = new ETTreeNode(BLACK, 4, 1, a1);
    auto a3 = new ETTreeNode(BLACK, 3, 1, a1);
    auto a4 = new ETTreeNode(RED, 7, 0, a3);
    auto a5 = new ETTreeNode(RED, 4, 0, a3);

    a1->left = a2;
    a1->right = a3;

    a3->left = a4;
    a3->right = a5;

    //Verify Input
    ETForest::verifyProperties(a1);

    ETForest::newDelete(a2);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));
}

TEST(BSTDeleteTest, CheckDeleteCase6_Left) {
    auto a1 = new ETTreeNode(BLACK, 3, 2);
    auto a2 = new ETTreeNode(BLACK, 4, 1, a1);
    auto a3 = new ETTreeNode(BLACK, 3, 1, a1);
    auto a4 = new ETTreeNode(RED, 7, 0, a2);
    auto a5 = new ETTreeNode(RED, 4, 0, a2);

    a1->left = a2;
    a1->right = a3;

    a2->left = a4;
    a2->right = a5;

    //Verify Input
    ETForest::verifyProperties(a1);

    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));
}

TEST(ForestMember, logN_Test){
    ETForest forest(10);
    EXPECT_TRUE(forest.logN == 4);
}

TEST(InsertTest, FirstInserts){
    DecGraph graph(10);
    ETForest forest(10);
    testInsertEdgeAndInOrder(3,4,graph,forest,list {3,4,3});
    testInsertEdgeAndInOrder(3,7,graph,forest,list {3,4,3,7,3});
    testInsertEdgeAndInOrder(6,4,graph,forest,list {4,3,7,3,4,6,4});
    testInsertEdgeAndInOrder(1,0,graph,forest,list {0,1,0});
    testInsertEdgeAndInOrder(8,6,graph,forest,list {6,4,3,7,3,4,6,8,6});
}
TEST(InsertTest, ConnectedAfterInsert){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(1,3,graph,forest,list {1,3,1});
    testInsertEdgeAndInOrder(0,6,graph,forest,list {0,6,0});
    testInsertEdgeAndInOrder(6,3,graph,forest,list {3,1,3,6,0,6,3});
    testInsertEdgeAndInOrder(1,5,graph,forest,list {1,3,6,0,6,3,1,5,1});
    testInsertEdgeAndInOrder(5,7,graph,forest,list {5,1,3,6,0,6,3,1,5,7,5});
    testInsertEdgeAndInOrder(4,8,graph,forest,list {4,8,4});
    testInsertEdgeAndInOrder(4,5,graph,forest,list {4,8,4,5,1,3,6,0,6,3,1,5,7,5,4});
    testInsertEdgeAndInOrder(1,7,graph,forest,list {4,8,4,5,1,3,6,0,6,3,1,5,7,5,4});
    testInsertEdgeAndInOrder(0,1,graph,forest,list {4,8,4,5,1,3,6,0,6,3,1,5,7,5,4});
    testInsertEdgeAndInOrder(8,3,graph,forest,list {4,8,4,5,1,3,6,0,6,3,1,5,7,5,4});
}
TEST(InsertTest, InfiniteLoopTest_1){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(4,8,graph,forest,list {4,8,4});
    testInsertEdgeAndInOrder(4,3,graph,forest,list {3,4,8,4,3});
    testInsertEdgeAndInOrder(0,5,graph,forest,list {0,5,0});
    testInsertEdgeAndInOrder(1,5,graph,forest,list {1,5,0,5,1});
    testInsertEdgeAndInOrder(3,0,graph,forest,list {0,5,1,5,0,3,4,8,4,3,0});
    testInsertEdgeAndInOrder(8,6,graph,forest,list {6,8,4,3,0,5,1,5,0,3,4,8,6});
}
TEST(InsertTest, InfiniteLoopTest_2){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(6,2,graph,forest,list {2,6,2});
    testInsertEdgeAndInOrder(8,7,graph,forest,list {7,8,7});
    testInsertEdgeAndInOrder(0,8,graph,forest,list {0,8,7,8,0});
    testInsertEdgeAndInOrder(2,1,graph,forest,list {1,2,6,2,1});
    testInsertEdgeAndInOrder(0,1,graph,forest,list {0,8,7,8,0,1,2,6,2,1,0});
    testInsertEdgeAndInOrder(3,5,graph,forest,list {3,5,3});
    testInsertEdgeAndInOrder(6,8,graph,forest,list {0,8,7,8,0,1,2,6,2,1,0});
    testInsertEdgeAndInOrder(1,7,graph,forest,list {0,8,7,8,0,1,2,6,2,1,0});
    testInsertEdgeAndInOrder(7,4,graph,forest,list {4,7,8,0,1,2,6,2,1,0,8,7,4});
    testInsertEdgeAndInOrder(7,0,graph,forest,list {4,7,8,0,1,2,6,2,1,0,8,7,4});
    testInsertEdgeAndInOrder(5,6,graph,forest,list {5,3,5,6,2,1,0,8,7,4,7,8,0,1,2,6,5});
}
TEST(InsertTest, InfiniteLoopTest_3) {
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(4,5,graph,forest,list {4,5,4});
    testInsertEdgeAndInOrder(0,6,graph,forest,list {0,6,0});
    testInsertEdgeAndInOrder(0,5,graph,forest,list {0,6,0,5,4,5,0});
    testInsertEdgeAndInOrder(2,1,graph,forest,list {1,2,1});
    testInsertEdgeAndInOrder(5,1,graph,forest,list {1,2,1,5,4,5,0,6,0,5,1});
    testInsertEdgeAndInOrder(2,0,graph,forest,list {1,2,1,5,4,5,0,6,0,5,1});
    testInsertEdgeAndInOrder(3,2,graph,forest,list {2,1,5,4,5,0,6,0,5,1,2,3,2});
    testInsertEdgeAndInOrder(4,6,graph,forest,list {2,1,5,4,5,0,6,0,5,1,2,3,2});
    testInsertEdgeAndInOrder(0,1,graph,forest,list {2,1,5,4,5,0,6,0,5,1,2,3,2});
    testInsertEdgeAndInOrder(7,0,graph,forest,list {0,6,0,5,1,2,3,2,1,5,4,5,0,7,0});
    testInsertEdgeAndInOrder(4,7,graph,forest,list {0,6,0,5,1,2,3,2,1,5,4,5,0,7,0});
    testInsertEdgeAndInOrder(2,5,graph,forest,list {0,6,0,5,1,2,3,2,1,5,4,5,0,7,0});
    testInsertEdgeAndInOrder(5,7,graph,forest,list {0,6,0,5,1,2,3,2,1,5,4,5,0,7,0});
    testInsertEdgeAndInOrder(7,3,graph,forest,list {0,6,0,5,1,2,3,2,1,5,4,5,0,7,0});
    testInsertEdgeAndInOrder(5,6,graph,forest,list {0,6,0,5,1,2,3,2,1,5,4,5,0,7,0});
    testInsertEdgeAndInOrder(4,8,graph,forest,list {4,5,0,7,0,6,0,5,1,2,3,2,1,5,4,8,4});
}
TEST(InsertTest, BlackHeightTest_1){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(7,8,graph,forest,list {7,8,7});
    testInsertEdgeAndInOrder(5,7,graph,forest,list {5,7,8,7,5});
    testInsertEdgeAndInOrder(8,0,graph,forest,list {0,8,7,5,7,8,0});
    testInsertEdgeAndInOrder(7,0,graph,forest,list {0,8,7,5,7,8,0});
    testInsertEdgeAndInOrder(3,7,graph,forest,list {3,7,5,7,8,0,8,7,3});
    testInsertEdgeAndInOrder(6,2,graph,forest,list {2,6,2});
    testInsertEdgeAndInOrder(4,7,graph,forest,list {4,7,5,7,8,0,8,7,3,7,4});
    testInsertEdgeAndInOrder(8,5,graph,forest,list {4,7,5,7,8,0,8,7,3,7,4});
    testInsertEdgeAndInOrder(2,7,graph,forest,list {2,6,2,7,5,7,8,0,8,7,3,7,4,7,2});
    testInsertEdgeAndInOrder(7,1,graph,forest,list {1,7,5,7,8,0,8,7,3,7,4,7,2,6,2,7,1});
}
TEST(InsertTest, BlackHeightTest_2){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(3,1,graph,forest,list {1,3,1});
    testInsertEdgeAndInOrder(8,3,graph,forest,list {3,1,3,8,3});
    testInsertEdgeAndInOrder(3,7,graph,forest,list {3,1,3,8,3,7,3});
    testInsertEdgeAndInOrder(6,4,graph,forest,list {4,6,4});
    testInsertEdgeAndInOrder(3,6,graph,forest,list {3,1,3,8,3,7,3,6,4,6,3});
    testInsertEdgeAndInOrder(4,5,graph,forest,list {4,6,3,1,3,8,3,7,3,6,4,5,4});
    testInsertEdgeAndInOrder(5,8,graph,forest,list {4,6,3,1,3,8,3,7,3,6,4,5,4});
    testInsertEdgeAndInOrder(4,2,graph,forest,list {2,4,6,3,1,3,8,3,7,3,6,4,5,4,2});
    testInsertEdgeAndInOrder(1,4,graph,forest,list {2,4,6,3,1,3,8,3,7,3,6,4,5,4,2});
    testInsertEdgeAndInOrder(0,3,graph,forest,list {0,3,1,3,8,3,7,3,6,4,5,4,2,4,6,3,0});
}
TEST(InsertTest, BlackHeightTest_3){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(4,3,graph,forest,list {3,4,3});
    testInsertEdgeAndInOrder(6,5,graph,forest,list {5,6,5});
    testInsertEdgeAndInOrder(3,0,graph,forest,list {0,3,4,3,0});
    testInsertEdgeAndInOrder(7,0,graph,forest,list {0,3,4,3,0,7,0});
    testInsertEdgeAndInOrder(1,7,graph,forest,list {1,7,0,3,4,3,0,7,1});
    testInsertEdgeAndInOrder(8,7,graph,forest,list {7,0,3,4,3,0,7,1,7,8,7});
    testInsertEdgeAndInOrder(8,5,graph,forest,list {5,6,5,8,7,0,3,4,3,0,7,1,7,8,5});
    testInsertEdgeAndInOrder(8,2,graph,forest,list {2,8,7,0,3,4,3,0,7,1,7,8,5,6,5,8,2});
}
TEST(InsertTest, nullptrderef){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdgeAndInOrder(8,1,graph,forest,list {1,8,1});
    testInsertEdgeAndInOrder(7,8,graph,forest,list {7,8,1,8,7});
    testInsertEdgeAndInOrder(5,2,graph,forest,list {2,5,2});
    testInsertEdgeAndInOrder(0,6,graph,forest,list {0,6,0});
    testInsertEdgeAndInOrder(5,6,graph,forest,list {5,2,5,6,0,6,5});
    testInsertEdgeAndInOrder(3,5,graph,forest,list {3,5,2,5,6,0,6,5,3});
    testInsertEdgeAndInOrder(7,6,graph,forest,list {6,0,6,5,3,5,2,5,6,7,8,1,8,7,6});
    testInsertEdgeAndInOrder(0,8,graph,forest,list {6,0,6,5,3,5,2,5,6,7,8,1,8,7,6});
    testInsertEdgeAndInOrder(4,8,graph,forest,list {4,8,1,8,7,6,0,6,5,3,5,2,5,6,7,8,4});
}
TEST(InsertTest, lastseenfail){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(8,5,graph,forest);
    testInsertEdge(0,6,graph,forest);
    testInsertEdge(2,5,graph,forest);
    testInsertEdge(8,1,graph,forest);
    testInsertEdge(1,0,graph,forest);
    testInsertEdge(4,1,graph,forest);
    testInsertEdge(6,2,graph,forest);
    testInsertEdge(6,3,graph,forest);
    testInsertEdge(1,6,graph,forest);
    testInsertEdge(0,5,graph,forest);
    testInsertEdge(4,0,graph,forest);
    testInsertEdge(7,5,graph,forest);
}
TEST(InsertTest, hugeGraph){
    DecGraph graph(100);
    ETForest forest(100);

    testInsertEdge(28,68,graph,forest);
    testInsertEdge(30,13,graph,forest);
    testInsertEdge(73,97,graph,forest);
    testInsertEdge(33,75,graph,forest);
    testInsertEdge(45,65,graph,forest);
    testInsertEdge(91,86,graph,forest);
    testInsertEdge(24,74,graph,forest);
    testInsertEdge(4,86,graph,forest);
    testInsertEdge(40,10,graph,forest);
    testInsertEdge(53,66,graph,forest);
    testInsertEdge(29,93,graph,forest);
    testInsertEdge(18,0,graph,forest);
    testInsertEdge(12,5,graph,forest);
    testInsertEdge(19,22,graph,forest);
    testInsertEdge(38,52,graph,forest);
    testInsertEdge(58,48,graph,forest);
    testInsertEdge(32,11,graph,forest);
    testInsertEdge(36,76,graph,forest);
    testInsertEdge(73,6,graph,forest);
    testInsertEdge(67,62,graph,forest);
    testInsertEdge(29,33,graph,forest);
    testInsertEdge(86,46,graph,forest);
    testInsertEdge(9,57,graph,forest);
    testInsertEdge(85,76,graph,forest);
    testInsertEdge(38,14,graph,forest);
    testInsertEdge(51,29,graph,forest);
    testInsertEdge(17,86,graph,forest);
    testInsertEdge(59,82,graph,forest);
    testInsertEdge(63,91,graph,forest);
    testInsertEdge(78,18,graph,forest);
    testInsertEdge(22,15,graph,forest);
    testInsertEdge(53,21,graph,forest);
    testInsertEdge(15,75,graph,forest);
    testInsertEdge(25,57,graph,forest);
    testInsertEdge(30,7,graph,forest);
    testInsertEdge(35,96,graph,forest);
    testInsertEdge(28,75,graph,forest);
    testInsertEdge(96,40,graph,forest);
    testInsertEdge(45,11,graph,forest);
    testInsertEdge(60,49,graph,forest);
    testInsertEdge(86,55,graph,forest);
    testInsertEdge(70,30,graph,forest);
    testInsertEdge(83,36,graph,forest);
    testInsertEdge(34,48,graph,forest);
    testInsertEdge(18,33,graph,forest);
    testInsertEdge(1,41,graph,forest);
    testInsertEdge(64,71,graph,forest);
    testInsertEdge(71,28,graph,forest);
    testInsertEdge(82,9,graph,forest);
    testInsertEdge(27,35,graph,forest);
    testInsertEdge(89,31,graph,forest);
    testInsertEdge(32,68,graph,forest);
    testInsertEdge(50,43,graph,forest);
    testInsertEdge(48,65,graph,forest);
    testInsertEdge(20,53,graph,forest);
    testInsertEdge(55,6,graph,forest);
    testInsertEdge(68,62,graph,forest);
    testInsertEdge(2,64,graph,forest);
    testInsertEdge(29,24,graph,forest);
    testInsertEdge(74,75,graph,forest);
    testInsertEdge(4,8,graph,forest);
    testInsertEdge(49,39,graph,forest);
    testInsertEdge(23,9,graph,forest);
    testInsertEdge(91,16,graph,forest);
    testInsertEdge(98,15,graph,forest);
    testInsertEdge(1,12,graph,forest);
    testInsertEdge(22,51,graph,forest);
    testInsertEdge(51,42,graph,forest);
}
TEST(InsertTest, HugeGraph2){
    DecGraph graph(100);
    ETForest forest(100);

    testInsertEdge(31,58,graph,forest);
    testInsertEdge(5,45,graph,forest);
    testInsertEdge(43,53,graph,forest);
    testInsertEdge(69,76,graph,forest);
    testInsertEdge(46,45,graph,forest);
    testInsertEdge(25,10,graph,forest);
    testInsertEdge(0,10,graph,forest);
    testInsertEdge(50,13,graph,forest);
    testInsertEdge(8,38,graph,forest);
    testInsertEdge(89,87,graph,forest);
    testInsertEdge(43,35,graph,forest);
    testInsertEdge(8,9,graph,forest);
    testInsertEdge(13,44,graph,forest);
    testInsertEdge(51,92,graph,forest);
    testInsertEdge(39,41,graph,forest);
    testInsertEdge(7,72,graph,forest);
    testInsertEdge(16,6,graph,forest);
    testInsertEdge(3,6,graph,forest);
    testInsertEdge(86,21,graph,forest);
    testInsertEdge(93,68,graph,forest);
    testInsertEdge(27,65,graph,forest);
    testInsertEdge(67,88,graph,forest);
    testInsertEdge(67,97,graph,forest);
    testInsertEdge(78,53,graph,forest);
    testInsertEdge(22,72,graph,forest);
    testInsertEdge(90,41,graph,forest);
    testInsertEdge(97,90,graph,forest);
    testInsertEdge(11,44,graph,forest);
    testInsertEdge(19,25,graph,forest);
    testInsertEdge(2,87,graph,forest);
    testInsertEdge(50,27,graph,forest);
    testInsertEdge(48,38,graph,forest);
    testInsertEdge(58,53,graph,forest);
    testInsertEdge(76,9,graph,forest);
    testInsertEdge(77,2,graph,forest);
    testInsertEdge(1,46,graph,forest);
    testInsertEdge(56,36,graph,forest);
    testInsertEdge(79,3,graph,forest);
    testInsertEdge(6,51,graph,forest);
    testInsertEdge(75,84,graph,forest);
    testInsertEdge(56,60,graph,forest);
    testInsertEdge(95,89,graph,forest);
    testInsertEdge(36,85,graph,forest);
    testInsertEdge(1,94,graph,forest);
    testInsertEdge(69,7,graph,forest);
    testInsertEdge(55,50,graph,forest);
    testInsertEdge(22,51,graph,forest);
    testInsertEdge(37,1,graph,forest);
    testInsertEdge(34,10,graph,forest);
    testInsertEdge(33,24,graph,forest);
    testInsertEdge(81,9,graph,forest);
    testInsertEdge(3,18,graph,forest);
    testInsertEdge(54,44,graph,forest);
    testInsertEdge(12,57,graph,forest);
    testInsertEdge(58,38,graph,forest);
    testInsertEdge(1,7,graph,forest);
    testInsertEdge(63,38,graph,forest);
    testInsertEdge(12,43,graph,forest);
    testInsertEdge(89,91,graph,forest);
    testInsertEdge(44,18,graph,forest);
    testInsertEdge(6,77,graph,forest);
    testInsertEdge(35,38,graph,forest);
    testInsertEdge(60,72,graph,forest);
    testInsertEdge(55,37,graph,forest);
    testInsertEdge(80,69,graph,forest);
    testInsertEdge(41,1,graph,forest);
    testInsertEdge(74,19,graph,forest);
    testInsertEdge(63,4,graph,forest);
    testInsertEdge(83,15,graph,forest);
    testInsertEdge(52,85,graph,forest);
    testInsertEdge(88,0,graph,forest);
    testInsertEdge(65,53,graph,forest);
    testInsertEdge(45,8,graph,forest);
    testInsertEdge(48,67,graph,forest);
    testInsertEdge(39,25,graph,forest);
    testInsertEdge(50,18,graph,forest);
    testInsertEdge(42,76,graph,forest);
    testInsertEdge(45,3,graph,forest);
    testInsertEdge(56,18,graph,forest);
    testInsertEdge(32,57,graph,forest);
    testInsertEdge(15,60,graph,forest);
    testInsertEdge(60,26,graph,forest);
    testInsertEdge(65,94,graph,forest);
    testInsertEdge(53,25,graph,forest);
    testInsertEdge(54,27,graph,forest);
    testInsertEdge(67,91,graph,forest);
    testInsertEdge(75,16,graph,forest);
    testInsertEdge(83,74,graph,forest);
    testInsertEdge(88,22,graph,forest);
    testInsertEdge(40,46,graph,forest);
    testInsertEdge(58,45,graph,forest);
    testInsertEdge(13,5,graph,forest);
    testInsertEdge(51,63,graph,forest);
    testInsertEdge(6,63,graph,forest);
    testInsertEdge(13,39,graph,forest);
    testInsertEdge(36,63,graph,forest);
    testInsertEdge(22,82,graph,forest);
    testInsertEdge(83,17,graph,forest);
    testInsertEdge(7,43,graph,forest);
    testInsertEdge(52,2,graph,forest);
    testInsertEdge(69,17,graph,forest);
    testInsertEdge(75,94,graph,forest);
    testInsertEdge(12,80,graph,forest);
    testInsertEdge(43,19,graph,forest);
    testInsertEdge(53,54,graph,forest);
    testInsertEdge(3,59,graph,forest);
    testInsertEdge(79,10,graph,forest);
    testInsertEdge(15,64,graph,forest);
    testInsertEdge(28,39,graph,forest);
    testInsertEdge(38,97,graph,forest);
    testInsertEdge(14,12,graph,forest);
    testInsertEdge(40,71,graph,forest);
    testInsertEdge(29,37,graph,forest);
    testInsertEdge(11,22,graph,forest);
    testInsertEdge(84,56,graph,forest);
    testInsertEdge(58,68,graph,forest);
    testInsertEdge(43,82,graph,forest);
    testInsertEdge(92,2,graph,forest);
    testInsertEdge(27,15,graph,forest);
    testInsertEdge(49,43,graph,forest);
    testInsertEdge(30,48,graph,forest);
    testInsertEdge(74,38,graph,forest);
    testInsertEdge(21,96,graph,forest);
    testInsertEdge(13,15,graph,forest);
    testInsertEdge(67,57,graph,forest);
    testInsertEdge(31,66,graph,forest);
    testInsertEdge(72,34,graph,forest);
    testInsertEdge(17,81,graph,forest);
}

TEST(DeleteTest, DISABLED_firstDelete){
    DecGraph graph(100);
    ETForest forest(100);
    testInsertEdgeAndInOrder(16,0,graph,forest,list {0,16,0});
    testInsertEdgeAndInOrder(10,13,graph,forest,list {10,13,10});
    testInsertEdgeAndInOrder(5,7,graph,forest,list {5,7,5});
    testInsertEdgeAndInOrder(18,3,graph,forest,list {3,18,3});
    testInsertEdgeAndInOrder(8,0,graph,forest,list {0,16,0,8,0});
    testInsertEdgeAndInOrder(0,11,graph,forest,list {0,16,0,8,0,11,0});
    testInsertEdgeAndInOrder(10,11,graph,forest,list {10,13,10,11,0,16,0,8,0,11,10});
    testInsertEdgeAndInOrder(18,15,graph,forest,list {15,18,3,18,15});
    testInsertEdgeAndInOrder(11,13,graph,forest,list {10,13,10,11,0,16,0,8,0,11,10});
    testInsertEdgeAndInOrder(4,6,graph,forest,list {4,6,4});
    testInsertEdgeAndInOrder(13,1,graph,forest,list {1,13,10,11,0,16,0,8,0,11,10,13,1});
    testInsertEdgeAndInOrder(8,6,graph,forest,list {6,4,6,8,0,11,10,13,1,13,10,11,0,16,0,8,6});
    testInsertEdgeAndInOrder(5,3,graph,forest,list {3,18,15,18,3,5,7,5,3});
    testInsertEdgeAndInOrder(17,2,graph,forest,list {2,17,2});
    testInsertEdgeAndInOrder(14,3,graph,forest,list {3,18,15,18,3,5,7,5,3,14,3});
    testInsertEdgeAndInOrder(16,3,graph,forest,list {3,18,15,18,3,5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3});
    testInsertEdgeAndInOrder(12,5,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(8,1,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(12,8,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(5,14,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(11,9,graph,forest,list {9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,9});
    testInsertEdgeAndInOrder(2,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,16,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(6,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,16,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(6,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,16,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,9,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,9,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,9,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});

    testRemoveEdgeAndInOrder(5,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,3,14,2}, list {7});
    testRemoveEdgeAndInOrder(18,3,graph,forest,list {18,15,18}, list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,5,12,5,3,14,2});
    testRemoveEdgeAndInOrder(8,0,graph,forest,list {8,6,4,6,8},list {2,17,2,14,3,16,0,11,9,11,10,13,1,13,10,11,0,16,3,5,12,5,3,14,2});
    testRemoveEdgeAndInOrder(0,11,graph,forest,list {2,17,2,14,3,16,0,16,3,5,12,5,3,14,2}, list {11,9,11,10,13,1,13,10,11});
    testRemoveEdgeAndInOrder(18,15,graph,forest,list {18},list {15});
    testRemoveEdgeAndInOrder(11,13,graph,forest,list {},list {});
//    testRemoveEdge(5,7,graph,forest);
//    testRemoveEdge(18,3,graph,forest);
//    testRemoveEdge(8,0,graph,forest);
//    testRemoveEdge(0,11,graph,forest);
//    testRemoveEdge(18,15,graph,forest);
//    testRemoveEdge(11,13,graph,forest);
}
TEST(DeleteTest, DISABLED_FirstDeleteWOInorder){
    DecGraph graph(20);
    ETForest forest(20);
    testInsertEdgeAndInOrder(16,0,graph,forest,list {0,16,0});
    testInsertEdgeAndInOrder(10,13,graph,forest,list {10,13,10});
    testInsertEdgeAndInOrder(5,7,graph,forest,list {5,7,5});
    testInsertEdgeAndInOrder(18,3,graph,forest,list {3,18,3});
    testInsertEdgeAndInOrder(8,0,graph,forest,list {0,16,0,8,0});
    testInsertEdgeAndInOrder(0,11,graph,forest,list {0,16,0,8,0,11,0});
    testInsertEdgeAndInOrder(10,11,graph,forest,list {10,13,10,11,0,16,0,8,0,11,10});
    testInsertEdgeAndInOrder(18,15,graph,forest,list {15,18,3,18,15});
    testInsertEdgeAndInOrder(11,13,graph,forest,list {10,13,10,11,0,16,0,8,0,11,10});
    testInsertEdgeAndInOrder(4,6,graph,forest,list {4,6,4});
    testInsertEdgeAndInOrder(13,1,graph,forest,list {1,13,10,11,0,16,0,8,0,11,10,13,1});
    testInsertEdgeAndInOrder(8,6,graph,forest,list {6,4,6,8,0,11,10,13,1,13,10,11,0,16,0,8,6});
    testInsertEdgeAndInOrder(5,3,graph,forest,list {3,18,15,18,3,5,7,5,3});
    testInsertEdgeAndInOrder(17,2,graph,forest,list {2,17,2});
    testInsertEdgeAndInOrder(14,3,graph,forest,list {3,18,15,18,3,5,7,5,3,14,3});
    testInsertEdgeAndInOrder(16,3,graph,forest,list {3,18,15,18,3,5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3});
    testInsertEdgeAndInOrder(12,5,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(8,1,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(12,8,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(5,14,graph,forest,list {5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5});
    testInsertEdgeAndInOrder(11,9,graph,forest,list {9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,3,16,0,8,6,4,6,8,0,11,9});
    testInsertEdgeAndInOrder(2,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,16,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(6,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,16,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(6,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(10,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,5,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,12,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(7,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(8,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,16,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(14,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(4,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,0,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(5,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(9,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,9,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(18,14,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,1,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,9,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(3,4,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(17,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(13,18,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,15,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(15,9,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(0,3,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,2,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,11,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(1,17,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,13,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(11,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(2,6,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,7,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(12,10,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});
    testInsertEdgeAndInOrder(16,8,graph,forest,list {2,17,2,14,3,16,0,8,6,4,6,8,0,11,9,11,10,13,1,13,10,11,0,16,3,18,15,18,3,5,12,5,7,5,3,14,2});

    testRemoveEdge(5,7,graph,forest);
    EXPECT_TRUE(graph.connected(5,7,forest));
    testRemoveEdge(18,3,graph,forest);
    testRemoveEdge(8,0,graph,forest);
    testRemoveEdge(0,11,graph,forest);
    testRemoveEdge(18,15,graph,forest);
    testRemoveEdge(11,13,graph,forest);
}
TEST(DeleteTest, SecondDelete){
    DecGraph graph(20);
    ETForest forest(20);
    testInsertEdge(18,15,graph,forest);
    testInsertEdge(8,5,graph,forest);
    testInsertEdge(14,17,graph,forest);
    testInsertEdge(8,7,graph,forest);
    testInsertEdge(16,9,graph,forest);
    testInsertEdge(1,9,graph,forest);
    testInsertEdge(18,0,graph,forest);
    testInsertEdge(7,11,graph,forest);
    testInsertEdge(8,10,graph,forest);
    testInsertEdge(14,12,graph,forest);
    testInsertEdge(15,14,graph,forest);
    testInsertEdge(0,7,graph,forest);
    testInsertEdge(3,9,graph,forest);
    testInsertEdge(18,3,graph,forest);
    testInsertEdge(8,1,graph,forest);
    testInsertEdge(3,2,graph,forest);
    testInsertEdge(15,7,graph,forest);
    testInsertEdge(2,15,graph,forest);
    testInsertEdge(13,8,graph,forest);
    testInsertEdge(4,9,graph,forest);
    testInsertEdge(4,17,graph,forest);
    testInsertEdge(7,3,graph,forest);
    testInsertEdge(11,9,graph,forest);
    testInsertEdge(7,12,graph,forest);
    testInsertEdge(11,14,graph,forest);
    testInsertEdge(6,6,graph,forest);
    testInsertEdge(6,10,graph,forest);
    testInsertEdge(18,4,graph,forest);
    testInsertEdge(13,0,graph,forest);
    testInsertEdge(5,9,graph,forest);
    testInsertEdge(0,1,graph,forest);
    testInsertEdge(16,13,graph,forest);
    testInsertEdge(5,12,graph,forest);
    testInsertEdge(12,15,graph,forest);
    testInsertEdge(9,18,graph,forest);
    testInsertEdge(9,14,graph,forest);
    testInsertEdge(2,7,graph,forest);
    testInsertEdge(18,12,graph,forest);
    testInsertEdge(11,6,graph,forest);
    testInsertEdge(12,2,graph,forest);
    testInsertEdge(10,11,graph,forest);
    testInsertEdge(11,4,graph,forest);
    testInsertEdge(18,10,graph,forest);
    testInsertEdge(14,8,graph,forest);
    testInsertEdge(8,16,graph,forest);
    testInsertEdge(7,14,graph,forest);
    testInsertEdge(2,4,graph,forest);
    testInsertEdge(17,9,graph,forest);
    testInsertEdge(17,3,graph,forest);
    testInsertEdge(9,7,graph,forest);
    testInsertEdge(13,9,graph,forest);
    testInsertEdge(16,10,graph,forest);
    testInsertEdge(17,6,graph,forest);
    testInsertEdge(8,3,graph,forest);
    testInsertEdge(8,4,graph,forest);
    testInsertEdge(2,1,graph,forest);
    testInsertEdge(9,0,graph,forest);
    testInsertEdge(16,3,graph,forest);
    testInsertEdge(10,12,graph,forest);
    testInsertEdge(15,10,graph,forest);
    testInsertEdge(10,1,graph,forest);
    testInsertEdge(6,0,graph,forest);
    testInsertEdge(0,3,graph,forest);
    testInsertEdge(14,16,graph,forest);
    testInsertEdge(12,16,graph,forest);
    testInsertEdge(17,2,graph,forest);
    testInsertEdge(3,13,graph,forest);
    testInsertEdge(10,13,graph,forest);
    testInsertEdge(6,12,graph,forest);
    testInsertEdge(5,15,graph,forest);
    testInsertEdge(5,2,graph,forest);
    testInsertEdge(2,16,graph,forest);
    testInsertEdge(16,5,graph,forest);
    testInsertEdge(12,13,graph,forest);
    testInsertEdge(0,8,graph,forest);
    testInsertEdge(11,16,graph,forest);
    testInsertEdge(1,16,graph,forest);
    testInsertEdge(1,11,graph,forest);
    testInsertEdge(14,4,graph,forest);
    testInsertEdge(7,7,graph,forest);
    testInsertEdge(18,15,graph,forest);
    testInsertEdge(12,9,graph,forest);
    testInsertEdge(15,16,graph,forest);
    testInsertEdge(0,12,graph,forest);
    testInsertEdge(18,17,graph,forest);
    testInsertEdge(11,15,graph,forest);
    testInsertEdge(2,11,graph,forest);
    testInsertEdge(9,10,graph,forest);
    testInsertEdge(8,18,graph,forest);
    testInsertEdge(11,18,graph,forest);
    testInsertEdge(6,1,graph,forest);
    testInsertEdge(17,7,graph,forest);
    testInsertEdge(5,7,graph,forest);
    testInsertEdge(0,5,graph,forest);
    testInsertEdge(15,6,graph,forest);
    testInsertEdge(1,7,graph,forest);
    testInsertEdge(14,0,graph,forest);
    testInsertEdge(17,0,graph,forest);
    testInsertEdge(1,17,graph,forest);
    testInsertEdge(18,6,graph,forest);
    testInsertEdge(6,4,graph,forest);
    testInsertEdge(16,16,graph,forest);
    testInsertEdge(0,15,graph,forest);
    testInsertEdge(16,0,graph,forest);
    testInsertEdge(10,0,graph,forest);
    testInsertEdge(10,17,graph,forest);
    testInsertEdge(18,13,graph,forest);
    testInsertEdge(3,11,graph,forest);
    testInsertEdge(8,15,graph,forest);
    testInsertEdge(15,4,graph,forest);
    testInsertEdge(18,1,graph,forest);
    testInsertEdge(6,9,graph,forest);
    testInsertEdge(5,17,graph,forest);
    testInsertEdge(1,5,graph,forest);
    testInsertEdge(2,13,graph,forest);
    testInsertEdge(4,10,graph,forest);
    testInsertEdge(17,15,graph,forest);
    testInsertEdge(4,3,graph,forest);
    testInsertEdge(18,14,graph,forest);
    testInsertEdge(2,8,graph,forest);
    testInsertEdge(12,4,graph,forest);
    testInsertEdge(16,7,graph,forest);
    testInsertEdge(2,9,graph,forest);
    testInsertEdge(18,7,graph,forest);
    testInsertEdge(7,10,graph,forest);
    testInsertEdge(15,13,graph,forest);
    testInsertEdge(5,13,graph,forest);
    testInsertEdge(6,13,graph,forest);
    testInsertEdge(17,13,graph,forest);
    testInsertEdge(18,16,graph,forest);
    testInsertEdge(12,17,graph,forest);
    testInsertEdge(17,11,graph,forest);
    testInsertEdge(9,9,graph,forest);
    testInsertEdge(1,4,graph,forest);
    testInsertEdge(12,8,graph,forest);
    testInsertEdge(11,13,graph,forest);
    testInsertEdge(6,5,graph,forest);
    testInsertEdge(4,13,graph,forest);
    testInsertEdge(7,4,graph,forest);
    testInsertEdge(7,6,graph,forest);
    testInsertEdge(8,11,graph,forest);
    testInsertEdge(9,8,graph,forest);
    testInsertEdge(10,3,graph,forest);
    testInsertEdge(14,2,graph,forest);
    testInsertEdge(9,15,graph,forest);
    testInsertEdge(5,14,graph,forest);
    testInsertEdge(10,14,graph,forest);
    testInsertEdge(5,11,graph,forest);
    testInsertEdge(11,12,graph,forest);
    testInsertEdge(1,14,graph,forest);
    testInsertEdge(16,4,graph,forest);
    testInsertEdge(6,3,graph,forest);

    testRemoveEdge(18,15,graph,forest);
    testRemoveEdge(8,5,graph,forest);
    testRemoveEdge(14,17,graph,forest);
    testRemoveEdge(8,7,graph,forest);
}

TEST(DeleteTest, thirdTest){
    DecGraph graph(20);
    ETForest forest(20);

    testInsertEdge(15,6,graph,forest);
    testInsertEdge(0,6,graph,forest);
    testInsertEdge(10,15,graph,forest);
    testInsertEdge(0,12,graph,forest);
    testInsertEdge(5,0,graph,forest);
    testInsertEdge(13,5,graph,forest);
    testInsertEdge(4,12,graph,forest);
    testInsertEdge(16,5,graph,forest);
    testInsertEdge(9,11,graph,forest);
    testInsertEdge(8,14,graph,forest);
    testInsertEdge(18,14,graph,forest);
    testInsertEdge(9,1,graph,forest);
    testInsertEdge(7,9,graph,forest);
    testInsertEdge(14,6,graph,forest);
    testInsertEdge(5,10,graph,forest);
    testInsertEdge(6,12,graph,forest);
    testInsertEdge(13,11,graph,forest);
    testInsertEdge(12,8,graph,forest);
    testInsertEdge(11,7,graph,forest);
    testInsertEdge(16,4,graph,forest);
    testInsertEdge(12,9,graph,forest);
    testInsertEdge(18,7,graph,forest);
    testInsertEdge(1,5,graph,forest);
    testInsertEdge(2,13,graph,forest);
    testInsertEdge(14,0,graph,forest);
    testInsertEdge(14,2,graph,forest);
    testInsertEdge(11,16,graph,forest);
    testInsertEdge(2,8,graph,forest);
    testInsertEdge(4,18,graph,forest);
    testInsertEdge(3,14,graph,forest);
    testInsertEdge(4,11,graph,forest);
    testInsertEdge(8,17,graph,forest);
    testInsertEdge(1,12,graph,forest);
    testInsertEdge(1,15,graph,forest);
    testInsertEdge(6,2,graph,forest);
    testInsertEdge(10,4,graph,forest);
    testInsertEdge(4,1,graph,forest);
    testInsertEdge(10,6,graph,forest);
    testInsertEdge(0,4,graph,forest);
    testInsertEdge(3,0,graph,forest);
    testInsertEdge(3,17,graph,forest);
    testInsertEdge(17,15,graph,forest);
    testInsertEdge(7,10,graph,forest);
    testInsertEdge(12,13,graph,forest);
    testInsertEdge(7,0,graph,forest);
    testInsertEdge(10,0,graph,forest);
    testInsertEdge(12,18,graph,forest);
    testInsertEdge(2,7,graph,forest);
    testInsertEdge(13,14,graph,forest);
    testInsertEdge(3,6,graph,forest);
    testInsertEdge(4,2,graph,forest);
    testInsertEdge(5,2,graph,forest);
    testInsertEdge(11,10,graph,forest);
    testInsertEdge(14,11,graph,forest);
    testInsertEdge(5,6,graph,forest);
    testInsertEdge(10,8,graph,forest);
    testInsertEdge(14,5,graph,forest);
    testInsertEdge(12,10,graph,forest);
    testInsertEdge(17,1,graph,forest);
    testInsertEdge(10,3,graph,forest);
    testInsertEdge(9,16,graph,forest);
    testInsertEdge(0,8,graph,forest);
    testInsertEdge(8,15,graph,forest);
    testInsertEdge(8,1,graph,forest);
    testInsertEdge(14,4,graph,forest);
    testInsertEdge(7,13,graph,forest);
    testInsertEdge(17,5,graph,forest);
    testInsertEdge(18,3,graph,forest);
    testInsertEdge(6,9,graph,forest);
    testInsertEdge(0,13,graph,forest);
    testInsertEdge(8,3,graph,forest);
    testInsertEdge(11,17,graph,forest);
    testInsertEdge(15,6,graph,forest);
    testInsertEdge(12,7,graph,forest);
    testInsertEdge(17,13,graph,forest);
    testInsertEdge(6,7,graph,forest);
    testInsertEdge(0,2,graph,forest);
    testInsertEdge(11,1,graph,forest);
    testInsertEdge(18,9,graph,forest);
    testInsertEdge(13,10,graph,forest);
    testInsertEdge(15,18,graph,forest);
    testInsertEdge(16,0,graph,forest);
    testInsertEdge(12,14,graph,forest);
    testInsertEdge(17,7,graph,forest);
    testInsertEdge(4,9,graph,forest);
    testInsertEdge(11,5,graph,forest);
    testInsertEdge(7,8,graph,forest);
    testInsertEdge(16,13,graph,forest);
    testInsertEdge(0,15,graph,forest);
    testInsertEdge(9,5,graph,forest);
    testInsertEdge(6,1,graph,forest);
    testInsertEdge(2,11,graph,forest);
    testInsertEdge(7,14,graph,forest);
    testInsertEdge(16,17,graph,forest);
    testInsertEdge(0,11,graph,forest);
    testInsertEdge(12,16,graph,forest);
    testInsertEdge(18,11,graph,forest);
    testInsertEdge(13,1,graph,forest);
    testInsertEdge(3,15,graph,forest);
    testInsertEdge(16,14,graph,forest);
    testInsertEdge(18,17,graph,forest);
    testInsertEdge(5,12,graph,forest);
    testInsertEdge(18,8,graph,forest);
    testInsertEdge(14,1,graph,forest);
    testInsertEdge(3,3,graph,forest);
    testInsertEdge(9,15,graph,forest);
    testInsertEdge(15,2,graph,forest);
    testInsertEdge(16,3,graph,forest);
    testInsertEdge(2,12,graph,forest);
    testInsertEdge(1,0,graph,forest);
    testInsertEdge(6,11,graph,forest);
    testInsertEdge(2,1,graph,forest);
    testInsertEdge(16,2,graph,forest);
    testInsertEdge(9,17,graph,forest);
    testInsertEdge(11,15,graph,forest);
    testInsertEdge(14,15,graph,forest);
    testInsertEdge(11,3,graph,forest);
    testInsertEdge(17,6,graph,forest);
    testInsertEdge(14,14,graph,forest);
    testInsertEdge(2,18,graph,forest);
    testInsertEdge(5,18,graph,forest);
    testInsertEdge(2,3,graph,forest);
    testInsertEdge(6,13,graph,forest);
    testInsertEdge(8,16,graph,forest);
    testInsertEdge(3,7,graph,forest);
    testInsertEdge(5,5,graph,forest);
    testInsertEdge(8,11,graph,forest);
    testInsertEdge(13,8,graph,forest);
    testInsertEdge(7,15,graph,forest);
    testInsertEdge(14,17,graph,forest);
    testInsertEdge(10,16,graph,forest);
    testInsertEdge(8,5,graph,forest);
    testInsertEdge(15,12,graph,forest);
    testInsertEdge(17,2,graph,forest);
    testInsertEdge(17,4,graph,forest);
    testInsertEdge(18,16,graph,forest);
    testInsertEdge(3,4,graph,forest);
    testInsertEdge(1,10,graph,forest);
    testInsertEdge(3,12,graph,forest);
    testInsertEdge(6,8,graph,forest);

    testInsertEdge(13,15,graph,forest);
    testInsertEdge(12,12,graph,forest);

    testInsertEdge(0,9,graph,forest);
    testInsertEdge(18,13,graph,forest);

    testInsertEdge(8,8,graph,forest);
    testInsertEdge(6,4,graph,forest);

    testInsertEdge(4,13,graph,forest);
    testInsertEdge(5,3,graph,forest);
    testInsertEdge(1,1,graph,forest);
    testInsertEdge(6,18,graph,forest);
    testInsertEdge(10,2,graph,forest);
    testInsertEdge(9,14,graph,forest);

    testRemoveEdge(10,15,graph,forest);
//    query :6 - 5
//    query :0 - 5
//    torles :10 - 15
//Expression: pNode == lastPNode
}
TEST(DeleteTest, ConnectionProblem){
    DecGraph graph(20);
    ETForest forest(20);

    testInsertEdge(4,9,graph,forest);
    testInsertEdge(13,5,graph,forest);
    testInsertEdge(11,2,graph,forest);
    testInsertEdge(14,8,graph,forest);
    testInsertEdge(8,17,graph,forest);
    testInsertEdge(6,9,graph,forest);
    testInsertEdge(12,15,graph,forest);
    testInsertEdge(13,8,graph,forest);
    testInsertEdge(1,13,graph,forest);
    testInsertEdge(9,7,graph,forest);
    testInsertEdge(1,12,graph,forest);
    testInsertEdge(18,12,graph,forest);
    testInsertEdge(17,16,graph,forest);
    testInsertEdge(0,14,graph,forest);
    testInsertEdge(12,10,graph,forest);
    testInsertEdge(10,9,graph,forest);
    testInsertEdge(9,13,graph,forest);
    testInsertEdge(8,9,graph,forest);
    testInsertEdge(6,16,graph,forest);
    testInsertEdge(13,3,graph,forest);
    testInsertEdge(1,0,graph,forest);
    testInsertEdge(18,5,graph,forest);
    testInsertEdge(1,2,graph,forest);
    testInsertEdge(7,12,graph,forest);
    testInsertEdge(11,16,graph,forest);
    testInsertEdge(10,2,graph,forest);
    testInsertEdge(3,11,graph,forest);
    testInsertEdge(9,3,graph,forest);
    testInsertEdge(9,1,graph,forest);
    testInsertEdge(14,16,graph,forest);
    testInsertEdge(8,10,graph,forest);
    testInsertEdge(16,5,graph,forest);
    testInsertEdge(17,13,graph,forest);
    testInsertEdge(0,16,graph,forest);
    testInsertEdge(8,18,graph,forest);
    testInsertEdge(6,13,graph,forest);
    testInsertEdge(3,2,graph,forest);
    testInsertEdge(11,1,graph,forest);
    testInsertEdge(8,16,graph,forest);
    testInsertEdge(18,1,graph,forest);
    testInsertEdge(2,5,graph,forest);
    testInsertEdge(10,14,graph,forest);
    testInsertEdge(11,18,graph,forest);
    testInsertEdge(1,10,graph,forest);
    testInsertEdge(7,1,graph,forest);
    testInsertEdge(4,1,graph,forest);
    testInsertEdge(3,16,graph,forest);
    testInsertEdge(5,1,graph,forest);
    testInsertEdge(18,4,graph,forest);
    testInsertEdge(9,16,graph,forest);
    testInsertEdge(15,0,graph,forest);
    testInsertEdge(7,16,graph,forest);
    testInsertEdge(12,4,graph,forest);
    testInsertEdge(11,7,graph,forest);
    testInsertEdge(10,6,graph,forest);
    testInsertEdge(9,12,graph,forest);
    testInsertEdge(2,12,graph,forest);
    testInsertEdge(1,15,graph,forest);
    testInsertEdge(12,14,graph,forest);
    testInsertEdge(13,2,graph,forest);
    testInsertEdge(5,3,graph,forest);
    testInsertEdge(9,5,graph,forest);
    testInsertEdge(4,17,graph,forest);
    testInsertEdge(5,0,graph,forest);
    testInsertEdge(0,17,graph,forest);
    testInsertEdge(13,7,graph,forest);
    testInsertEdge(16,4,graph,forest);
    testInsertEdge(11,8,graph,forest);
    testInsertEdge(15,3,graph,forest);
    testInsertEdge(3,17,graph,forest);
    testInsertEdge(18,3,graph,forest);
    testInsertEdge(12,6,graph,forest);
    testInsertEdge(13,12,graph,forest);
    testInsertEdge(2,15,graph,forest);
    testInsertEdge(12,16,graph,forest);
    testInsertEdge(14,4,graph,forest);
    testInsertEdge(10,15,graph,forest);
    testInsertEdge(14,15,graph,forest);
    testInsertEdge(17,1,graph,forest);
    testInsertEdge(14,9,graph,forest);
    testInsertEdge(16,10,graph,forest);
    testInsertEdge(8,4,graph,forest);
    testInsertEdge(13,18,graph,forest);
    testInsertEdge(13,14,graph,forest);
    testInsertEdge(14,18,graph,forest);
    testInsertEdge(12,17,graph,forest);
    testInsertEdge(11,9,graph,forest);
    testInsertEdge(2,4,graph,forest);
    testInsertEdge(17,7,graph,forest);
    testInsertEdge(15,13,graph,forest);
    testInsertEdge(14,11,graph,forest);
    testInsertEdge(15,18,graph,forest);
    testInsertEdge(11,12,graph,forest);
    testInsertEdge(11,17,graph,forest);
    testInsertEdge(11,4,graph,forest);
    testInsertEdge(1,3,graph,forest);
    testInsertEdge(15,5,graph,forest);
    testInsertEdge(17,10,graph,forest);
    testInsertEdge(13,11,graph,forest);
    testInsertEdge(3,10,graph,forest);
    testInsertEdge(15,8,graph,forest);
    testInsertEdge(5,4,graph,forest);
    testInsertEdge(15,16,graph,forest);
    testInsertEdge(7,2,graph,forest);
    testInsertEdge(11,15,graph,forest);
    testInsertEdge(2,16,graph,forest);
    testInsertEdge(7,4,graph,forest);
    testInsertEdge(5,8,graph,forest);
    testInsertEdge(7,15,graph,forest);
    testInsertEdge(0,2,graph,forest);
    testInsertEdge(12,5,graph,forest);
    testInsertEdge(2,8,graph,forest);
    testInsertEdge(18,10,graph,forest);
    testInsertEdge(4,9,graph,forest);
    testInsertEdge(16,1,graph,forest);
    testInsertEdge(13,0,graph,forest);
    testInsertEdge(3,8,graph,forest);
    testInsertEdge(6,0,graph,forest);
    testInsertEdge(12,3,graph,forest);
    testInsertEdge(6,4,graph,forest);
    testInsertEdge(15,4,graph,forest);
    testInsertEdge(9,2,graph,forest);
    testInsertEdge(0,11,graph,forest);
    testInsertEdge(0,4,graph,forest);
    testInsertEdge(17,14,graph,forest);
    testInsertEdge(2,17,graph,forest);
    testInsertEdge(13,16,graph,forest);
    testInsertEdge(9,0,graph,forest);
    testInsertEdge(6,15,graph,forest);
    testInsertEdge(0,18,graph,forest);
    testInsertEdge(6,14,graph,forest);
    testInsertEdge(5,6,graph,forest);
    testInsertEdge(7,0,graph,forest);
    testInsertEdge(1,14,graph,forest);
    testInsertEdge(12,0,graph,forest);
    testInsertEdge(6,18,graph,forest);
    testInsertEdge(17,9,graph,forest);
    testInsertEdge(3,6,graph,forest);
    testInsertEdge(13,4,graph,forest);
    testInsertEdge(18,9,graph,forest);
    testInsertEdge(7,8,graph,forest);
    testInsertEdge(6,2,graph,forest);
    testInsertEdge(6,8,graph,forest);
    testInsertEdge(6,7,graph,forest);
    testInsertEdge(18,7,graph,forest);
    testInsertEdge(10,13,graph,forest);
    testInsertEdge(11,5,graph,forest);
    testInsertEdge(8,12,graph,forest);
    testInsertEdge(16,18,graph,forest);
    testInsertEdge(5,10,graph,forest);
    testInsertEdge(1,6,graph,forest);
    testInsertEdge(6,11,graph,forest);

    testRemoveEdge(1,13,graph,forest);
    EXPECT_TRUE(graph.connected(1,13,forest));
}