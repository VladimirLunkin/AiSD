#include "WeightedGraph.h"

#include <climits>
#include <set>


WeightedGraph::WeightedGraph(int verticesCount)
        : graph_(verticesCount, std::vector<std::pair<int, int>>()) {}

void WeightedGraph::addEdge(int from, int to, int weight) {
    graph_[from].emplace_back(weight, to);
    graph_[to].emplace_back(weight, from);
}

size_t WeightedGraph::verticesCount() const {
    return graph_.size();
}

std::vector<std::pair<int, int>> WeightedGraph::getNextVertices(int vertex) const {
    std::vector<std::pair<int, int>> result(graph_[vertex].size());
    for (int i = 0; i < graph_[vertex].size(); ++i) {
        result[i] = graph_[vertex][i];
    }
    return result;
}

std::vector<std::pair<int, int>> WeightedGraph::getPrevVertices(int vertex) const {
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < graph_.size(); ++i) {
        for (auto child : graph_[i]) {
            if (vertex == child.second) {
                result.push_back(graph_[vertex][i]);
                break;
            }
        }
    }
    return result;
}


static inline void decreaseKey(std::set<std::pair<int, int>> &queue, int child, int distance, int newDistance) {
    queue.erase(std::pair<int, int>(distance, child));
    queue.emplace(newDistance, child);
}

std::vector<int> dijkstra(const WeightedGraph &graph, int from) {
    std::vector<int> parents(graph.verticesCount(), -1);
    std::vector<int> distance(graph.verticesCount(), INT_MAX);
    distance[from] = 0;
    /// first - длна пути до вершины
    /// second - номер вершины
    std::set<std::pair<int, int>> queue;
    queue.emplace(distance[from], from);

    while (!queue.empty()) {
        std::pair<int, int> edge = move(queue.extract(queue.begin()).value());
        int vertex = edge.second;

        for (auto child : graph.getNextVertices(vertex)) {
            int childVertex = child.second;
            int newDistance = distance[vertex] + child.first;

            if (distance[childVertex] == INT_MAX) {
                distance[childVertex] = newDistance;
                parents[childVertex] = vertex;
                queue.emplace(distance[childVertex], childVertex);
            } else if (distance[childVertex] > newDistance) {
                decreaseKey(queue, childVertex, distance[childVertex], newDistance);

                distance[childVertex] = newDistance;
                parents[childVertex] = vertex;
            }
        }
    }

    return distance;
}
