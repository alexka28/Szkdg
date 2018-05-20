#include "CreateDeleteQuery.h"
#include <time.h>
#include <list>
#include <stdlib.h>

std::list<std::pair<int, int>> fillGraph(int n) {

    int nodeOne, nodeTwo, numInserts;
    numInserts = ((n * (n - 1)) / 2) * 0.8;
    std::list<std::pair<int, int>> insertList;

//80%-osra töltjük fel
    for (int i = 1; i <= numInserts; ++i) {
        nodeOne = rand() % (n - 1);
        nodeTwo = rand() % (n - 1);

        while (nodeOne == nodeTwo) {
            nodeOne = rand() % (n - 1);
            nodeTwo = rand() % (n - 1);
        }
        std::list<std::pair<int, int>>::iterator it;
        for (it = insertList.begin(); it != insertList.end(); ++it) {
            if ((it->first == nodeOne && it->second == nodeTwo) || (it->first == nodeTwo && it->second == nodeOne)) {
                nodeOne = rand() % (n - 1);
                nodeTwo = rand() % (n - 1);
                it = insertList.begin();
            }
        }
        std::pair<int, int> edge(nodeOne, nodeTwo);
        insertList.push_back(edge);

    }
    return insertList;
}

std::list<std::pair<std::pair<int, int>, int>> createDQ(std::list<std::pair<int, int>> insertList, int n) {
    int numDel = 0;
    int r;
    std::list<std::pair<int, int>>::iterator it;
    it = insertList.begin();
    int nodeOne, nodeTwo;
    //egy él és a hozzá kapcsolódó művelet 0 delete, 1 query
    std::list<std::pair<std::pair<int, int>, int>> result;
//amíg nincs meg az 50% delete
    while (it != insertList.end()) {
        r = rand() % 10 + 1;
        //ebben az esetben töröljünk
        if (r <= 5) {
result.push_back(std::make_pair(std::make_pair(it->first,it->second),0));
       it++; }
        //query esetén generáljunk egy random élt
        else{
            nodeOne = rand() % (n-1);
            nodeTwo = rand() % (n-1);
            while(nodeOne == nodeTwo){
                nodeOne = rand() % (n-1);
                nodeTwo = rand() % (n-1);
            }
            result.push_back(std::make_pair(std::make_pair(nodeOne,nodeTwo),1));
            it++;
        }
    }
    return result;
}