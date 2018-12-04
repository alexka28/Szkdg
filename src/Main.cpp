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
#include "TestETT.h"
#include <cassert>
#include <cmath>
#include "ETTQueries.h"
#include <ctime>

using namespace std;

int main() {
    testInsert(250, 50);
    testDelete(250, 50);
    //testDeleteWithVerify(100,10);
    return 0;
}
