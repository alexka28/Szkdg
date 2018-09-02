//
// Created by Alex on 2018. 08. 10..
//

#include "gtest/gtest.h"
#include "../src/TestETT.h"


TEST(CompareTest, CompareTrees) {
    ETTreeNode *a1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 1);
    ETTreeNode *a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 2);
    ETTreeNode *a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;


    ETTreeNode *b1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 1);
    ETTreeNode *b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 2);
    ETTreeNode *b3 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 3);

    b1->left = b2;
    b1->right = b3;

    b2->rank = 0;
    b3->rank = 0;
    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);


}
TEST(CompareTest, CompareUnequalTrees){
    ETTreeNode *a1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 1);
    ETTreeNode *a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 2);
    ETTreeNode *a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;


    ETTreeNode *b1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 1);
    ETTreeNode *b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 2);
    ETTreeNode *b3 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 3);

    b1->left = b2;
    b1->right = b3;

    b2->rank = 0;
    b3->rank = 1;
    EXPECT_FALSE(TestETT::compare(a1,b1) == 0);
}

TEST(BSTDeleteTest, deleteLeaf){
    //Input
    ETTreeNode *a1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 5);
    ETTreeNode *a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 3);
    ETTreeNode *a3 = new ETTreeNode(a1, &theNullNode, &theNullNode, RED, 8);

    a1->left = a2;
    a1->right = a3;

    a2->rank = 0;
    a3->rank = 0;
    //Expected output
    ETTreeNode *b1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 5);
    ETTreeNode *b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, RED, 3);

    b1->left = b2;
    b2->rank = 0;


    ETForest::newDelete(a3);

    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);
    ETForest::newDelete(a2);
    b1->left = &theNullNode;
    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);
    ETForest::newDelete(a1);

    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);

}

TEST(BSTDeleteTest, DeleteOnlyMinThenMax){
    //Input
    ETTreeNode *a1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 10); //10
    ETTreeNode *a2 = new ETTreeNode(a1, &theNullNode, &theNullNode, BLACK, 8); //8
    ETTreeNode *a3 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 6); //6
    ETTreeNode *a4 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 9); //9
    ETTreeNode *a5 = new ETTreeNode(a1, &theNullNode, &theNullNode, BLACK, 15); // 15
    ETTreeNode *a6 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 12); // 12
    ETTreeNode *a7 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 18); // 18

    a1->left = a2;
    a1->right = a5;
    a1->rank = 2;

    a2->left =a3;
    a2->right = a4;
    a2->rank = 1;

    a3->parent = a2;
    a3->rank = 0;

    a4->parent = a2;
    a4->rank = 0;

    a5->left = a6;
    a5->right = a7;
    a5->rank = 1;

    a6->parent = a5;
    a6->rank = 0;

    a7->parent = a5;
    a7->rank = 0;
    //Expected output
    ETTreeNode *b1 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, BLACK, 10); //10
    ETTreeNode *b2 = new ETTreeNode(b1, &theNullNode, &theNullNode, BLACK, 8); //8
    ETTreeNode *b3 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 6); //6
    ETTreeNode *b4 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 9); //9
    ETTreeNode *b5 = new ETTreeNode(b1, &theNullNode, &theNullNode, BLACK, 15); // 15
    ETTreeNode *b6 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 12); // 12
    ETTreeNode *b7 = new ETTreeNode(nullptr, &theNullNode, &theNullNode, RED, 18); // 18

    b1->left = b2;
    b1->right = b5;
    b1->rank = 2;

    b2->left =b3;
    b2->right = b4;
    b2->rank = 1;

    b3->parent = b2;
    b3->rank = 0;

    b4->parent = b2;
    b4->rank = 0;

    b5->left = b6;
    b5->right = b7;
    b5->rank = 1;

    b6->parent = b5;
    b6->rank = 0;

    b7->parent = b5;
    b7->rank = 0;

    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);
    ETForest::newDelete(a3);
    b2->left = &theNullNode;
    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);
    ETForest::newDelete(a2);
    b1->left = b4;
    b4->parent = b1;
    b4->color = BLACK;
    b4->rank = 1;
    EXPECT_TRUE(TestETT::compare(a1,b1) == 0);
}
