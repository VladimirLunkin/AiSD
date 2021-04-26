#ifndef DZ3_LISTGRAPH_H
#define DZ3_LISTGRAPH_H

#include "IGraph.h"


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


#endif  // DZ3_LISTGRAPH_H
