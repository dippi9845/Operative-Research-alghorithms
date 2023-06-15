#include "../Graph.hpp"
#ifndef FORD_FULKERSON_SERIAL
#define FORD_FULKERSON_SERIAL

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


class FordFulkersonSerial {

private:
    Graph * original;

    Path BFS(Node * start, Node * end);

protected:
    Graph * copy;
    
    void InitCopyGraph();

public:
    FordFulkersonSerial(Graph * max_flow_graph);
    int Solve();
    ~FordFulkersonSerial();

};

#endif