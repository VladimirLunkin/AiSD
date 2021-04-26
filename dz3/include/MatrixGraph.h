#ifndef DZ3_MATRIXGRAPH_H
#define DZ3_MATRIXGRAPH_H

#include "IGraph.h"


class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t verticesCount);
    ~MatrixGraph() override = default;

    explicit MatrixGraph(const IGraph&);

    void addEdge(int from, int to) override;

    size_t verticesCount() const override;

    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> graph_;
};


#endif //DZ3_MATRIXGRAPH_H
