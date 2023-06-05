#include "Node.hpp"

#ifndef EDGE_H
#define EDGE_H

class DirectedEdge {
private:
    const Node * start;
    const Node * end;
    int max_flow;
    int curent_flow;

public:
    DirectedEdge(const Node * start, const Node * end, int max_flow);
    ~DirectedEdge();

    int IncreaseCurrentFlow(int flow);
    int GetCurrentFlow();
    int GetMaxFlow();
    const Node * GetStart();
    const Node * GetEnd();
    bool HasResidue();
    int GetResidueFlow();

};

#endif