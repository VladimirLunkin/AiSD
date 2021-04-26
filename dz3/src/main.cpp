#include <algorithm>
#include <iostream>
#include <vector>

#include "ArcGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
//#include "SetGraph.h"

using namespace std;

static inline bool find(const vector<int>& v, int item) {
    return find(v.begin(), v.end(), item) != v.end();
}

typedef bool (*test_t)();

bool testList1() {
    ListGraph graph(0);
    return graph.verticesCount() == 0;
}
bool testList2() {
    ListGraph graph(2);
    graph.addEdge(0, 1);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 && p_0.empty() && n_1.empty() && p_1[0] == 0;
}
bool testList3() {
    ListGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(1, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 &&
           p_0[0] == 1 &&
           n_1[0] == 0 &&
           p_1[0] == 0;
}
bool testList4() {
    ListGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(n_0, 2) && p_0.empty() &&
           find(n_1, 2) && find(p_1, 0) &&
           n_2.empty() && find(p_2, 0) && find(p_2, 1);
}
bool testList5() {
    ListGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(p_0, 2) &&
           find(n_1, 2) && find(p_1, 0) &&
           find(n_2, 0) && find(p_2, 1);
}
bool testList6() {
    ListGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(0, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return find(n_0, 1) && find(n_0, 0) && find(p_0, 0) &&
           n_1.empty() && find(p_1, 0);
}
bool testList7() {
    ListGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_4 = graph.getNextVertices(4);
    vector<int> p_4 = graph.getPrevVertices(4);
    vector<int> n_5 = graph.getNextVertices(5);
    vector<int> p_5 = graph.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}
bool testList8() {
    ListGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    MatrixGraph graph_copy(graph);

    vector<int> n_0 = graph_copy.getNextVertices(0);
    vector<int> p_0 = graph_copy.getPrevVertices(0);
    vector<int> n_4 = graph_copy.getNextVertices(4);
    vector<int> p_4 = graph_copy.getPrevVertices(4);
    vector<int> n_5 = graph_copy.getNextVertices(5);
    vector<int> p_5 = graph_copy.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}

bool testMatrix1() {
    MatrixGraph graph(0);
    return graph.verticesCount() == 0;
}
bool testMatrix2() {
    MatrixGraph graph(2);
    graph.addEdge(0, 1);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 && p_0.empty() && n_1.empty() && p_1[0] == 0;
}
bool testMatrix3() {
    MatrixGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(1, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 &&
           p_0[0] == 1 &&
           n_1[0] == 0 &&
           p_1[0] == 0;
}
bool testMatrix4() {
    MatrixGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(n_0, 2) && p_0.empty() &&
           find(n_1, 2) && find(p_1, 0) &&
           n_2.empty() && find(p_2, 0) && find(p_2, 1);
}
bool testMatrix5() {
    MatrixGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(p_0, 2) &&
           find(n_1, 2) && find(p_1, 0) &&
           find(n_2, 0) && find(p_2, 1);
}
bool testMatrix6() {
    MatrixGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(0, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return find(n_0, 1) && find(n_0, 0) && find(p_0, 0) &&
           n_1.empty() && find(p_1, 0);
}
bool testMatrix7() {
    MatrixGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_4 = graph.getNextVertices(4);
    vector<int> p_4 = graph.getPrevVertices(4);
    vector<int> n_5 = graph.getNextVertices(5);
    vector<int> p_5 = graph.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}
/*
bool testMatrix8() {
    MatrixGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    SetGraph graph_copy(graph);

    vector<int> n_0 = graph_copy.getNextVertices(0);
    vector<int> p_0 = graph_copy.getPrevVertices(0);
    vector<int> n_4 = graph_copy.getNextVertices(4);
    vector<int> p_4 = graph_copy.getPrevVertices(4);
    vector<int> n_5 = graph_copy.getNextVertices(5);
    vector<int> p_5 = graph_copy.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}
*/

/*bool testSet1() {
    SetGraph graph(0);
    return graph.verticesCount() == 0;
}
bool testSet2() {
    SetGraph graph(2);
    graph.addEdge(0, 1);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 && p_0.empty() && n_1.empty() && p_1[0] == 0;
}
bool testSet3() {
    SetGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(1, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 &&
           p_0[0] == 1 &&
           n_1[0] == 0 &&
           p_1[0] == 0;
}
bool testSet4() {
    SetGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(n_0, 2) && p_0.empty() &&
           find(n_1, 2) && find(p_1, 0) &&
           n_2.empty() && find(p_2, 0) && find(p_2, 1);
}
bool testSet5() {
    SetGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(p_0, 2) &&
           find(n_1, 2) && find(p_1, 0) &&
           find(n_2, 0) && find(p_2, 1);
}
bool testSet6() {
    SetGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(0, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return find(n_0, 1) && find(n_0, 0) && find(p_0, 0) &&
           n_1.empty() && find(p_1, 0);
}
bool testSet7() {
    SetGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_4 = graph.getNextVertices(4);
    vector<int> p_4 = graph.getPrevVertices(4);
    vector<int> n_5 = graph.getNextVertices(5);
    vector<int> p_5 = graph.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}
bool testSet8() {
    SetGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    ArcGraph graph_copy(graph);

    vector<int> n_0 = graph_copy.getNextVertices(0);
    vector<int> p_0 = graph_copy.getPrevVertices(0);
    vector<int> n_4 = graph_copy.getNextVertices(4);
    vector<int> p_4 = graph_copy.getPrevVertices(4);
    vector<int> n_5 = graph_copy.getNextVertices(5);
    vector<int> p_5 = graph_copy.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}*/

bool testArc1() {
    ArcGraph graph(0);
    return graph.verticesCount() == 0;
}
bool testArc2() {
    ArcGraph graph(2);
    graph.addEdge(0, 1);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 && p_0.empty() && n_1.empty() && p_1[0] == 0;
}
bool testArc3() {
    ArcGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(1, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return n_0[0] == 1 &&
           p_0[0] == 1 &&
           n_1[0] == 0 &&
           p_1[0] == 0;
}
bool testArc4() {
    ArcGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(n_0, 2) && p_0.empty() &&
           find(n_1, 2) && find(p_1, 0) &&
           n_2.empty() && find(p_2, 0) && find(p_2, 1);
}
bool testArc5() {
    ArcGraph graph(3);
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);
    vector<int> n_2 = graph.getNextVertices(2);
    vector<int> p_2 = graph.getPrevVertices(2);

    return find(n_0, 1) && find(p_0, 2) &&
           find(n_1, 2) && find(p_1, 0) &&
           find(n_2, 0) && find(p_2, 1);
}
bool testArc6() {
    ArcGraph graph(2);
    graph.addEdge(0, 1);
    graph.addEdge(0, 0);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_1 = graph.getNextVertices(1);
    vector<int> p_1 = graph.getPrevVertices(1);

    return find(n_0, 1) && find(n_0, 0) && find(p_0, 0) &&
           n_1.empty() && find(p_1, 0);
}
bool testArc7() {
    ArcGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    vector<int> n_0 = graph.getNextVertices(0);
    vector<int> p_0 = graph.getPrevVertices(0);
    vector<int> n_4 = graph.getNextVertices(4);
    vector<int> p_4 = graph.getPrevVertices(4);
    vector<int> n_5 = graph.getNextVertices(5);
    vector<int> p_5 = graph.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}
bool testArc8() {
    ArcGraph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(1, 2);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);

    ListGraph graph_copy(graph);

    vector<int> n_0 = graph_copy.getNextVertices(0);
    vector<int> p_0 = graph_copy.getPrevVertices(0);
    vector<int> n_4 = graph_copy.getNextVertices(4);
    vector<int> p_4 = graph_copy.getPrevVertices(4);
    vector<int> n_5 = graph_copy.getNextVertices(5);
    vector<int> p_5 = graph_copy.getPrevVertices(5);

    return find(n_0, 1) && find(n_0, 2) && find(n_0, 3) && p_0.empty() &&
           find(n_4, 5) && find(p_4, 1) && find(p_4, 3) &&
           n_5.empty() && find(p_5, 2) && find(p_5, 3) && find(p_5, 4);
}

static inline void print_tests(const string &name, vector<test_t> tests) {
    cout << "  --- " << name << " --- " << endl;
    for (int i = 0; i < tests.size(); ++i) {
        cout << "Test " << i + 1 << ((tests[i]()) ? ": OK" : ": Failed") << endl;
    }
    cout << endl;
}
#include "HashTable.h"
int main() {
    vector<test_t> list_tests = { testList1, testList2, testList3, testList4, testList5, testList6, testList7, testList8, };
    vector<test_t> matrix_tests = { testMatrix1, testMatrix2, testMatrix3, testMatrix4, testMatrix5, testMatrix6, testMatrix7, /*testMatrix8,*/ };
//    vector<test_t> set_tests = { testSet1, testSet2, testSet3, testSet4, testSet5, testSet6, testSet7, testSet8, };
    vector<test_t> arc_tests = { testArc1, testArc2, testArc3, testArc4, testArc5, testArc6, testArc7, testArc8, };

    print_tests("ListGraph", list_tests);
    print_tests("MatrixGraph", matrix_tests);
//    print_tests("SetGraph", set_tests);
    print_tests("ArcGraph", arc_tests);

    DefaultHash1<int> h1;
    DefaultHash2<int> h2;
    HashTable<int, DefaultHash1<int>, DefaultHash2<int>> ht(h1, h2);

    std::cout << " sedw " << std::endl;

//    ht.print();
//
//    int a = 123;
//    ht.insert(a);
//
//    ht.print();
    return 0;
}
