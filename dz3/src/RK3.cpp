#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct IGraph {
    virtual ~IGraph() = default;

    virtual void addEdge(int from, int to) = 0;

    virtual size_t verticesCount() const = 0;

    virtual std::vector<int> getNextVertices(int vertex) const = 0;
    virtual std::vector<int> getPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t verticesCount);
    ~ListGraph() override = default;

    explicit ListGraph(const IGraph&);

    void addEdge(int from, int to) override;

    size_t verticesCount() const override;

    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> graph_;
};
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

#include <set>

static inline void dfs_aux(const IGraph &graph, int vertex, std::vector<bool> &visited) {
    visited[vertex] = true;

    for (auto child : graph.getNextVertices(vertex)) {
        if (!visited[child]) {
            dfs_aux(graph, child, visited);
        }
    }
}


bool is_hamiltonian_path(const IGraph &graph, const std::vector<int> &path) {
    if (graph.verticesCount() != path.size()) {
        return false;
    }

    std::set<int> s;
    for (auto i : path) {
        s.insert(i);
    }
    if (s.size() != path.size()) {
        return false;
    }

    std::vector<bool> visited(graph.verticesCount(), false);

    int num = 0;

    for (int i = 0; i < graph.verticesCount(); ++i) {
        if (!visited[i]) {
            num++;
            dfs_aux(graph, i, visited);
        }
    }

    return num == 1;
}

int main() {
    size_t v;
    cin >> v;

    size_t n;
    cin >> n;

    ListGraph graph(v);

    for (size_t i = 0; i < n; ++i) {
        int v1;
        int v2;
        std::cin >> v1 >> v2;
        graph.addEdge(v1, v2);
        graph.addEdge(v2, v1);
    }

    cout << numberOfComponents(graph) << endl;

}

