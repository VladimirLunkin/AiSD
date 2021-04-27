#include "Traversal.h"

#include <queue>


static inline void dfs_aux(const IGraph &graph, int vertex, std::vector<bool> &visited, void (*callback)(int v)) {
    visited[vertex] = true;
    callback(vertex);

    for (auto child : graph.getNextVertices(vertex)) {
        if (!visited[child]) {
            dfs_aux(graph, child, visited, callback);
        }
    }
}

void dfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.verticesCount(), false);

    for (int i = 0; i < graph.verticesCount(); ++i) {
        if (!visited[i]) {
            dfs_aux(graph, i, visited, callback);
        }
    }
}

static inline void bfs_aux(const IGraph &graph, std::queue<int> &queue, std::vector<bool> &visited, void (*callback)(int v)) {
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        callback(vertex);
        for (auto child : graph.getNextVertices(vertex)) {
            if (!visited[child]) {
                queue.push(child);
                visited[child] = true;
            }
        }
    }
}

void bfs(const IGraph &graph, void (*callback)(int v)) {
    std::vector<bool> visited(graph.verticesCount(), false);
    std::queue<int> queue;

    for (int i = 0; i < graph.verticesCount(); ++i) {
        if (!visited[i]) {
            queue.push(i);
            visited[i] = true;
            bfs_aux(graph, queue, visited, callback);
        }
    }
}

int numberOfShortestPaths(const IGraph &graph, int from, int to) {
    /// first - количество кратчайших путей от from до текущей вершины
    /// second - длина кратчайшего пути от from до текущей вершины
    std::vector<std::pair<int, int>> counters(graph.verticesCount(), {0, 0});
    counters[from] = {1, 0};

    std::vector<bool> visited(graph.verticesCount(), false);
    visited[from] = true;

    std::queue<int> queue;
    queue.push(from);

    int layerNumber = 1;
    int viewedInLayer = 0;
    int quantityInNextLayer = 0;
    int quantityInCurrentLayer = 1;

    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        viewedInLayer++;

        for (auto child : graph.getNextVertices(vertex)) {
            if (!visited[child]) {
                counters[child].second = layerNumber;
                visited[child] = true;
                queue.push(child);
                quantityInNextLayer++;
            }

            if (layerNumber == counters[child].second) {
                counters[child].first += counters[vertex].first;
            }
        }

        if (viewedInLayer == quantityInCurrentLayer) {
            quantityInCurrentLayer = quantityInNextLayer;
            quantityInNextLayer = 0;
            viewedInLayer = 0;
            layerNumber++;

            if (counters[to].first != 0) {
                return counters[to].first;
            }
        }
        
    }

    return -1;
}
