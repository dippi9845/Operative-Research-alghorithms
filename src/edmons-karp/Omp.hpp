#ifndef EDMONS_KARP_OMP
#define EDMONS_KARP_OMP

#include "Serial.hpp"
#include <omp.h>

class EdmonsKarpOmp : EdmonsKarpSerial {
private:
    vector<int> visited;
    vector<DirectedEdge<Node> *> parent_edge;

    Path BFS(Node * start, Node * end);

    void Expand(int adj_num, DirectedEdge<Node> * edge);

    void Explore(Node * node);

public:
    EdmonsKarpOmp(Graph * max_flow_graph);
    int Solve();
    ~EdmonsKarpOmp();
};

#endif