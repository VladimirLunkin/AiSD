#include "ArcGraph.h"

ArcGraph::ArcGraph(size_t verticesCount)
    : verticesCount_(verticesCount) {}

ArcGraph::ArcGraph(const IGraph &graph)
    : ArcGraph(graph.verticesCount()) {
    for (int i = 0; i < graph_.size(); ++i) {
        std::vector<int> row = graph.getNextVertices(i);
        for (int j : row) {
            graph_.emplace_back(i, j);
        }
    }
}

void ArcGraph::addEdge(int from, int to) {
    graph_.emplace_back(from, to);
}

size_t ArcGraph::verticesCount() const {
    return verticesCount_;
}

std::vector<int> ArcGraph::getNextVertices(int vertex) const {
    std::vector<int> result;
    for (const auto & i : graph_) {
        if (i.first == vertex) {
            result.push_back(i.second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::getPrevVertices(int vertex) const {
    std::vector<int> result;
    for (const auto & i : graph_) {
        if (i.second == vertex) {
            result.push_back(i.first);
        }
    }
    return result;
}
