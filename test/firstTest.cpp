//
// Created by Alex on 2018. 08. 10..
//

#include "gtest/gtest.h"
#include "../src/TestETT.h"

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

    //TODO: ha a törlés kitörölné a node-ot, majd nullptrre állítaná, akkor tesztelhető lenne
    //ETForest::newDelete(a1);
    //EXPECT_TRUE(a1 == nullptr);
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
    forest.insert(3,4);
    EXPECT_TRUE(forest.logN == 4);
    EXPECT_TRUE(forest.contains(3,4));
    forest.insert(3,5);
    EXPECT_TRUE(forest.contains(3,5));
    forest.insert(3,8);
    EXPECT_TRUE(forest.contains(3,8));
}
