#ifndef DZ3_SETGRAPH_H
#define DZ3_SETGRAPH_H

#include "IGraph.h"

#include <set>


class SetGraph : public IGraph {
public:
    explicit SetGraph(size_t verticesCount);
    ~SetGraph() override = default;

    explicit SetGraph(const IGraph&);

    void addEdge(int from, int to) override;

    size_t verticesCount() const override;

    std::vector<int> getNextVertices(int vertex) const override;
    std::vector<int> getPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> graph_;
};


#endif //DZ3_SETGRAPH_H
