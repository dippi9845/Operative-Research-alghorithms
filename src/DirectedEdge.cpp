#include "DirectedEdge.hpp"

DirectedEdge::DirectedEdge(const Node * start, const Node * end, int max_flow) {
    this->start = start;
    this->end = end;
    this->max_flow = max_flow;
    this->curent_flow = 0;
}

int DirectedEdge::IncreaseCurrentFlow(int flow) {
    if (this->curent_flow + flow <= this->max_flow){
        this->curent_flow += flow;
    }
    
    return this->curent_flow;
}

int DirectedEdge::GetCurrentFlow() {
    return this->curent_flow;
}

const Node * DirectedEdge::GetEnd() {
    return this->end;
}

const Node * DirectedEdge::GetStart() {
    return this->start;
}

int DirectedEdge::GetMaxFlow() {
    return this->max_flow;
}

bool DirectedEdge::HasResidue() {
    return this->curent_flow < this->max_flow;
}

int DirectedEdge::GetResidueFlow() {
    return this->max_flow - this->curent_flow;
}

DirectedEdge::~DirectedEdge() {
}
