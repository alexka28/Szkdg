#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#include "GraphGen.h"
bool DFSUtil(Graph g, int v, bool visited[], int f, bool *ret);
bool queryGraph(Graph g, int v, int f, bool *ret);
#endif // DFS_H_INCLUDED
