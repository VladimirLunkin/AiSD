#ifndef DZ3_IGRAPH_H
#define DZ3_IGRAPH_H

#include <vector>


struct IGraph {
    virtual ~IGraph() = default;

    virtual void addEdge(int from, int to) = 0;

    virtual size_t verticesCount() const = 0;

    virtual std::vector<int> getNextVertices(int vertex) const = 0;
    virtual std::vector<int> getPrevVertices(int vertex) const = 0;
};


#endif //DZ3_IGRAPH_H
