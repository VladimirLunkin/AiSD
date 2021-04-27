#ifndef DZ3_TRAVERSAL_H
#define DZ3_TRAVERSAL_H

#include "IGraph.h"


void dfs(const IGraph &graph, void (*callback)(int v));
void bfs(const IGraph &graph, void (*callback)(int v));

int numberOfShortestPaths(const IGraph &graph, int from, int to);


#endif //DZ3_TRAVERSAL_H
