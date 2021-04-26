#include "SetGraph.h"

SetGraph::SetGraph(size_t verticesCount)
        : graph_(verticesCount, std::set<int>()) {}

SetGraph::SetGraph(const IGraph &graph)
        : SetGraph(graph.verticesCount()) {
    for (int i = 0; i < graph_.size(); ++i) {
        std::vector<int> row = graph.getNextVertices(i);
        for (int j : row) {
            graph_[i].insert(j);
        }
    }
}

void SetGraph::addEdge(int from, int to) {
    graph_[from].insert(to);
}

size_t SetGraph::verticesCount() const {
    return graph_.size();
}

std::vector<int> SetGraph::getNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        if (graph_[vertex].find(i) != graph_[vertex].end()) {
            result.push_back(i);
        }
    }
    return result;
}

std::vector<int> SetGraph::getPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        if (graph_[i].find(vertex) != graph_[i].end()) {
            result.push_back(i);
        }
    }
    return result;
}
