#include "../Graph.hpp"
#ifndef EDMONS_KARP_SERIAL
#define EDMONS_KARP_SERIAL

class Path
{
private:
    vector<DirectedEdge<Node> *> edges;
    int min_flow;
public:
    Path();
    bool IsEmpty();
    void AddEdge(DirectedEdge<Node> * edge);
    int IncreaseFlow();

    ~Path();
};


class EdmonsKarpSerial {

private:
    Graph * original;

    Path BFS(Node * start, Node * end);

protected:
    Graph * copy;
    
    void InitCopyGraph();

public:
    EdmonsKarpSerial(Graph * max_flow_graph);
    int Solve();
    ~EdmonsKarpSerial();

};

#endif