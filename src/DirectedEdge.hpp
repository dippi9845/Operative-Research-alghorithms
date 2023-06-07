#include "Node.hpp"

#ifndef EDGE_H
#define EDGE_H

class DirectedEdge {
private:
    Node * start;
    Node * end;
    int max_flow;
    int curent_flow;

public:
    DirectedEdge(Node * start, Node * end, int max_flow);
    ~DirectedEdge();

    int IncreaseCurrentFlow(int flow);
    int GetCurrentFlow();
    int GetMaxFlow();
    Node * GetStart();
    Node * GetEnd();
    bool HasResidue();
    int GetResidueFlow();

};

#endif