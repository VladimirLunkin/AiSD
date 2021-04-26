#ifndef DZ3_ARCGRAPH_H
#define DZ3_ARCGRAPH_H

#include "IGraph.h"


class ArcGraph : public IGraph {
public:
    explicit ArcGraph(size_t verticesCount);
    ~ArcGraph() override = default;

    explicit ArcGraph(const IGraph&);

    void addEdge(int from, int to) override;

    size_t verticesCount() const override;

    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> graph_;
    size_t verticesCount_;
};


#endif //DZ3_ARCGRAPH_H
