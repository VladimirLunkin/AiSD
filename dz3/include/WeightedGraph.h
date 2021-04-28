#ifndef DZ3_WEIGHTEDGRAPH_H
#define DZ3_WEIGHTEDGRAPH_H

#include <vector>


class WeightedGraph {
public:
    WeightedGraph() = delete;
    ~WeightedGraph() = default;

    explicit WeightedGraph(int verticesCount);

    void addEdge(int from, int to, int weight);

    size_t verticesCount() const;

    std::vector<std::pair<int, int>> getNextVertices(int vertex) const;

    std::vector<std::pair<int, int>> getPrevVertices(int vertex) const;

private:
    /// first - длна пути до вершины
    /// second - номер вершины
    std::vector<std::vector<std::pair<int, int>>> graph_;
};

std::vector<int> dijkstra(const WeightedGraph &graph, int from);


#endif //DZ3_WEIGHTEDGRAPH_H
