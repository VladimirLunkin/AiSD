#include "Test.h"
#include "WeightedGraph.h"

#include <iostream>

using namespace std;


int main() {
    runTests();

    int v = 0;
    cin >> v;

    WeightedGraph graph(v);

    int n = 0;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int from = 0;
        int to = 0;
        int weight = 0;
        cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }

    int from = 0;
    int to = 0;
    cin >> from >> to;
    vector<int> distance = dijkstra(graph, from);
    cout << distance[to] << endl;

    return 0;
}
/*
6
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2
*/
/*
9
16
0 1 9
0 2 2
0 3 6
1 3 2
1 6 4
2 3 3
2 4 1
3 4 1
3 5 9
3 6 7
4 7 6
5 6 1
5 7 5
5 8 1
6 8 5
7 8 5
0 8
*/
