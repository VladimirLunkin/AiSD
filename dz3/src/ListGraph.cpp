#include "ListGraph.h"


ListGraph::ListGraph(size_t verticesCount)
    : graph_(verticesCount, std::vector<int>()) {}

ListGraph::ListGraph(const IGraph &graph)
    : ListGraph(graph.verticesCount()) {
    for (int i = 0; i < graph_.size(); ++i) {
        graph_[i] = graph.getNextVertices(i);
    }
}

void ListGraph::addEdge(int from, int to) {
    graph_[from].push_back(to);
}

size_t ListGraph::verticesCount() const {
    return graph_.size();
}

std::vector<int> ListGraph::getNextVertices(int vertex) const {
    std::vector<int> result(graph_[vertex].size());
    std::copy(graph_[vertex].begin(), graph_[vertex].end(), result.begin());
    return result;
}

std::vector<int> ListGraph::getPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < graph_.size(); ++i) {
        for (auto child : graph_[i]) {
            if (vertex == child) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}
