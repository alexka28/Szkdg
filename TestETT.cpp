//
// Created by Alex on 2018. 07. 28..
//

#include "TestETT.h"
#include <iostream>

int TestETT::compare(const ETTreeNode *sample, const ETTreeNode *normal) {
    int result = 0;
    std::list<Node> sampleNodes;
    std::list<Node> normalTreeNodes;
    std::map<const ETTreeNode *, int> normalTreeNodeAdresses;

    inOrderSampleTree(sample, sampleNodes);
    inOrderNormalTree(normal, normalTreeNodes, normalTreeNodeAdresses, result);

    if (result == -2) {
        std::cout << "vegtelen ciklus vagy azonos memoriacimu node van a faban!" << std::endl;
    } else if (sampleNodes.size() != normalTreeNodes.size()) {
        result = -1;
        std::cout << "a ket fa merete nem egyenlo! elso fa: " << sampleNodes.size() << " masodik fa: "
                  << normalTreeNodes.size() << std::endl;
    } else {
        auto sampleIt = sampleNodes.begin();
        auto normalIt = normalTreeNodes.begin();
        for (; sampleIt != sampleNodes.end(); sampleIt++, normalIt++) {
            if (sampleIt->color != normalIt->color || sampleIt->nodeId != normalIt->nodeId ||
                sampleIt->rank != normalIt->rank) {
                result = -1;
                std::cout << "egy node tulajdonsagai nem egyeznek!" << std::endl;
                break;
            }
        }
    }
    return result;
}

void TestETT::inOrderSampleTree(const ETTreeNode *sample, std::list<Node> &nodes) {
    if (sample != nullptr && sample != &theNullNode && sample->left != &theNullNode) {
        inOrderSampleTree(sample->left, nodes);
    }
    if (sample != nullptr) {
        Node tmp;
        tmp.nodeId = sample->nodeId;
        tmp.rank = sample->rank;
        tmp.color = sample->color;
        nodes.push_back(tmp);
    }

    if (sample != nullptr && sample != &theNullNode && sample->right != &theNullNode) {
        inOrderSampleTree(sample->right, nodes);
    }
}

void TestETT::inOrderNormalTree(const ETTreeNode *pNode, std::list<TestETT::Node> &nodes,
                                std::map<const ETTreeNode *, int> &adresses, int &result) {
    if (pNode != nullptr && pNode != &theNullNode && pNode->left != &theNullNode && result != -2) {
        if (adresses.count(pNode) > 0) {
            int tmp = adresses.find(pNode)->second;
            if (tmp > 3) {
                result = -2;
                return;
            } else {
                adresses.erase(pNode);
                adresses.insert(std::pair<const ETTreeNode *, int>(pNode, tmp + 1));
            }
        } else {
            adresses.insert(std::pair<const ETTreeNode *, int>(pNode, 1));
        }
        inOrderNormalTree(pNode->left, nodes, adresses, result);
    }
    if (pNode != nullptr && result != -2) {
        Node tmp;
        tmp.nodeId = pNode->nodeId;
        tmp.rank = pNode->rank;
        tmp.color = pNode->color;
        nodes.push_back(tmp);
        if (adresses.count(pNode) > 0) {
            int tmp = adresses.find(pNode)->second;
            if (tmp > 3) {
                result = -2;
                return;
            } else {
                adresses.erase(pNode);
                adresses.insert(std::pair<const ETTreeNode *, int>(pNode, tmp + 1));
            }
        } else {
            adresses.insert(std::pair<const ETTreeNode *, int>(pNode, 1));
        }
    }

    if (pNode != nullptr && pNode != &theNullNode && pNode->right != &theNullNode && result != -2) {
        if (adresses.count(pNode) > 0) {
            int tmp = adresses.find(pNode)->second;
            if (tmp > 3) {
                result = -2;
                return;
            } else {
                adresses.erase(pNode);
                adresses.insert(std::pair<const ETTreeNode *, int>(pNode, tmp + 1));
            }
        } else {
            adresses.insert(std::pair<const ETTreeNode *, int>(pNode, 1));
        }
        inOrderNormalTree(pNode->right, nodes, adresses, result);
    }

}


const ETTreeNode *TestETT::findRootForTest(const ETTreeNode *u) {

    const ETTreeNode *pNode = u;
    while (pNode->parent != nullptr) {

        pNode = pNode->parent;

    }

    return pNode;
}

