#include "DirectedEdge.hpp"

DirectedEdge::DirectedEdge(Node * start, Node * end, int max_flow) {
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

Node * DirectedEdge::GetEnd() {
    return this->end;
}

Node * DirectedEdge::GetStart() {
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
