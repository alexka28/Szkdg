//
// Created by Alex on 2018. 08. 10..
//

#include "gtest/gtest.h"
#include "../src/TestETT.h"

TEST(CompareTest, CompareTrees) {
    auto a1 = new ETTreeNode(BLACK, 1,1);
    auto a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 2);
    auto a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;


    auto b1 = new ETTreeNode(BLACK, 1,1);
    auto b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 2);
    auto b3 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 3);

    b1->left = b2;
    b1->right = b3;

    b2->rank = 0;
    b3->rank = 0;
    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);


}
TEST(CompareTest, CompareUnequalTrees){
    auto a1 = new ETTreeNode(BLACK, 1, 1);
    auto a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 2);
    auto a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;


    auto b1 = new ETTreeNode(BLACK, 1, 1);
    auto b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 2);
    auto b3 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 3);

    b1->left = b2;
    b1->right = b3;

    b2->rank = 0;
    b3->rank = 1;
    EXPECT_FALSE(TestETT::compare(a1,b1) == 0);
}

TEST(BSTDeleteTest, deleteLeaf){
    //Input
    auto a1 = new ETTreeNode(BLACK, 5, 1);
    auto a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);
    auto a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 8);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;

    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(a1));

    ETForest::newDelete(a2);
    EXPECT_TRUE(ETForest::verifyProperties(a1));

    //TODO: ha a törlés kitörölné a node-ot, majd nullptrre állítaná, akkor tesztelhető lenne
    //ETForest::newDelete(a1);
    //EXPECT_TRUE(a1 == nullptr);

}

TEST(BSTDeleteTest, DeleteOnlyMinThenMax){
    //Input
    auto a1 = new ETTreeNode(BLACK, 10, 2); //10
    auto a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, BLACK, 8); //8
    auto a3 = new ETTreeNode(RED, 6, 0); //6
    auto a4 = new ETTreeNode(RED, 9, 0); //9
    auto a5 = new ETTreeNode(a1, &theNullNode, &theNullNode, BLACK, 15); // 15
    auto a6 = new ETTreeNode(RED, 12, 0); // 12
    auto a7 = new ETTreeNode(RED, 18, 0); // 18

    a1->left = a2;
    a1->right = a5;

    a2->left =a3;
    a2->right = a4;
    a2->rank = 1;

    a3->parent = a2;

    a4->parent = a2;

    a5->left = a6;
    a5->right = a7;
    a5->rank = 1;

    a6->parent = a5;

    a7->parent = a5;

    //Verify Input
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));
    //Expected output
    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));

    ETForest::newDelete(a2);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));
}

TEST(BSTDeleteTest, DeleteRoot){
    auto a1 = new ETTreeNode(BLACK, 5, 1);
    auto a2 = new ETTreeNode(RED, 2, 0);
    auto a3 = new ETTreeNode(RED, 1, 0);


    a1->right = a2;
    a1->left = a3;

    a2->parent = a1;

    a3->parent = a1;


    ETForest::newDelete(a1);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a2)));

    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a2)));
}
TEST(BSTDeleteTest, CheckDeleteCase6_Right){
    auto a1 = new ETTreeNode(BLACK, 3, 2);
    auto a2 = new ETTreeNode(BLACK, 4, 1);
    auto a3 = new ETTreeNode(BLACK, 3, 1);
    auto a4 = new ETTreeNode(RED, 7, 0);
    auto a5 = new ETTreeNode(RED, 4, 0);

    a1->left = a2;
    a1->right = a3;

    a2->parent = a1;

    a3->parent = a1;
    a3->left = a4;
    a3->right = a5;

    a4->parent = a3;

    a5->parent = a3;

    //Verify Input
    ETForest::verifyProperties(a1);

    ETForest::newDelete(a2);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));

}
TEST(BSTDeleteTest, CheckDeleteCase6_Left){
    auto a1 = new ETTreeNode(BLACK,3,2);
    auto a2 = new ETTreeNode(BLACK,4,1);
    auto a3 = new ETTreeNode(BLACK, 3,1);
    auto a4 = new ETTreeNode(RED, 7,0);
    auto a5 = new ETTreeNode(RED, 4,0);

    a1->left = a2;
    a1->right = a3;

    a2->parent = a1;
    a2->left = a4;
    a2->right = a5;

    a3->parent = a1;

    a4->parent = a2;

    a5->parent = a2;

    //Verify Input
    ETForest::verifyProperties(a1);

    ETForest::newDelete(a3);
    EXPECT_TRUE(ETForest::verifyProperties(ETForest::findRoot(a1)));

}
