//
// Created by Alex on 2018. 08. 10..
//

#include "gtest/gtest.h"
#include "../src/TestETT.h"
#include "../src/DecrementalGraph.h"
#include "../src/ETTQueries.h"



void testInsertEdge(int x, int y, DecGraph graph, ETForest forest){
    graph.insert(x,y,forest);
    forest.verifyFirstLast();
    forest.verify2SideConnection();
    EXPECT_TRUE(forest.verifyProperties(forest.findRoot(x)));
    EXPECT_TRUE(forest.verifyProperties(forest.findRoot(y)));
    EXPECT_TRUE(graph.connected(x,y, forest));
}

void hitBreakPoint(int x, int y, DecGraph graph, ETForest forest){
    bid = true;
    testInsertEdge(x,y,graph,forest);
    bid = false;
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

    testInsertEdge(3,4,graph,forest);
    testInsertEdge(3,7,graph,forest);
    testInsertEdge(6,4,graph,forest);
    testInsertEdge(1,0,graph,forest);
    testInsertEdge(8,6,graph,forest);
}
TEST(InsertTest, ConnectedAfterInsert){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(1,3,graph,forest);
    testInsertEdge(0,6,graph,forest);
    testInsertEdge(6,3,graph,forest);
    testInsertEdge(1,5,graph,forest);
    testInsertEdge(5,7,graph,forest);
    testInsertEdge(4,8,graph,forest);
    testInsertEdge(4,5,graph,forest);
    testInsertEdge(1,7,graph,forest);
    testInsertEdge(0,1,graph,forest);
    testInsertEdge(8,3,graph,forest);
}
TEST(InsertTest, InfiniteLoopTest_1){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(4,8,graph,forest);
    testInsertEdge(4,3,graph,forest);
    testInsertEdge(0,5,graph,forest);
    testInsertEdge(1,5,graph,forest);
    testInsertEdge(3,0,graph,forest);
    testInsertEdge(8,6,graph,forest);
}
TEST(InsertTest, InfiniteLoopTest_2){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(6,2,graph,forest);
    testInsertEdge(8,7,graph,forest);
    testInsertEdge(0,8,graph,forest);
    testInsertEdge(2,1,graph,forest);
    testInsertEdge(0,1,graph,forest);
    testInsertEdge(3,5,graph,forest);
    testInsertEdge(6,8,graph,forest);
    testInsertEdge(1,7,graph,forest);
    testInsertEdge(7,4,graph,forest);
    testInsertEdge(7,0,graph,forest);
    testInsertEdge(5,6,graph,forest);
}
TEST(InsertTest, InfiniteLoopTest_3) {
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(4,5,graph,forest);
    testInsertEdge(0,6,graph,forest);
    testInsertEdge(0,5,graph,forest);
    testInsertEdge(2,1,graph,forest);
    testInsertEdge(5,1,graph,forest);
    testInsertEdge(2,0,graph,forest);
    testInsertEdge(3,2,graph,forest);
    testInsertEdge(4,6,graph,forest);
    testInsertEdge(4,4,graph,forest);
    testInsertEdge(0,1,graph,forest);
    testInsertEdge(7,0,graph,forest);
    testInsertEdge(4,7,graph,forest);
    testInsertEdge(2,5,graph,forest);
    testInsertEdge(5,7,graph,forest);
    testInsertEdge(7,3,graph,forest);
    testInsertEdge(5,6,graph,forest);
    testInsertEdge(4,8,graph,forest);
}
TEST(InsertTest, BlackHeightTest_1){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(7,8,graph,forest);
    testInsertEdge(5,7,graph,forest);
    testInsertEdge(8,0,graph,forest);
    testInsertEdge(7,0,graph,forest);
    testInsertEdge(3,7,graph,forest);
    testInsertEdge(6,2,graph,forest);
    testInsertEdge(4,7,graph,forest);
    testInsertEdge(8,5,graph,forest);
    testInsertEdge(2,7,graph,forest);
    testInsertEdge(7,1,graph,forest);
}
TEST(InsertTest, BlackHeightTest_2){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(3,1,graph,forest);
    testInsertEdge(8,3,graph,forest);
    testInsertEdge(3,7,graph,forest);
    testInsertEdge(6,4,graph,forest);
    testInsertEdge(3,6,graph,forest);
    testInsertEdge(4,5,graph,forest);
    testInsertEdge(5,8,graph,forest);
    testInsertEdge(4,2,graph,forest);
    testInsertEdge(1,4,graph,forest);
    testInsertEdge(0,3,graph,forest);
}
TEST(InsertTest, BlackHeightTest_3){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(4,3,graph,forest);
    testInsertEdge(6,5,graph,forest);
    testInsertEdge(3,0,graph,forest);
    testInsertEdge(7,0,graph,forest);
    testInsertEdge(1,7,graph,forest);
    testInsertEdge(8,7,graph,forest);
    testInsertEdge(8,5,graph,forest);
    testInsertEdge(8,2,graph,forest);
}
TEST(InsertTest, nullptrderef){
    DecGraph graph(10);
    ETForest forest(10);

    testInsertEdge(8,1,graph,forest);
    testInsertEdge(7,8,graph,forest);
    testInsertEdge(5,2,graph,forest);
    testInsertEdge(0,6,graph,forest);
    testInsertEdge(5,6,graph,forest);
    testInsertEdge(3,5,graph,forest);
    testInsertEdge(7,6,graph,forest);
    testInsertEdge(0,8,graph,forest);
    testInsertEdge(4,8,graph,forest);
}
TEST(InsertTest, DISABLED_lastseenfail){
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
    hitBreakPoint(51,42,graph,forest);
}