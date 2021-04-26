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

void numberOfShortestPaths(const IGraph &graph, size_t from, size_t to) {
    std::vector<size_t> counters(graph.verticesCount(),0);
    std::vector<bool> visited(graph.verticesCount(), false);
    std::queue<size_t> queue;

    for (size_t i = 0; i < graph.verticesCount(); ++i) {
        size_t vertex = (i + from) % graph.verticesCount();
        if (!visited[vertex]) {
            queue.push(vertex);
            visited[vertex] = true;

            bfs_aux(graph, queue, visited, callback);
        }
    }
}
